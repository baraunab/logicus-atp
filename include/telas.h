#ifndef TELAS_H
#define TELAS_H

typedef enum {
    TELA_INICIAL = 0,
    TELA_MENU,
    TELA_JOGO,
    TELA_MAPA,
    TELA_INPUT,
    TELA_SAVES,
    SAIR
} EstadoTela;

// prototipação de funções
bool mudarTela (EstadoTela *telaAtual, Imagens *imagens, int LARGURA, int ALTURA);
// cada tela é representada por uma função
EstadoTela telaInicial(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaMenu(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaJogo(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaMapa(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaInput(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);

#endif
