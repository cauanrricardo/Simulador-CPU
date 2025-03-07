#include "../src/globais.h"

//STORE
void strImediato(uint8_t r_destino, uint8_t imediato){
    if (imediato & 0x100) { // Se o bit 9 for 1 (negativo)
        imediato |= 0xFE00; // Estende com 1s (16 bits)
    }
    int16_t valor_c2 = (uint16_t) imediato;
    printf("STR R[%01x], #%04x\n", r_destino, valor_c2);
    Memoria_de_dados[Registrador[r_destino]] = valor_c2;
    printf("Valor final de Memoria_de_dados[%04x] = %04x\n", Registrador[r_destino], imediato);
}

void strRegistrador(uint8_t r_destino, uint8_t r_origem){
    printf("STR R[%01x], R[%01x]\n", r_destino, r_origem);
    Memoria_de_dados[Registrador[r_destino]] = Registrador[r_origem];
    printf("Valor final de Memoria_de_dados[%04x] = %04x\n", Registrador[r_destino], Registrador[r_origem]);
}

//LOAD
void ldr(uint8_t r_destino, uint8_t r_origem){ 
    printf("LDR R[%01x], R[%01x]\n", r_destino, r_origem);
    Registrador[r_destino] = Memoria_de_dados[Registrador[r_origem]];
    printf("Valor final de Registrador[%01x] = %04x\n", r_destino, Memoria_de_dados[Registrador[r_origem]]);
}