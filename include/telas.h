#ifndef TELAS_H
#define TELAS_H

#include "recursos.h"

typedef enum {
    TELA_INICIAL = 0,
    TELA_MENU,
    TELA_JOGO,
    TELA_MAPA,
    TELA_INPUT,
    TELA_SAVES,
    TELA_SALA,
    TELA_CAIXINHAS,
    TELA_GRIMORIO,
    TELA_DESAFIO1,
    TELA_DESAFIO2,
    TELA_DESAFIO3,
    TELA_DESAFIO4,
    TELA_DESAFIO5,
    SAIR
} EstadoTela;

// prototipação de funções
bool mudarTela (EstadoTela *telaAtual, Imagens *imagens, int LARGURA, int ALTURA, int *idSalaAtual);
// cada tela é representada por uma função
EstadoTela telaInicial(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaMenu(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaJogo(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA, int *idSalaAtual);
EstadoTela telaMapa(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA, int *idSalaAtual);
EstadoTela telaInput(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaGrimorio(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
#endif
