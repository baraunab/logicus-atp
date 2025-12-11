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

int slotAtivo = -1;
SaveEstado *saveEmUso;
SaveEstado saveSlots[3];

void salvarEstadoDeJogo(SaveEstado *estado, int slot) {
    char arquivo[256];
    snprintf(arquivo, 256, "saves/slot%d", slot);

    FILE *f = fopen(arquivo, "wb");
    
    printf("LOG: escrevendo em save: %s\n", arquivo);

    // validacao se arquivo pode ser encontrado/aberto
    if (f == NULL) {
        printf("LOG: impossivel abrir arquivo: %s\n", arquivo);
        exit(1);
    }

    // ler estado passado para a funcao e armazenar em arquivo binario
    fwrite(estado, sizeof(SaveEstado), 1, f);

    // fechar arquivo
    fclose(f);
}

void carregarEstadoDeJogo(SaveEstado *estado, int slot) {
    char arquivo[256];
    snprintf(arquivo, 256, "saves/slot%d", slot);

    printf("LOG: carregando save: %s\n", arquivo);
    
    // abrir arquivo binario para leitura
    FILE *f = fopen(arquivo, "rb");

    if (f == NULL) {
        fclose(f);
        return;
    }

    // ler dados e armazenar no estado passado para a funcao
    fread(estado, sizeof(SaveEstado), 1, f);
    
    // fechar arquivo
    fclose(f);
}

void inicializarSistemaDeSave(SaveEstado *saveSlots) {
    for (int i = 0; i < 3; ++i) {
        char nome[32];
        snprintf(nome, 32, "saves/slot%d", i);

        FILE *f = fopen(nome, "rb");
        if (f == NULL) {
            FILE *fp = fopen("nome", "wb");
            fclose(fp);
            continue;
        }

        fread(&saveSlots[i], sizeof(SaveEstado), 1, f);
    }
}

EstadoTela telaSlotsSave(Imagens *imagens) {
    Rectangle slots[3];

    DrawTexture((*imagens).interface[SAVES_FUNDO], 0, 0, WHITE);

    int espacamento = 8;

    int alturaBotao = 64, larguraBotao = 256 * 2;
    int posicaoX = (GetScreenWidth() / 2) - ((larguraBotao + alturaBotao) / 2);
    int posicaoY = (GetScreenHeight() / 2) - (3 * alturaBotao) / 2;

    int tamanhoFonte = 20;

    for (int i = 0; i < 3; ++i) {
        slots[i] = (Rectangle) { posicaoX, posicaoY + ((alturaBotao + espacamento) * i), larguraBotao, alturaBotao };
        Rectangle apagar = (Rectangle) { posicaoX + larguraBotao + espacamento, posicaoY + ((alturaBotao + espacamento) * i), alturaBotao, alturaBotao };
        GuiSetIconScale(2);

        if (saveSlots[i].ativo) {
            DrawTexture((*imagens).interface[BOTAO_APAGAR_SAVE], apagar.x, apagar.y, WHITE);
        } else {
            DrawTexture((*imagens).interface[BOTAO_APAGAR_SAVE_INATIVO], apagar.x, apagar.y, WHITE);
        }

        if (CheckCollisionPointRec(GetMousePosition(), apagar) && saveSlots[i].ativo) {
            DrawTexture((*imagens).interface[BOTAO_APAGAR_SAVE_FOCADO], apagar.x, apagar.y, WHITE);
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                memset(&saveSlots[i], 0, sizeof(SaveEstado));
                salvarEstadoDeJogo(&saveSlots[i], i);

                printf("LOG: apagado save slot %d\n", i);
            }
        }

        char texto[256];
        if (saveSlots[i].ativo) {
            strcpy(texto, "Continuar jogando...");
        } else {
            strcpy(texto, "Novo jogo!");
        }
        
        DrawTexture((*imagens).interface[BOTAO_NORMAL], slots[i].x, slots[i].y, WHITE);
        DrawText(texto, slots[i].x + (alturaBotao / 2), slots[i].y + (alturaBotao / 2) - 8, tamanhoFonte, BLACK);
        
        if (CheckCollisionPointRec(GetMousePosition(), slots[i])) {
            DrawTexture((*imagens).interface[BOTAO_FOCADO], slots[i].x, slots[i].y, WHITE);
            DrawText(texto, slots[i].x + (alturaBotao / 2), slots[i].y + (alturaBotao / 2) - 8, tamanhoFonte, WHITE);
            
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                DrawTexture((*imagens).interface[BOTAO_PRESSIONADO], slots[i].x, slots[i].y, WHITE);
                DrawText(texto, slots[i].x + (alturaBotao / 2), slots[i].y + (alturaBotao / 2) - 8, tamanhoFonte, PURPLE);
            }
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                printf("LOG: selecionado slot %d\n", i);

                slotAtivo = i;
                saveEmUso = &saveSlots[i];
                saveEmUso->ativo = true;

                printf("saveEmUso->ativo = %d\n", saveEmUso->ativo);

                return TELA_JOGO;
            }
        }
    }

    return TELA_SAVES;
}
