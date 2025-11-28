// importacao de arquivos header de bibliotecas padrao

#include <stdio.h>

// importacao de arquivos header de bibliotecas third party

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

// importacao de arquivos header de prototipacao e carregamento

#include "recursos.h"
#include "telas.h"
#include "caixinhas.h"
#include "save.h"
#include "dialogo.h"
// declaracao de constantes globais
// ...

//Identificadores das salas
typedef enum {
	ID_SALA_NULA = 0,
	ID_SALA_BIBLIOTECAS,
	ID_SALA_MAIN,
	ID_SALA_VARIAVEIS,
	ID_SALA_PRINT,
	ID_SALA_SCAN
} IdSala;

//Struct para representar uma sala no mapa
typedef struct {
	Rectangle area;			//Área clicável do mapa (eixos, largura, altura)
	IdSala idProximaSala;	//Qual ID de sala vai ser carregado
	const char *nome;		//Nome da sala que vai aparecer na tela
	Color cor;				//Cor da sala no mapa
} SalaMapa;

// define tamanho da janela

#define LARGURA 800
#define ALTURA 480

// declaracao de variaveis globais
// ...

// vetor com a quantidade de slots de save acessiveis para o usuario
SaveEstado saveSlots[3];

int main(void) {
    // aloca estaticamente memoria para recursos de imagem
    Imagens imagens = {0};
    
    // funcao auxiliar de inicializacao dos saves
    inicializarSistemaDeSave(saveSlots);

    // declara a tela inicial ao abrir o programa
    EstadoTela tela = TELA_INICIAL;
    
    //Variavel para controlar em qual sala o jogador está
    int idSalaAtual = ID_SALA_NULA;

    // inicializa janela da biblioteca RayGUI
    InitWindow(LARGURA, ALTURA, "Logicus;");
    SetTargetFPS(60);

    // tamanho da fonte
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    
    // carrega recursos de imagem do jogo
    carregarRecursos(&imagens);

    // inicia game loop para desenhar na janela
    while (!WindowShouldClose()) {

        BeginDrawing();
            // limpa cor de fundo para proxima iteracao
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, 20)));

            // através desta função acontecem todas as transições
            if (mudarTela(&tela, &imagens, LARGURA, ALTURA)) {
                break;
            }

        EndDrawing();

    }
    
    // descarrega recursos de imagem alocadas pelo rayGUI
    descarregarRecursos(&imagens);

    // finaliza janela
    CloseWindow();
    return 0;
}
