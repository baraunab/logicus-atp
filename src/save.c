#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raygui.h"

#include "recursos.h"
#include "telas.h"

#define ALTURA 800
#define LARGURA 480

// estrutura com campos de informacao de um save especifico
typedef struct {
    char nomeUsuario[64];

    int pontuacao;
    EstadoTela fase;
    int dialogoAtual;
    bool ativo;
} SaveEstado;

int slotAtivo = -1;

SaveEstado saveSlots[3];
SaveEstado *saveEmUso = &saveSlots[0];

char *nomesArquivosSave[3] = {
    "slot1",
    "slot2",
    "slot3"
};

void salvarEstadoDeJogo(SaveEstado *estado, int slot) {
    char arquivo[256] = "./saves/";
    strcat(arquivo, nomesArquivosSave[slot]);

    FILE *f = fopen(arquivo, "wb");
    
    printf("LOG: escrevendo save: %s\n", arquivo);

    // validacao se arquivo pode ser encontrado/aberto
    if (f == NULL) {
        printf("LOG: impossivel abrir arquivo: %s\n", arquivo);
        exit(1);
    }

    estado->ativo = true;
    
    // ler dados e armazenar no estado passado para a funcao
    fwrite(estado, sizeof(SaveEstado), 1, f);

    // fechar arquivo
    fclose(f);
}

void carregarEstadoDeJogo(SaveEstado *estado, int slot) {
    char arquivo[256] = "./saves/";
    strcat(arquivo, nomesArquivosSave[slot]);

    // abrir arquivo binario para leitura
    FILE *f = fopen(arquivo, "rb");

    printf("LOG: carregando save: %s\n", arquivo);
    // validacao se arquivo pode ser encontrado/aberto
    if (f == NULL) {
        fprintf(stderr, "ERRO: impossivel abrir arquivo: %s\n", arquivo);
        f = fopen(arquivo, "wb");
        fclose(f);
        return;
    }
    
    // ler dados e armazenar no estado passado para a funcao
    fread(estado, sizeof(SaveEstado), 1, f);
    
    // fechar arquivo
    fclose(f);
}

EstadoTela telaSlotsSave() {
    Rectangle slots[3];

    //Rectangle fundoDeTela = { 0, ALTURA * 0.04, 800, 480 };
    DrawRectangle(0, 0, 800, 480, PURPLE);
    //ClearBackground(GetColor(GuiGetStyle(DEFAULT, 20)));

    int espacamento = 8;

    int posicaoX = 16, posicaoY = 16;
    int alturaBotao = 64, larguraBotao = 256;

    char *nomeBotoes[3] = {
        "Slot 1",
        "Slot 2",
        "Slot 3"
    };

    for (int i = 0; i < 3; ++i) {
        slots[i] = (Rectangle) { posicaoX, posicaoY + ((alturaBotao + espacamento) * i), larguraBotao, alturaBotao };
        Rectangle apagar = (Rectangle) { posicaoX + larguraBotao + espacamento, posicaoY + ((alturaBotao + espacamento) * i), alturaBotao, alturaBotao };
        GuiSetIconScale(2);
        if (GuiButton(apagar, "#143#")) {
            memset(&saveSlots[i], 0, sizeof(SaveEstado));
            salvarEstadoDeJogo(&saveSlots[i], i);
            printf("LOG: Apagado save slot %d\n", i + 1);
        }
        if (GuiButton(slots[i], nomeBotoes[i])) { 
            slotAtivo = i;
            printf("LOG: Slot %d selecionado\n", i + 1);

            saveEmUso = &saveSlots[i];
            
            if (saveEmUso->ativo) {
                carregarEstadoDeJogo(saveEmUso, slotAtivo);
            }
            
            printf("saveEmUso->ativo = %d\n", saveEmUso->ativo);

            return TELA_JOGO;
        }
    }

    return TELA_SAVES;
}

void inicializarSistemaDeSave(void) {
    for (int i = 0; i < 3; ++i) {
        carregarEstadoDeJogo(&saveSlots[i], i);
        printf("LOG: Slot %d inicializado!\n", i + 1);
    }
}
