// se alterar, favor manter a ordem das includes de bibliotecas
#include "raylib.h"

#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

// função que muda de tela ativamente
void mudarTela(EstadoTela *telaAtual, Imagens *imagens, int LARGURA, int ALTURA)
{
    // estrutura de controle das telas
    switch (*telaAtual)
    {
    case TELA_INICIAL:
        *telaAtual = telaInicial(&telaAtual, &imagens, LARGURA, ALTURA);
        break;

    case TELA_MENU:
        *telaAtual = telaMenu(&telaAtual, &imagens, LARGURA, ALTURA);
        break;

    case TELA_JOGO:
        *telaAtual = telaJogo(&telaAtual, &imagens, LARGURA, ALTURA);
        break;

    case TELA_MAPA:
        *telaAtual = telaMapa(&telaAtual, &imagens, LARGURA, ALTURA);
        break;
    }
}

EstadoTela telaInicial(EstadoTela **tela, Imagens **imagens, int LARGURA, int ALTURA)
{
    DrawText("TELA INICIAL - Aperte Enter para começar.", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_ENTER))
    {
        return TELA_MENU;
    }
    else
    {
        // se Enter não for apertado a tela permanece a mesma
        return **tela;
    }
}

EstadoTela telaMenu(EstadoTela **tela, Imagens **imagens, int LARGURA, int ALTURA)
{
    // desenha splash arte do menu
    DrawTexture((**imagens).interface[SPLASH_ARTE], 0, 0, WHITE);

    // desenha titulo
    DrawTexture((**imagens).interface[TITULO_ARTE], (LARGURA / 2) - 180, ALTURA / 28, WHITE);
    DrawText("TELA DE MENU - Aperte Enter para continuar", 100, 200, 20, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        return TELA_JOGO;
    }
    else
    {
        // se Enter não for apertado a tela permanece a mesma
        return **tela;
    }
}

EstadoTela telaJogo(EstadoTela **tela, Imagens **imagens, int LARGURA, int ALTURA)
{
    DrawText("TELA DO JOGO - Aperte \'M\' para abrir o mapa", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_M))
    {
        return TELA_MAPA;
    }
    else
    {
        // se 'M' não for apertado a tela permanece a mesma
        return **tela;
    }
}

EstadoTela telaMapa(EstadoTela **tela, Imagens **imagens, int LARGURA, int ALTURA)
{
    DrawText("MAPA MPAAP MAPA", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_TAB))
    {
        return TELA_JOGO;
    }
    else
    {
        // se 'M' ou Tab não forem apertados a tela permanece a mesma
        return **tela;
    }
}