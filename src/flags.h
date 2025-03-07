#include "../src/globais.h"
#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
#include <stdio.h>

void atualizar_flags(uint16_t op1, uint16_t op2, uint32_t resultado, char operacao) {
    // Convertendo para inteiros com sinal para operações aritméticas
    int16_t signed_op1 = (int16_t)op1;
    int16_t signed_op2 = (int16_t)op2;
    int32_t signed_result;

    // Resetar todas as flags (O, C, Z, S)
    Flags &= ~((1 << 8) | (1 << 12) | (1 << 4) | 1);

    // Apenas operações aritméticas (A, S, M) modificam O e C
    if (operacao == 'A' || operacao == 'S' || operacao == 'M') {
        if (operacao == 'A') { // ADD
            signed_result = (int32_t)signed_op1 + signed_op2;
            // Overflow para adição
            if (((op1 & 0x8000) == (op2 & 0x8000)) && ((op1 & 0x8000) != (signed_result & 0x8000))) {
                Flags |= (1 << 8); // O = 1
            }
            // Carry (resultado excede 16 bits sem sinal)
            if (resultado > TAMANHO_DA_MEMORIA) {
                Flags |= (1 << 12); // C = 1
            }
        } 
        else if (operacao == 'S') { // SUB
            signed_result = (int32_t)signed_op1 - signed_op2;
            // Overflow para subtração
            if ((signed_op1 >= 0 && signed_op2 < 0 && signed_result < 0) || 
                (signed_op1 < 0 && signed_op2 >= 0 && signed_result >= 0)) {
                Flags |= (1 << 8); // O = 1
            }
            // Borrow (carry em subtração)
            if (op1 < op2) {
                Flags |= (1 << 12); // C = 1
            }
        } 
        else if (operacao == 'M') { // MUL
            signed_result = (int32_t)signed_op1 * signed_op2;
            int16_t truncated_signed = (int16_t)signed_result;
            // Overflow para multiplicação (sinal)
            if (signed_result != (int32_t)truncated_signed) {
                Flags |= (1 << 8); // O = 1
            }
            // Carry (resultado excede 16 bits sem sinal)
            if (resultado > TAMANHO_DA_MEMORIA) {
                Flags |= (1 << 12); // C = 1
            }
        }
    }

    // Atualização das flags Z e S para TODAS as operações
    Flags = (resultado == 0) ? (Flags | (1 << 4)) : (Flags & ~(1 << 4)); // Z
    Flags = (resultado & 0x8000) ? (Flags | 1) : (Flags & ~1); // S

    printf("Flags: 0x%04X\n", Flags);
}
#endif