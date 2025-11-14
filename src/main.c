// importacao de arquivos header de bibliotecas padrao

#include <stdio.h>

// importacao de arquivos header de bibliotecas third party

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

// importacao de arquivos header de prototipacao

#include "save.h"
#include "dialogo.h"

// declaracao de constantes globais

// declaracao de variaveis globais

int main(void) {
    InitWindow(800, 460, "Logicus;");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
