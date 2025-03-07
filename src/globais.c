// globais.c
#include "../src/globais.h"

uint16_t Registrador[8] = {0};
uint16_t PC = 0;
uint16_t IR = 0;
uint16_t SP = 0x8200;
uint16_t Flags = 0000;
uint8_t Memoria_de_dados[TAMANHO_DA_MEMORIA] = {0};
uint8_t Memoria_de_programa[TAMANHO_DA_MEMORIA] = {0};
uint8_t Pilha[TAMANHO_DA_PILHA] = {0};