#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

#define TAMANHO_DA_MEMORIA (1 << 16)
#define START_PILHA_BASE 0x81F0
#define END_PILHA_BASE   0x8200
#define TAMANHO_DA_PILHA (END_PILHA_BASE - START_PILHA_BASE)

extern uint16_t Registrador[8];
extern uint16_t PC;
extern uint16_t IR;
extern uint16_t SP;
extern uint16_t Flags; // representa as flags Carry, Overflow, Zero, Signal respectivamente

// Como as funções de memória trabalham com bytes, defina as memórias como uint8_t:
extern uint8_t Memoria_de_dados[TAMANHO_DA_MEMORIA];
extern uint8_t Memoria_de_programa[TAMANHO_DA_MEMORIA];

extern uint8_t Pilha[TAMANHO_DA_PILHA];

#endif // GLOBALS_H