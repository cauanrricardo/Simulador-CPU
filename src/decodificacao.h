#include "../src/globais.h"

void decodificarInstrucao(uint16_t instrucao) {
    uint8_t opcode = (instrucao >> 12) & 0xF; // Extrai o opcode (4 bits mais significativos)
    uint8_t modo = (instrucao >> 11) & 0x1;   // Extrai o modo (5º bit)
    uint16_t operandos = instrucao & 0x7FF;   // Extrai os operandos (11 bits restantes)
    //MOV 
    if(opcode == 0b0001) { 
        if(modo == 0) {
            uint8_t rd = (operandos >> 8) & 0x7;
            uint8_t rm = (operandos >> 5) & 0x7;
            movRegistrador(rd, rm);
        }
        else {
            uint8_t rd = (operandos >> 8) & 0x7;
            uint16_t imediato = (operandos & 0xFF);
            movImediato(rd, imediato);
        }
    } 
    //STORE (STR)
    if(opcode == 0b0010) {
        if(modo == 0) {
            uint8_t rn = (operandos >> 2) & 0x7;
            uint8_t rm = (operandos >> 5) & 0x7;
            strRegistrador(rm, rn);
        }
        else {
            uint16_t parte_immediato = (operandos >> 8) & 0x7;
            uint16_t segunda_parte = operandos & 0x1F;
            uint16_t rm = (operandos >> 5) & 0x7;
            strImediato(rm, ((parte_immediato << 5) | segunda_parte));
        }
    } 
    //LOAD (LDR) 
    if(opcode == 0b0011) {
        uint8_t rd = (operandos >> 8) & 0x7;
        uint8_t rm = (operandos >> 5) & 0x7;
        ldr(rd,  rm);
        //Rd = endereço(Rm);
    }
    //Instruções da ULA
    uint8_t rd = (operandos >> 8) & 0x7;
    uint8_t rm = (operandos >> 5) & 0x7;
    uint8_t rn = (operandos >> 2) & 0x7;
    //ADD
    if(opcode == 0b0100) {
        add(rd, rm, rn);
    }
    //SUB
    if(opcode == 0b0101) {
        sub(rd, rm, rn);
    }
    //MUL
    if(opcode == 0b0110) {
        mul(rd, rm, rn);
    }
    //AND
    if(opcode == 0b0111) {
        and(rd, rm, rn);
    }
    //ORR
    if(opcode == 0b1000) {
        orr(rd, rm, rn);
    }
    //NOT
    if(opcode == 0b1001) {
        not(rd, rm);
    }
    //XOR
    if(opcode == 0b1010) {
        xor(rd, rm, rn);
    }
    // CMP & PILHA
    uint8_t LSB = operandos & 0x3;

    if(opcode == 0b0000 && modo == 0) {
        if(LSB == 0b11) {
            cmp(rm, rn);
        }
        else if(LSB == 0b01) {
            psh(rn);
        }
        else if(LSB == 0b10) {
            pop(rd);
        }
        else {
            printf("ERRO: Instrucao indefinida: 0x%04X\n", instrucao);
        }
    }
    //Shift Right (SHR)
    uint8_t imediato = operandos & 0x1F;
    if(opcode == 0b1011) {
        shr(rd, rm, imediato);
    }
    //Shift Left (SHL)
    if(opcode == 0b1100) {
        shl(rd, rm, imediato);
    }
    //Rotate Right (ROR)
    if(opcode == 0b1101) {
        ror(rd, rm);
    }
    //Rotate Left (ROL) 
    if(opcode == 0b1110) {
        rol(rd, rm);
    }
    //DESVIOS 
    if(opcode == 0b0000 && modo == 1) {
        uint16_t imediato = (operandos >> 2) & 0x1FF;
        if(LSB == 0b00) {
            jmp(imediato);
        }
        if(LSB == 0b01) {
            jeq(imediato);
        }
        if(LSB == 0b10) {
            jlt(imediato);
        }
        if(LSB == 0b11) {
            jgt(imediato);
        }
    }
    //NOP
    if(instrucao == 0x0000) {
        nop();
    }
    //HALT
    if(instrucao == 0xFFFF) {
        halt();
    }
    if (opcode > 0b1110) { // Opcodes válidos: 0b0000 a 0b1110
        printf("ERRO: Instrucao indefinida: 0x%04X\n", instrucao);
    } 
} 