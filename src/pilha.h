#include "../src/globais.h"
uint16_t ler_memoria_pilha(uint8_t Memoria_de_dados[], uint16_t SP)
{
    uint16_t addr = SP & 0xFFFE; //forca endereco par

    uint8_t byte0 = Memoria_de_dados[addr];
    uint8_t byte1 = Memoria_de_dados[addr - 1];
    //printf("IR: %02x %02x\n", byte0, byte1);
    return (byte0 << 8) | (byte1);
}
uint16_t ler_memoria_de_dados_pilha(uint16_t address)
{
    return ler_memoria_pilha(Memoria_de_dados, address);
}
void escrever_byte_pilha(uint8_t Memoria_de_dados[], uint16_t SP, uint8_t data)
{
    Memoria_de_dados[SP] = data; /////dados -> pilha
    printf("Pilha[%04x] = %04x\n", SP, data);
}
void escrever_half_pilha(uint8_t Memoria_de_dados[], uint16_t SP, uint16_t data) //////- dados -> programa
{
    uint8_t byte0 = (uint8_t)(data & 0x00ff);
    uint8_t byte1 = (uint8_t)((data & 0xff00) >> 8);

    escrever_byte_pilha(Memoria_de_dados, SP, byte1);
    escrever_byte_pilha(Memoria_de_dados, (SP - 1), byte0);
}
//PILHA
void psh(uint8_t Rn) {
    printf("PUSH R[%01x]\n", Rn);
    if(SP == START_PILHA_BASE){
        printf("ERRO: PILHA CHEIA!, NAO E POSSIVEL DAR PUSH.\n");
        return;
    }
    escrever_half_pilha(Memoria_de_dados, SP, Registrador[Rn]);
    SP -= 2; //SP decrementa depois no PUSH, pois a pilha que estamos trabalhando é empty descend;
    printf("Valor final de SP = %04x\n", SP);
}
void pop(uint8_t Rd) {
    printf("POP R[%01x]\n", Rd);
    if (SP < END_PILHA_BASE) { // Verifica se a pilha não está vazia
        SP += 2; //SP incrementa antes no POP, pois a pilha que estamos trabalhando é empty descend;
        Registrador[Rd] = ler_memoria_de_dados_pilha(SP); // Rd recebe o valor no topo da pilha
        printf("Valor final de Registrador[%01x] = %04x\n", Rd, ler_memoria_de_dados_pilha(SP));
        printf("Valor final de SP = %04x\n", SP);
    } else {
        printf("ERRO: PILHA TA VAZIA!, NAO E POSSIVEL DAR POP.\n");
    }
}