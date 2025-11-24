// importacao de arquivos header de bibliotecas padrao

#include <stdio.h>

// importacao de arquivos header de bibliotecas third party

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

// importacao de arquivos header de prototipacao e carregamento

#include "save.h"
#include "dialogo.h"
#include "recursos.h"
#include "telas.h"

// declaracao de constantes globais
// ...

// define tamanho da janela

#define LARGURA 800
#define ALTURA 480

// declaracao de variaveis globais
// ...



int main(void) {
    // aloca estaticamente memoria para recursos de imagem
    Imagens imagens = {0};

    // declara a tela inicial ao abrir o programa
    EstadoTela tela = TELA_INICIAL;

    // inicializa janela da biblioteca RayGUI
    InitWindow(LARGURA, ALTURA, "Logicus;");
    SetTargetFPS(60);

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
