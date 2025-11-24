// se alterar, favor manter a ordem das includes de bibliotecas
#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

EstadoTela telaInicial(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA)
{
    DrawText("TELA INICIAL - Aperte Enter para começar.", 100, 200, 20, WHITE);
    if (IsKeyPressed(KEY_ENTER)) {
        return TELA_MENU;
    } else {
        // se Enter não for apertado a tela permanece a mesma
        return *tela;
    }
}