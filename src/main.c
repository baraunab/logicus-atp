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

// define tamanho da janela

#define LARGURA 800
#define ALTURA 480

// declaracao de variaveis globais
// ...

// vetor com a quantidade de slots de save acessiveis para o usuario

int main(void) {
    // carrega saves de jogo existentes
    inicializarSistemaDeSave();

    // aloca estaticamente memoria para recursos de imagem
    Imagens imagens = {0};
    
    // declara a tela inicial ao abrir o programa
    EstadoTela tela = TELA_MENU;

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
