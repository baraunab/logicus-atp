// prototipacao de funcoes e estruturas para funcionalidades relacionadas ao CRUD responsavel
// em salvar o estado de jogo

#ifndef SAVE_H
#define SAVE_H

#include "telas.h"

typedef struct {
    char nomeUsuario[64];

    int pontuacao;
    int fase;
    int dialogoAtual;

    bool ativo;
} SaveEstado;

extern SaveEstado *saveEmUso;
extern int slotAtivo;
extern SaveEstado saveSlots[3];

void salvarEstadoDeJogo(SaveEstado *estado, int slot);
void carregarEstadoDeJogo(SaveEstado *estado, int slot);
void inicializarSistemaDeSave(SaveEstado *saveSlots);

#endif // SAVE_H
