#include "../src/globais.h"

//MOV
void movImediato(uint8_t r_destino, uint16_t imediato) {
    if (imediato & 0x100) { // Se o bit 9 for 1 (negativo)
        imediato |= 0xFE00; // Estende com 1s (16 bits)
    }
    // Converte o imediato (uint16_t) para int16_t (complemento de 2)
    int16_t valor_c2 = (int16_t)imediato;
    printf("MOV R[%01x], #%04x\n", r_destino, valor_c2);
    Registrador[r_destino] = valor_c2;
    printf("Valor final de R[%01x] = %04x\n", r_destino, valor_c2);
}

void movRegistrador(uint8_t r_destino, uint8_t r_origem) {
    printf("MOV R[%01x], R[%01x]\n", r_destino, r_origem);
    Registrador[r_destino] = Registrador[r_origem];
    printf("Valor final de R[%01x] = %04x\n", r_destino, Registrador[r_origem]);
}
