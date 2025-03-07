#include "../src/globais.h"
#include "../src/flags.h"
//ULA
void add(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    printf("ADD R[%01x], R[%01x], R[%01x]\n", r_destino, r_origem, r_origem2);
    Registrador[r_destino] = Registrador[r_origem] + Registrador[r_origem2];
    atualizar_flags(Registrador[r_origem], Registrador[r_origem2], (uint32_t)Registrador[r_destino], 'A');
    if((Flags & 0x1) == 1) { // Verifica se a flag Signal é igual a 1 (número negativo);
        printf("Valor final em complemento 2 de R[%01x] = %04x\n", r_destino, Registrador[r_destino]);
    }
    else {
        printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
    }
}

void sub(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    printf("SUB R[%01x], R[%01x], R[%01x]\n", r_destino, r_origem, r_origem2);
    Registrador[r_destino] = Registrador[r_origem] - Registrador[r_origem2]; 
    atualizar_flags(Registrador[r_origem], Registrador[r_origem2], Registrador[r_destino], 'S');
    if((Flags & 0x1) == 1) { // Verifica se a flag Signal é igual a 1 (número negativo);
       printf("Valor final em complemento 2 de R[%01x] = %04x\n", r_destino, Registrador[r_destino]);
    }
    else {
       printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
    }
}

void mul(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    printf("MUL R[%01x], R[%01x], R[%01x]\n", r_destino, r_origem, r_origem2);
    Registrador[r_destino] = Registrador[r_origem] * Registrador[r_origem2];
    atualizar_flags(Registrador[r_origem], Registrador[r_origem2], Registrador[r_destino], 'M');
    if((Flags & 0x1) == 1) { // Verifica se a flag Signal é igual a 1 (número negativo);
        printf("Valor final em complemento 2 de R[%01x] = %04x\n", r_destino, Registrador[r_destino]);
    }
    else {
        printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
    }
}


void and(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    printf("AND R[%01x], R[%01x], R[%01x]\n", r_destino, r_origem, r_origem2);
    Registrador[r_destino] = Registrador[r_origem] & Registrador[r_origem2];
    atualizar_flags(Registrador[r_origem], Registrador[r_origem2], Registrador[r_destino], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
    
}

void xor(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    printf("XOR R[%01x], R[%01x], R[%01x]\n", r_destino, r_origem, r_origem2);
    Registrador[r_destino] = Registrador[r_origem] ^ Registrador[r_origem2];
    atualizar_flags(Registrador[r_origem], Registrador[r_origem2], Registrador[r_destino], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
}

void orr(uint8_t r_destino, uint8_t r_origem, uint8_t r_origem2) {
    printf("ORR R[%01x], R[%01x], R[%01x]\n", r_destino, r_origem, r_origem2);
    Registrador[r_destino] = Registrador[r_origem] | Registrador[r_origem2];
    atualizar_flags(Registrador[r_origem], Registrador[r_origem2], Registrador[r_destino], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
}

void shr(uint8_t r_destino, uint8_t r_origem, uint8_t imediato) {
    if (imediato & 0x100) { // Se o bit 9 for 1 (negativo)
        imediato |= 0xFE00; // Estende com 1s (16 bits)
    }
    // Converte o imediato para int8_t (complemento de 2)
    int8_t offset = (int8_t)imediato;
    if (offset < 0) {
        // Se o deslocamento for negativo, trata como 0
        printf("ERRO: Valor negativo!, tratado como 0.\n");
        offset = 0;
    }
    printf("SHR R[%01X], R[%01X], #%03x\n", r_destino, r_origem, imediato);
    Registrador[r_destino] = Registrador[r_origem] >> offset;
    atualizar_flags(Registrador[r_origem], imediato, Registrador[r_destino], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
}


void shl(uint8_t r_destino, uint8_t r_origem, uint8_t imediato){
    if (imediato & 0x100) { // Se o bit 9 for 1 (negativo)
        imediato |= 0xFE00; // Estende com 1s (16 bits)
    }
    // Converte o imediato para int8_t (complemento de 2)
    int8_t offset = (int8_t)imediato;

    printf("SHL R[%01X], R[%01X], #%03x\n", r_destino, r_origem, imediato);
    if (offset < 0) {
        // Se o deslocamento for negativo, trata como 0
        printf("ERRO: Valor negativo!, tratado como 0.\n");
        offset = 0;
    } 
    Registrador[r_destino] = Registrador[r_origem] << offset;
    atualizar_flags(Registrador[r_origem], imediato, Registrador[r_destino], 'L');  // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", r_destino, Registrador[r_destino]);
}

void ror(uint8_t Rd, uint8_t Rm) {
    printf("ROR R[%01X], R[%01X]\n", Rd, Rm);
    uint16_t valor = Registrador[Rm];
    uint16_t bitLSB = valor & 1; // Obtém o bit menos significativo (LSB)
    Registrador[Rd] = (valor >> 1) | (bitLSB << 15); // Move bits e recoloca o LSB no MSB
    atualizar_flags(valor, 0, Registrador[Rd], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", Rd, Registrador[Rd]);
}

void rol(uint8_t Rd, uint8_t Rm) {
    printf("ROL R[%01X], R[%01X]\n", Rd, Rm);
    uint16_t valor = Registrador[Rm];
    uint16_t bitMSB = (valor >> 15) & 1; // Obtém o bit mais significativo (MSB)
    Registrador[Rd] = (valor << 1) | bitMSB; // Move bits e recoloca o MSB no LSB
    atualizar_flags(valor, 0, Registrador[Rd], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%02x]: %04x\n", Rd, Registrador[Rd]);
}

void cmp(uint8_t r1, uint8_t r2) {
    printf("CMP R[%01X], R[%01X]\n", r1, r2);
    uint16_t valor_r1 = Registrador[r1];
    uint16_t valor_r2 = Registrador[r2];
    int16_t resultado = (int16_t)(valor_r1 - valor_r2); // Resultado com sinal

    // Resetar flags Z (bit 4) e S (bit 0)
    Flags &= ~((1 << 4) | (1 << 0));
    
    // Atualizar flag Z (Zero): 1 se os valores são iguais
    if (valor_r1 == valor_r2) {
        Flags |= (1 << 4);
    }
    // Atualizar flag S (Signal): 1 se o resultado da subtração é negativo
    if (resultado < 0) {
        Flags |= (1 << 0);
    }
    printf("Flags apos o cmp: %04x\n", Flags);
}

void not(uint8_t Rd, uint8_t Rm) {
    printf("NOT R[%01X], R[%01X]\n", Rd, Rm);
    Registrador[Rd] = ~Registrador[Rm];
    atualizar_flags(Registrador[Rd], Registrador[Rm], Registrador[Rd], 'L'); // 'L' para lógica/rotação
    printf("Valor final de R[%01x]: %04x\n", Rd, Registrador[Rd]);
}
