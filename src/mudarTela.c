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
#include "grimorio.h"
#include "desafioCaixinhas.h"

// função que muda de tela ativamente
bool mudarTela(EstadoTela *telaAtual, Imagens *imagens, int LARGURA, int ALTURA, int *idSalaAtual)
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
            *telaAtual = telaJogo(telaAtual, imagens, LARGURA, ALTURA, idSalaAtual);
            break;

        case TELA_MAPA:
            *telaAtual = telaMapa(telaAtual, imagens, LARGURA, ALTURA, idSalaAtual);
            break;

        case TELA_INPUT:
            *telaAtual = telaInput(telaAtual, imagens, LARGURA, ALTURA);
            break;

         case TELA_SAVES:
            *telaAtual = telaSlotsSave();
            break;

         case TELA_SALA:
            *telaAtual = telaSala(imagens, LARGURA, ALTURA, idSalaAtual);
            break;

         case TELA_CAIXINHAS:
            *telaAtual = RodarDesafioCaixinhas();
            break;
           
        case TELA_DESAFIO1:
			*telaAtual = desafioCaixinhas1();
            break;
            
		case TELA_DESAFIO2:
			*telaAtual = desafioCaixinhas2();
            break;
            
		case TELA_DESAFIO3:
			*telaAtual = desafioCaixinhas3();
            break;
            
		case TELA_DESAFIO4:
			*telaAtual = desafioCaixinhas4();
            break;
            
		case TELA_DESAFIO5:
			*telaAtual = desafioCaixinhas5();
            break;
		
        case TELA_GRIMORIO:
            *telaAtual = telaGrimorio(telaAtual, imagens, LARGURA, ALTURA);
            break;

        case SAIR:
            return true;
    }
    return false;
}
