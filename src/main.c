// importacao de arquivos header de bibliotecas padrao

#include <stdio.h>

// importacao de arquivos header de bibliotecas third party

#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"

// importacao de arquivos header de prototipacao e carregamento



#include "recursos.h"
#include "caixinhas.h"


// declaracao de constantes globais
// ...
typedef enum {
    TELA_INICIAL = 0,
    TELA_MENU,
    TELA_JOGO,
    TELA_MAPA
} EstadoTela;

// define tamanho da janela

#define LARGURA 800
#define ALTURA 480

// declaracao de variaveis globais
// ...

// prototipação de funções

void mudarTela (EstadoTela *telaAtual, Imagens *imagens);
// cada tela é representada por uma função
EstadoTela telaInicial(EstadoTela **tela);
EstadoTela telaMenu(EstadoTela **tela, Imagens **imagens);
EstadoTela telaJogo(EstadoTela **tela);
EstadoTela telaMapa(EstadoTela **tela);

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
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // através desta função acontecem todas as transições
            mudarTela(&tela, &imagens);

        EndDrawing();

    }
    
    // descarrega recursos de imagem alocadas pelo rayGUI
    descarregarRecursos(&imagens);

    // finaliza janela
    CloseWindow();
    return 0;
}

//função que muda de tela ativamente
void mudarTela (EstadoTela *telaAtual, Imagens *imagens){
    // estrutura de controle das telas
    switch(*telaAtual){
        case TELA_INICIAL:
            *telaAtual = telaInicial(&telaAtual);
            break;
        
        case TELA_MENU:
            *telaAtual = telaMenu(&telaAtual, &imagens);
            break;
        
        case TELA_JOGO:
            *telaAtual = telaJogo(&telaAtual);
            break;

        case TELA_MAPA:
            *telaAtual = telaMapa(&telaAtual);
            break;
    }
}

EstadoTela telaInicial(EstadoTela **tela){
    DrawText("TELA INICIAL - Aperte Enter para começar.", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_ENTER))
    {
        return TELA_MENU;
    } else {
        // se Enter não for apertado a tela permanece a mesma
        return **tela;
    }
}

EstadoTela telaMenu(EstadoTela **tela, Imagens **imagens){
    // desenha splash arte do menu
    DrawTexture((**imagens).interface[SPLASH_ARTE], 0, 0, WHITE);
    
    // desenha titulo
    DrawTexture((**imagens).interface[TITULO_ARTE], (LARGURA / 2) - 180, ALTURA / 28, WHITE);
    DrawText("TELA DE MENU - Aperte Enter para continuar", 100, 200, 20, WHITE);

    if (IsKeyPressed(KEY_ENTER))
    {
        return TELA_JOGO;
    } else {
        // se Enter não for apertado a tela permanece a mesma
        return **tela;
    }
}

EstadoTela telaJogo(EstadoTela **tela){
    // aqui roda o desafio dentro da tela de jogo
    EstadoTela telaJogo(EstadoTela **tela);{
    // aqui roda o desafio dentro da tela de jogo
    RodarDesafioCaixinhas();

    // exemplo de transição pro mapa continua igual
    if (IsKeyPressed(KEY_M)) {
        return TELA_MAPA;
    } else {
        return **tela;
    }
}

    DrawText("TELA DO JOGO - Aperte \'M\' para abrir o mapa", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_M))
    {
        return TELA_MAPA;
    } else {
        // se 'M' não for apertado a tela permanece a mesma
        return **tela;
    }
}

EstadoTela telaMapa(EstadoTela **tela){
    DrawText("MAPA MPAAP MAPA", 100, 200, 20, BLACK);
    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_TAB))
    {
        return TELA_JOGO;
    } else {
        // se 'M' ou Tab não forem apertados a tela permanece a mesma
        return **tela;
    }
}