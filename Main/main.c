#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../src/ula.h"
#include "../src/pilha.h"
#include "../src/desvio.h"
#include "../src/mov.h"
#include "../src/nop_halt.h"
#include "../src/store_load.h"
#include "../src/decodificacao.h"
#include "../src/globais.c"
#include "../src/globais.h"
#include "../src/flags.h"

uint16_t ler_memoria(uint8_t Memoria_de_programa[], uint16_t address)
{
    uint16_t addr = address & 0xFFFE; // força endereço par
    uint8_t byte0 = Memoria_de_programa[addr];
    uint8_t byte1 = Memoria_de_programa[addr + 1];
    return (byte0 << 8) | (byte1);
}

void escrever_byte_memoria(uint8_t Memoria_de_programa[], uint16_t address, uint8_t data)
{
    Memoria_de_programa[address] = data;
}

void escrever_half_memoria(uint8_t Memoria_de_programa[], uint16_t address, uint16_t data)
{
    uint8_t byte0 = (uint8_t)(data & 0x00ff);
    uint8_t byte1 = (uint8_t)((data & 0xff00) >> 8);

    escrever_byte_memoria(Memoria_de_programa, address, byte1);
    escrever_byte_memoria(Memoria_de_programa, (address + 1), byte0);
}

uint16_t ler_memoria_de_program(uint16_t address)
{
    return ler_memoria(Memoria_de_programa, address);
}

void busca()
{
    IR = ler_memoria(Memoria_de_programa, PC);
    PC = PC + 2;
    printf("IR: %04x, PC: %04x\n", IR, PC);
}

/////////////////////////////////////////////////////

int main()
{
    FILE *arquivo;
    char nomeArquivo[100]; // Nome do arquivo
    uint16_t endereco, instrucao;
    int halt = 0;
    uint16_t maior_endereco = 0; // Guarda o maior endereço lido
    uint16_t armazena_PC; // Guarda o ultimo PC

    printf("Digite o path do arquivo: ");
    scanf("%99s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Lê o arquivo linha por linha no formato "endereço: 0xINSTRUÇÃO"
    while (fscanf(arquivo, "%hx: 0x%hx", &endereco, &instrucao) == 2)
    {
        printf("Lendo endereco 0x%04X: 0x%04X\n", endereco, instrucao); // Depuração
        escrever_half_memoria(Memoria_de_programa, endereco, instrucao);
        if (endereco > maior_endereco)
        {
            maior_endereco = endereco;
        }
    }
    fclose(arquivo);

    // Certifica-se de que maior_endereco é par
    if (maior_endereco % 2 != 0)
    {
        maior_endereco++;
    }

    // Depuração: Mostra o maior endereço carregado e o PC inicial
    printf("Maior endereco carregado: 0x%04X\n", maior_endereco);
    printf("PC inicial: 0x%04X\n", PC);

    // Executa instruções até o maior endereço carregado
    while (!halt && PC <= maior_endereco)
    {
        busca();
        printf("Executando instrucao em 0x%04X: 0x%04X\n", PC - 2, IR);
        if(armazena_PC == PC) {
            printf("Loop detectado no PC 0x%04X! Encerrando.\n", PC - 2);
            IR = 0xFFFF;
        }
        // Verifica se a instrução é HALT (0xFFFF)
        if (IR == 0xFFFF) {
            halt = 1;
        }
        armazena_PC = PC;
        decodificarInstrucao(IR);
    }

    printf("Final da execucao do programa\n");
    if (halt == 0)
    {
        printf("Valores finais dos Componentes:\n");
        decodificarInstrucao(0xFFFF);
    }

    return 0;
}
