#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

// VARIAVEIS DE CONTROLE ---------------------------------------------------------------------------------

bool UltimoInputFoiSucesso = false;
    // maximo de caracteres por linha com tamanho de fonte 20 é de 68 caracteres
    const char *strEnunciado = "A definir";
    char resposta [256] = "digite aqui sua resposta";
    const char *respostaCorreta = "resposta";
	
	EstadoTela destinoSucesso = TELA_MENU;
    EstadoTela destinoFalha = TELA_MENU;
    
    Rectangle areaBotaoAceitar;
    Rectangle areaBotaoRecusar;
    Rectangle areaBotaoVerificar;

    Color corAceitar = WHITE;
    Color corStrAceitar = BLACK;
    Color corRecusar = WHITE;
    Color corStrRecusar = BLACK;
    Color corVerificar = WHITE;
    Color corStrVerificar = BLACK;
    
    bool desativarFundo = false;
    bool label = false;
    bool resultado = false;
    bool tabClicado = false;
    bool desafioFeito = false;

// FIM DAS VARIAVEIS DE CONTROLE -------------------------------------------------------------------------
//função para configurar o desafio em cada tela
void configurarInput(const char *pergunta, const char *gabarito, EstadoTela sucesso, EstadoTela falha) {
    strEnunciado = pergunta;
    respostaCorreta = gabarito;
    destinoSucesso = sucesso;
    destinoFalha = falha;

    // Reseta as variaveis de controle para o novo desafio
    desativarFundo = false;
    label = false;
    resultado = false;
    tabClicado = false;
    desafioFeito = false;
    strcpy(resposta, "Digite aqui sua resposta.");
    
    // Reseta o status global do resultado
    UltimoInputFoiSucesso = false;
}

EstadoTela telaInput(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA) {

    // CAIXA DO ENUNCIADO --------------------------------------------------------------------------------
    
    DrawRectangleRounded((Rectangle){LARGURA * 0.01, ALTURA * 0.25, LARGURA * 0.98, ALTURA * 0.50}, 0.1f, 10, (Color){255, 255, 255, (255)/1});

    DrawText("DESAFIO DE SINTAXE", LARGURA * 0.04, ALTURA * 0.11, 50, RED);
    
    DrawText(strEnunciado, LARGURA * 0.04, ALTURA * 0.275, 20, BLACK);

    // FIM DA CAIXA DO ENUNCIADO -------------------------------------------------------------------------
    
    // BOTÕES --------------------------------------------------------------------------------------------

    areaBotaoRecusar = (Rectangle){ LARGURA * 0.01, ALTURA * 0.775, LARGURA * 0.48, ALTURA * 0.2 };
    areaBotaoAceitar = (Rectangle){ LARGURA * 0.51, ALTURA * 0.775, LARGURA * 0.48, ALTURA * 0.2 };
    DrawRectangleRounded(areaBotaoRecusar, 0.3f, 10, corRecusar);
    DrawRectangleRounded(areaBotaoAceitar, 0.3f, 10, corAceitar);
    
    DrawText("RECUSAR", LARGURA * 0.04, ALTURA * 0.9, 30, corStrRecusar);
    DrawText("ACEITAR", LARGURA * 0.54, ALTURA * 0.9, 30, corStrAceitar);

    // hover dos botões
    if (CheckCollisionPointRec(GetMousePosition(), areaBotaoRecusar) && desativarFundo == false) {
        
        // mudar cor do texto ao passar o mouse por cima
        corRecusar = RED;
        corStrRecusar = WHITE;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Recusar\n");
            return TELA_JOGO;
        }

    } else {
        corRecusar = WHITE;
        corStrRecusar = BLACK;
    }
    
    if (CheckCollisionPointRec(GetMousePosition(), areaBotaoAceitar) && desativarFundo == false) {
        
        // mudar cor do texto ao passar o mouse por cima
        corAceitar = (Color){ 0, 255, 255, 255 };
        corStrAceitar = WHITE;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Aceitar\n");
            label = true;
        }
    
    } else {
        corAceitar = WHITE;
        corStrAceitar = BLACK;
    }

    // FIM DOS BOTÕES ------------------------------------------------------------------------------------

    // ao soltar tab (você vai entender mais na frente no código) volta à label de resposta
    if (IsKeyReleased(KEY_TAB) && tabClicado) {
        label = true;
    }
    

    // INPUT ---------------------------------------------------------------------------------------------
    
    if (label) {

        // impede usar os botões ao usar o tab
        desativarFundo = true;
        
        // fundo preto transparente
        DrawRectangle(0, 0, LARGURA, ALTURA, (Color){ 0, 0, 0, 255 * 0.9 } );
        
        DrawText("Aperte Tab para voltar ao enunciado", LARGURA * 0.04, ALTURA * 0.13, 30, WHITE);
        
        GuiTextBox((Rectangle){LARGURA * 0.01, ALTURA * 0.25, LARGURA * 0.98, ALTURA * 0.50}, resposta, 120, true);

        // esse if serve para que ao segurar tab, o usuário não consiga clicar nos botões
        if (IsKeyPressed(KEY_TAB)) {
            tabClicado = true;
            label = false;
        }
        
        // botão verificar, não tem muito o que dizer
        areaBotaoVerificar = (Rectangle){ LARGURA * 0.51, ALTURA * 0.775, LARGURA * 0.48, ALTURA * 0.2 };
        DrawRectangleRounded(areaBotaoVerificar, 0.3f, 10, corVerificar);
        DrawText("VERIFICAR", LARGURA * 0.54, ALTURA * 0.9, 30, corStrVerificar);

        if (CheckCollisionPointRec(GetMousePosition(), areaBotaoVerificar)) {
            
            // mudar cor do texto ao passar o mouse por cima
            corVerificar = ORANGE;
            corStrVerificar = WHITE;
            
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && strcmp(resposta, "Digite aqui sua resposta.") != 0) {
                
                printf("Verificar\n");
                resultado = true;
                label = false;

            }
        
        } else {
            corVerificar = WHITE;
            corStrVerificar = BLACK;
        }
    
    }

    // FIM DO INPUT --------------------------------------------------------------------------------------

    // quando o desafio é concluido, você recebe um feedback através da tela de resultado
    if (resultado) {

        DrawRectangle(0, 0, LARGURA, ALTURA, (Color){ 0, 0, 0, 255 * 0.9 } );

        // se o desafio já foi feito anteriormente, aqui o programa avisa e pergunta ao usuário o que fazer
        if (desafioFeito) {

            DrawText("Este desafio já foi feito antes!", LARGURA * 0.21, ALTURA * 0.38, 30, ORANGE);
            DrawText("Aperte Espaçamento para tentar novamente.\nAperte Enter para continuar.", LARGURA * 0.215, ALTURA * 0.45, 20, WHITE);

            if (IsKeyPressed(KEY_SPACE)) {
                strcpy(resposta, "Digite aqui sua resposta.");
                desafioFeito = false;
                resultado = false;
                desativarFundo = false;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                return destinoFalha;
            }
            

        } else {

            // se as strings forem iguais
            if (strcmp(resposta, respostaCorreta) == 0) {
            
                DrawText("Bem na mosca!", LARGURA * 0.36, ALTURA * 0.38, 30, GREEN);
                DrawText("Aperte Enter para continuar", LARGURA * 0.305, ALTURA * 0.45, 20, WHITE);

                if (IsKeyPressed(KEY_ENTER)) {

                    // ao sair da tela, reinicia todas as variaveis de controle
                    desativarFundo = false,
                    label = false,
                    resultado = false,
                    tabClicado = false;
                    desafioFeito = true;
					
					UltimoInputFoiSucesso = true;
                    return destinoSucesso;
                }

            } else {

                // senão
                DrawText("RESPOSTA ERRADA", LARGURA * 0.305, ALTURA * 0.38, 30, RED);
                DrawText("Aperte Enter para continuar", LARGURA * 0.305, ALTURA * 0.45, 20, WHITE);

                if (IsKeyPressed(KEY_ENTER)) {

                    // ao sair da tela, reinicia todas as variaveis de controle
                    desativarFundo = false,
                    label = false,
                    resultado = false,
                    tabClicado = false;
                    desafioFeito = true;
                    
                    UltimoInputFoiSucesso = false;
                    return destinoFalha;
                    
                }
            }
        }
        
    }
    
    return *tela;
}