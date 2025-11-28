#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "raygui.h"

#include "recursos.h"
#include "telas.h"

// estrutura com campos de informacao de um save especifico
typedef struct {
    char nomeUsuario[64];

    int pontuacao;
    EstadoTela fase;
    int dialogoAtual;
    bool ativo;
} SaveEstado;

int slotAtivo = 0;

SaveEstado saveSlots[3];
SaveEstado *saveEmUso = &saveSlots[0];

char *nomesArquivosSave[3] = {
    "slot1",
    "slot2",
    "slot3"
};

void salvarEstadoDeJogo(SaveEstado *estado) {
    char arquivo[256] = "./saves/";
    strcat(arquivo, nomesArquivosSave[slotAtivo]);

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

void carregarEstadoDeJogo(SaveEstado *estado) {
    char arquivo[256] = "./saves/";
    strcat(arquivo, nomesArquivosSave[slotAtivo]);

    // abrir arquivo binario para leitura
    FILE *f = fopen(arquivo, "rb");

    printf("LOG: carregando save: %s\n", arquivo);
    // validacao se arquivo pode ser encontrado/aberto
    if (f == NULL) {
        fprintf(stderr, "ERRO: impossivel abrir arquivo: %s\n", arquivo);
        exit(1);
    }
    
    // ler dados e armazenar no estado passado para a funcao
    fread(estado, sizeof(SaveEstado), 1, f);
    
    // fechar arquivo
    fclose(f);
}

EstadoTela telaSlotsSave() {
    Rectangle slots[3];

    int espacamento = 8;

    int posicaoX = 16, posicaoY = 16;
    int alturaBotao = 64, larguraBotao = 256;

    char *nomeBotoes[3] = {
        "Slot 1",
        "Slot 2",
        "Slot 3"
    };



    slots[0] = (Rectangle) { posicaoX, posicaoY + ((alturaBotao + espacamento)), larguraBotao, alturaBotao };
    
    if (GuiButton((Rectangle) { (posicaoX + larguraBotao) * 3, posicaoY, 64 , 64 }, "X")) {
        memset(saveEmUso, 0, sizeof(SaveEstado));
        salvarEstadoDeJogo(saveEmUso);
    }

    if (GuiButton(slots[0], nomeBotoes[0])) {
        slotAtivo = 0;

        if (saveEmUso->ativo == true) {
            carregarEstadoDeJogo(saveEmUso);
        } else {
            printf("Save inexistente\n");
        }

        return TELA_JOGO;
    }

    /*for (int i = 0; i < 3; ++i) {
        slots[i] = (Rectangle) { posicaoX, posicaoY + ((alturaBotao + espacamento) * i), larguraBotao, alturaBotao };

        if (GuiButton(slots[i], nomeBotoes[i])) { 
            slotAtivo = i;
            printf("Slot %d selecionado\n", i + 1);

            saveEmUso = &saveSlots[i];
            
            printf("saveEmUso->ativo = %d\n", saveEmUso->ativo);
            if (saveEmUso->ativo) {
                carregarEstadoDeJogo(saveEmUso);
            }
            
            printf("saveEmUso->ativo = %d\n", saveEmUso->ativo);

            return TELA_JOGO;
        }
    }*/

    return TELA_SAVES;
}
