// se alterar, favor manter a ordem das includes de bibliotecas
#include "raylib.h"
#include "raygui.h"
#include "dialogo.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"
#include "save.h"
#include "telaSala.h"
#include "caixinhas.h"
#include "combate.h"

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
            
        //Novas telas de fases
        case TELA_ENTRADA:
            *telaAtual = telaEntrada(imagens, LARGURA, ALTURA);
            break;

        case TELA_ENIGMA:
            *telaAtual = telaEnigma(imagens, LARGURA, ALTURA);
            break;

        case TELA_BAU:
            *telaAtual = telaBau(imagens, LARGURA, ALTURA);
            break;

        case TELA_LABIRINTO:
            *telaAtual = telaLabirinto(imagens, LARGURA, ALTURA);
            break;

        case TELA_LACOS:
            *telaAtual = telaLacos(imagens, LARGURA, ALTURA);
            break;
        //Fim das novas fases
		
		case TELA_COMBATE:
			*telaAtual = AtualizarCombate(imagens, LARGURA, ALTURA);
			break;
			
        case TELA_INPUT:
            *telaAtual = telaInput(telaAtual, imagens, LARGURA, ALTURA);
            break;

         case TELA_SAVES:
            *telaAtual = telaSlotsSave();
            break;

         case TELA_CAIXINHAS:
            *telaAtual = RodarDesafioCaixinhas();
            break;

        case SAIR:
            return true;
    }
    return false;
}
