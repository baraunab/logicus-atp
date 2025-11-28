// prototipacao de funcoes e estruturas para funcionalidades relacionadas ao CRUD responsavel
// em salvar o estado de jogo

#ifndef SAVE_H
#define SAVE_H

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

bool salvarEstadoDeJogo(SaveEstado *estado);
bool carregarEstadoDeJogo(SaveEstado *estado);
EstadoTela telaSlotsSave(void);

#endif // SAVE_H
