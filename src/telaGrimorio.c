#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "raygui.h"

#include "recursos.h"
#include "telas.h"
#include "grimorio.h"

// card de instruções exibido no lado esquerdo
typedef struct Card {
	char titulo[20];
	char texto[50];
} Card;

// array com os dados dos cards
Card cardsGrimorio [5] = {
	{"pancada", "pancada();"},
	{"Misseis mágicos", "for(i = 1, i != 0, misseis magicos)"},
	{"Aniquilar", "if(inimigoVivo){aniquilar};"},
	{"Lord C", "?????????"},
	{"Ornácio", "Por algum motivo\no herói anotou isso"}
};

// fundo combinando com a cor da imagem
Color fundo = (Color){20, 12, 28, 100};
Color corTransparente = (Color){0, 0, 0, 0};

static float scrollPaginaEsquerda = 0;
static float scrollPaginaDireita = 0;

bool verificaHoverPagina (Rectangle retangulo) {
	return CheckCollisionPointRec(GetMousePosition(), retangulo);
}

EstadoTela telaGrimorio(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA){
	
	// divisão das paginas 
	Rectangle paginaEsquerda = { 100, 90, 270, 285 };
	Rectangle paginaDireita = { 430, 90, 270, 285 };
	
	// ponteiro para as variaveis estaticas do scroll
	float *deslocarScrollEsquerda = &scrollPaginaEsquerda;
	float *deslocarScrollDireita = &scrollPaginaDireita;		
	
	// fundo combinando	
	ClearBackground(fundo);

        DrawTexture((*imagens).interface[FUNDO_GENERICO], 0, 0, WHITE);

	// imagem do grimorio
	DrawTexture((*imagens).interface[GRIMORIO], 0, 40, WHITE);
	
	int estadoGuiTemporario = GuiGetState();
	
	GuiSetStyle(DEFAULT, BORDER_WIDTH, 0);
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x00000000);
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x00000000);
	
	float alturaConteudoEsquerda = 5 * 90 + 10;
	
        if (alturaConteudoEsquerda > paginaEsquerda.height) {
            float movimentoScroll = GetMouseWheelMove();
            if (verificaHoverPagina(paginaEsquerda) && movimentoScroll != 0) {
                *deslocarScrollEsquerda += movimentoScroll * 20.0f;
            }

            // Limita o scroll
            if (*deslocarScrollEsquerda > 0) {
                *deslocarScrollEsquerda = 0;
            }

            float maximoScroll = paginaEsquerda.height - alturaConteudoEsquerda;

            if (*deslocarScrollEsquerda < maximoScroll) { 
                *deslocarScrollEsquerda = maximoScroll;
            }
        } else {
            *deslocarScrollEsquerda = 0;
        }
	
	
	// Limita o desenho da pagina 
	BeginScissorMode(
		(int)paginaEsquerda.x, (int)paginaEsquerda.y,
		(int)paginaEsquerda.width, (int)paginaEsquerda.height
	);
	
	// cards exibidos no lado esquerdo
	float larguraCard = paginaEsquerda.width - (20);
	
	// tamanho dos textos nos cards
	int TAM_TITULO = 25;
	int TAM_TEXTO = 15;
	
	for (int i = 0; i < 5; i++){
		Rectangle areaCard = {
			paginaEsquerda.x + 10, paginaEsquerda.y + 10 + (float)i * 90 + *deslocarScrollEsquerda, larguraCard, 80
		};
		
		// desenho dos cards	
		DrawRectangleRec(areaCard, corTransparente);
		DrawRectangleLinesEx(areaCard, 1, BLACK);
		
		// escrita do nos cards
		// TÍTULO
		DrawText(cardsGrimorio[i].titulo, areaCard.x + 5, areaCard.y + 5, TAM_TITULO, DARKPURPLE);
		
		// TEXTO
		DrawText(cardsGrimorio[i].texto, areaCard.x + 5, areaCard.y + 30, TAM_TEXTO, BLACK);
		
	}
	
	EndScissorMode();
	
        GuiSetStyle(BUTTON, BORDER_WIDTH, 1);
        GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BLACK));
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(corTransparente));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(DARKPURPLE));


        float alturaConteudoDireita = 5 * 60 + 10;

        if (alturaConteudoDireita > paginaDireita.height) {
            float movimentoScroll = GetMouseWheelMove();
            if (verificaHoverPagina(paginaDireita) && movimentoScroll != 0) {
                *deslocarScrollDireita += movimentoScroll * 20.0f;
            }

            // Limita o scroll
            if (*deslocarScrollDireita > 0) {
                *deslocarScrollDireita = 0;
            }

            float maximoScroll = paginaDireita.height - alturaConteudoDireita;

            if (*deslocarScrollDireita < maximoScroll) { 
                *deslocarScrollDireita = maximoScroll;
            }
        } else {
            *deslocarScrollDireita = 0;
        }
	
	
	BeginScissorMode(
		(int)paginaDireita.x, (int)paginaDireita.y,
		(int)paginaDireita.width, (int)paginaDireita.height
	);
	
	// cards exibidos no lado esquerdo
	float larguraBotao = paginaDireita.width - (20);
	
	for (int i = 0; i < 5; i++){
		Rectangle areaBotao = {
			paginaDireita.x + 10, paginaDireita.y + 10 + (float)i * 60 + *deslocarScrollDireita, larguraBotao, 50
		};
		
		char rotulo[5][20] = {
			"Biblioteca",
			"Variável",
			"Entrada",
			"Condicional",
			"Laço"
		};

        if (GuiButton(areaBotao, rotulo[i]))  {
			if (i + 1 == 1) {
				EndScissorMode();
				GuiSetState(estadoGuiTemporario);
				return TELA_DESAFIO1;
			} else if (i + 1 == 2) {
				EndScissorMode();
				GuiSetState(estadoGuiTemporario);
				return TELA_DESAFIO2;
			} else if (i + 1 == 3) {
				EndScissorMode();
				GuiSetState(estadoGuiTemporario);
				return TELA_DESAFIO3;
			} else if (i + 1 == 4) {
				EndScissorMode();
				GuiSetState(estadoGuiTemporario);
				return TELA_DESAFIO4;
			} else if (i + 1 == 5) {
				EndScissorMode();
				GuiSetState(estadoGuiTemporario);
				return TELA_DESAFIO5;
			} 	
		}	
	}
	
	EndScissorMode();
	
	GuiSetState(estadoGuiTemporario);
	
	// retorna para a tela do jogo
	if (IsKeyPressed(KEY_I)){
		return TELA_JOGO;
	}
	
	return *tela;
}
