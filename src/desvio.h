#include "../src/globais.h"

void jmp(uint16_t imediato) {
    printf("JMP #%03x\n", imediato); 
    if (imediato & 0x100) { // Se o bit 9 for 1 (negativo)
        imediato |= 0xFE00; // Estende com 1s (16 bits)
    }
    int16_t offset = (int16_t)imediato; // Converte para complemento de 2
    PC += offset; // Desvio relativo ao PC atual
}

void jeq(uint16_t imediato) {
    printf("JEQ #%03x\n", imediato);
    if (imediato & 0x100) { 
        imediato |= 0xFE00; 
    }
    int16_t offset = (int16_t)imediato; 
    if ((Flags & 0x10) && !(Flags & 0x1)) { // Zero ativo e Signal inativo
        PC += offset; 
    }
}

void jlt(uint16_t imediato) {
    printf("JLT #%03x\n", imediato);
    if (imediato & 0x100) { 
        imediato |= 0xFE00; 
    }
    int16_t offset = (int16_t)imediato;
    if (!(Flags & 0x10) && (Flags & 0x1)) { // Zero inativo e Signal ativo
        PC += offset; 
    }
}

void jgt(uint16_t imediato) {
    printf("JGT #%04x\n", imediato);
    if (imediato & 0x100) { 
        imediato |= 0xFE00; 
    }
    int16_t offset = (int16_t)imediato; 
    if (!(Flags & 0x10) && !(Flags & 0x1)) { // Zero e Signal inativos
        PC += offset; 
    }
}