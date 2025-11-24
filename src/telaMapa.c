// se alterar, favor manter a ordem das includes de bibliotecas
#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"

EstadoTela telaMapa(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA)
{
    DrawText("MAPA MPAAP MAPA", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_TAB)) {
        return TELA_JOGO;
    } else {
        // se 'M' ou Tab não forem apertados a tela permanece a mesma
        return *tela;
    }
}