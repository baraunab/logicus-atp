#ifndef TELAS_H
#define TELAS_H

#include "recursos.h"
#include "save.h"

typedef enum {
    TELA_INICIAL = 0,
    TELA_MENU,
    TELA_JOGO,
    TELA_MAPA,

    //Telas de fases (salas)
    TELA_ENTRADA,
    TELA_ENIGMA,
    TELA_BAU,
    TELA_LABIRINTO,
    TELA_LACOS,
    //Fim das fases
    TELA_COMBATE,
    TELA_INPUT,
    TELA_SAVES,
    TELA_SALA,
  
    TELA_DESAFIO1,
    TELA_DESAFIO2,
    TELA_DESAFIO3,
    TELA_DESAFIO4,
    TELA_DESAFIO5,
  
    TELA_CAIXINHAS,
    TELA_GRIMORIO,
    SAIR
} EstadoTela;

// prototipação de funções
void configurarInput(const char *pergunta, const char *gabarito, EstadoTela sucesso, EstadoTela falha);
bool mudarTela (EstadoTela *telaAtual, Imagens *imagens, int LARGURA, int ALTURA);
// cada tela é representada por uma função
EstadoTela telaInicial(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaMenu(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaJogo(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaMapa(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaInput(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaSlotsSave(Imagens *imagens);
EstadoTela telaGrimorio(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA);

EstadoTela desafioCaixinhas1(void);
EstadoTela desafioCaixinhas2(void);
EstadoTela desafioCaixinhas3(void);
EstadoTela desafioCaixinhas4(void);
EstadoTela desafioCaixinhas5(void);

//Protótipo de fases
EstadoTela telaEntrada(Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaEnigma(Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaBau(Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaLabirinto(Imagens *imagens, int LARGURA, int ALTURA);
EstadoTela telaLacos(Imagens *imagens, int LARGURA, int ALTURA);

//Variavel para entregar para as outras telas o resultado do ultimo input
extern bool UltimoInputFoiSucesso;

#endif
