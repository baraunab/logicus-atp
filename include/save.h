// prototipacao de funcoes e estruturas para funcionalidades relacionadas ao CRUD responsavel
// em salvar o estado de jogo

#ifndef SAVE_H
#define SAVE_H

typedef struct {
    char nomeUsuario[64];

    int pontuacao;
    int fase;
    int numeroDialogo;
    bool ativo;

    int slot;
} SaveEstado;

void inicializarSistemaDeSave(SaveEstado *estado);
bool salvarEstadoDeJogo(SaveEstado estado);
bool carregarEstadoDeJogo(SaveEstado *estado);
#endif // SAVE_H
