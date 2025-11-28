// se alterar, favor manter a ordem das includes de bibliotecas
#include "raylib.h"
#include "raygui.h"
#include "dialogo.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

// função que muda de tela ativamente
bool mudarTela(EstadoTela *telaAtual, Imagens *imagens, int LARGURA, int ALTURA)
{
    // estrutura de controle das telas
    switch (*telaAtual) {
        case TELA_INICIAL:
            *telaAtual = telaInicial(telaAtual, imagens, LARGURA, ALTURA);
            break;

        case TELA_MENU:
            *telaAtual = telaMenu(telaAtual, imagens, LARGURA, ALTURA);
            break;

        case TELA_JOGO:
            *telaAtual = telaJogo(telaAtual, imagens, LARGURA, ALTURA);
            break;

        case TELA_MAPA:
            *telaAtual = telaMapa(telaAtual, imagens, LARGURA, ALTURA);
            break;

        case TELA_INPUT:
            *telaAtual = telaInput(telaAtual, imagens, LARGURA, ALTURA);
            break;
            
        case SAIR:
            return true;
    }
    return false;
}
