// se alterar, favor manter a ordem das includes de bibliotecas
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

// FOLHA DE ESTILO ---------------------------------------------------------------------------------------

    Color
        corStrHistorico = WHITE,
        corStrPular = WHITE,
        corStrAuto = WHITE,
        corStrSalvar = WHITE,
        corStrCarregar = WHITE;
    
// FIM DA FOLHA DE ESTILO --------------------------------------------------------------------------------


// VARIAVEIS DE CONTROLE ---------------------------------------------------------------------------------

    // maximo de caracteres por linha com tamanho de fonte 20 é de 68 caracteres
    char strCaixaDialogo[] = "texto texto texto texto texto texto texto texto texto texto texto \ntexto texto texto texto texto texto texto texto texto texto texto \ntexto texto texto texto texto texto texto texto texto texto texto \ntexto texto texto texto texto texto texto texto texto texto texto \ntexto texto texto texto texto texto texto texto texto texto texto \n";
    // usar laço for() para realizar a quebra de linhas
    
// FIM DAS VARIAVEIS DE CONTROLE -------------------------------------------------------------------------

EstadoTela telaJogo(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA)
{
    /* levando em consideração que:
        typedef struct Rectangle {
            float x;      // posição horizontal (eixo X)
            float y;      // posição vertical (eixo Y)
            float width;  // largura do retângulo
            float height; // altura do retângulo
        } Rectangle;
    */

    DrawTexture((*imagens).interface[IMAGEM_FUNDO], 0, 0, WHITE);
    Rectangle fundoDeTela = {0, ALTURA * 0.04, 800, 480};

    // calcula área de clique baseada no tamanho do texto
    int larguraHistorico = MeasureText("Histórico", 12);
    Rectangle areaHistorico = {LARGURA * 0.3, ALTURA * 0.01, larguraHistorico, 12};

    int larguraPular = MeasureText("Pular", 12);
    Rectangle areaPular = {LARGURA * 0.4, ALTURA * 0.01, larguraPular, 12};

    int larguraAuto = MeasureText("Auto", 12);
    Rectangle areaAuto = {LARGURA * 0.48725, ALTURA * 0.01 * 0.2, larguraAuto, 12};

    int larguraSalvar = MeasureText("Salvar", 12);
    Rectangle areaSalvar = {LARGURA * 0.54, ALTURA * 0.01 * 0.3, larguraSalvar, 12};

    int larguraCarregar = MeasureText("Carregar", 12);
    Rectangle areaCarregar = {LARGURA * 0.617, ALTURA * 0.01 * 0.4, larguraCarregar, 12};

    // desenha a palavra
    DrawText("Histórico", LARGURA * 0.3, ALTURA * 0.01, 12, corStrHistorico);
    DrawText("Pular", LARGURA * 0.4, ALTURA * 0.01, 12, corStrPular);
    DrawText("Auto", LARGURA * 0.475, ALTURA * 0.01, 12, corStrAuto);
    DrawText("Salvar", LARGURA * 0.54, ALTURA * 0.01, 12, corStrSalvar);
    DrawText("Carregar", LARGURA * 0.617, ALTURA * 0.01, 12, corStrCarregar);

    // CAIXA DE DIALOGO
    DrawRectangleRounded((Rectangle){LARGURA * 0.01, ALTURA * 0.65, LARGURA * 0.98, ALTURA * 0.33}, 0.3f, 10, (Color){0, 0, 0, (255)/1.5});
    // DIALOGO INTERNO
    DrawText(strCaixaDialogo, LARGURA * 0.04, ALTURA * 0.7, 20, WHITE);
    

    // HISTORICO
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaHistorico)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrHistorico = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Historico\n");
        }

    } else {
        corStrHistorico = WHITE;
    }

    // PULAR
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaPular)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrPular = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Pular\n");
        }

    } else {
        corStrPular = WHITE;
    }

    // AUTO
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaAuto)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrAuto = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Auto\n");
        }

    } else {
        corStrAuto = WHITE;
    }
    
    // SALVAR
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaSalvar)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrSalvar = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Salvar\n");
        }

    } else {
        corStrSalvar = WHITE;
    }

    // CARREGAR
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaCarregar)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrCarregar = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Carregar\n");
        }

    } else {
        corStrCarregar = WHITE;
    }

    // se (clicar na tela) OU apertar Enter OU apertar Espaçamento
    if ((CheckCollisionPointRec(GetMousePosition(), fundoDeTela) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        printf("Abrindo tela de input...\n");
        return TELA_INPUT;
    }
    
    
    return *tela;
}