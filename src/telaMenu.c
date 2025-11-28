// se alterar, favor manter a ordem das includes de bibliotecas
#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

// FOLHA DE ESTILO ---------------------------------------------------------------------------------------
    
    Color
        corStrJogar,
        corStrSair,
        corStrPadrao = WHITE,
        corStrDestaque = { 0, 255, 255, 255 };

    const int
        tamanhoFontePequena = 12,
        tamanhoFontePadrao = 20;
    
// FIM DA FOLHA DE ESTILO --------------------------------------------------------------------------------

// VARIAVEIS DE CONTROLE ---------------------------------------------------------------------------------

    Rectangle areaBotaoJogar;
    Rectangle areaBotaoSair;
    float transparencia = 255/2;

// FIM DAS VARIAVEIS DE CONTROLE -------------------------------------------------------------------------



EstadoTela telaMenu(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA) {
    // desenha splash arte do menu
    DrawTexture((*imagens).cenario[TORRE], 0, 0, WHITE);
    DrawTexture((*imagens).interface[TITULO_ARTE], (LARGURA / 2) - 180, ALTURA / 28, WHITE);

    /* levando em consideração que:
        typedef struct Rectangle {
            float x;      // posição horizontal (eixo X)
            float y;      // posição vertical (eixo Y)
            float width;  // largura do retângulo
            float height; // altura do retângulo
        } Rectangle;
    */

    // BOTÕES

    // botão JOGAR
    areaBotaoJogar = (Rectangle){LARGURA / 4, ALTURA * 0.5, LARGURA / 2, ALTURA / 9};
    DrawRectangleRounded(areaBotaoJogar, 0.3f, 10, (Color){0, 0, 0, transparencia});
    DrawText("JOGAR", LARGURA / 2.175, ALTURA * 0.5375, tamanhoFontePadrao, corStrJogar);

    // botão SAIR
    areaBotaoSair = (Rectangle){LARGURA / 4, ALTURA * 0.62, LARGURA / 2, ALTURA / 9};
    DrawRectangleRounded(areaBotaoSair, 0.3f, 10, (Color){0, 0, 0, transparencia});
    DrawText("SAIR", LARGURA / 2.12, ALTURA * 0.656, tamanhoFontePadrao, corStrSair);
    
    if (CheckCollisionPointRec(GetMousePosition(), areaBotaoJogar)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrJogar = corStrDestaque;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return TELA_SAVES;
        }

    } else {
        corStrJogar = corStrPadrao;
    }

    if (CheckCollisionPointRec(GetMousePosition(), areaBotaoSair)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrSair = corStrDestaque;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return SAIR;
        }

    } else {
        corStrSair = corStrPadrao;
    }

    return *tela;
}
