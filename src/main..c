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

    // inicializa janela da biblioteca RayGUI
    InitWindow(LARGURA, ALTURA, "Logicus;");
    SetTargetFPS(60);

    // carrega recursos de imagem do jogo
    carregarRecursos(&imagens);

    // inicia game loop para desenhar na janela
    while (!WindowShouldClose()) {
        BeginDrawing();
            // limpa cor de fundo para proxima iteracao
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // desenha splash arte do menu
            DrawTexture(imagens.interface[SPLASH_ARTE], 0, 0, WHITE);
            
            // desenha titulo
            DrawTexture(imagens.interface[TITULO_ARTE], (LARGURA / 2) - 180, ALTURA / 28, WHITE);
        EndDrawing();
    }
    
    // descarrega recursos de imagem alocadas pelo rayGUI
    descarregarRecursos(&imagens);

    // finaliza janela
    CloseWindow();
    return 0;
}
