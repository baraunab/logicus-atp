#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
#include "telas.h"
#include "salas.h"

// Struct local para facilitar a criação dos botões
typedef struct {
    Rectangle area;
    EstadoTela telaDestino;
    const char *nome;
    Color cor;
} BotaoNoMapa;

EstadoTela telaMapa(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA) {
    
    // Definição das 5 fases
    static BotaoNoMapa fases[] = {
        // Posição X, Y, Largura, Altura - Destino - Texto - Cor
        { { 350, 400, 100, 50 }, TELA_ENTRADA,   "Entrada",   DARKGREEN },
        { { 350, 325, 100, 50 }, TELA_ENIGMA,    "Enigma das\nvariáveis",    PURPLE    },
        { { 350, 250, 100, 50 }, TELA_BAU,       "Bau\nestranho",       GOLD      },
        { { 350, 175, 100, 50 }, TELA_LABIRINTO, "Labirinto\ncondicional", DARKBLUE  },
        { { 350, 100, 100, 50 }, TELA_LACOS,     "Batalha dos\nlaços",   MAROON    }
    };

    EstadoTela proximaTela = *tela;

    // Desenho do fundo do mapa
    DrawRectangle(0, 0, LARGURA, ALTURA, RAYWHITE);
    DrawText("MAPA DA MASMORRA", LARGURA/2 - MeasureText("MAPA DA MASMORRA", 20)/2, 20, 20, BLACK);

    // Botões
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BLANK));
    
    // Armazena o tamanho original da fonte
    int tamanhoOriginal = GuiGetStyle(DEFAULT, TEXT_SIZE); 
    
    // Define novo tamanho para a fonte das áreas clicáveis do mapa
    GuiSetStyle(DEFAULT, TEXT_SIZE, 15);

    int qtd = sizeof(fases) / sizeof(fases[0]);
    
    for (int i = 0; i < qtd; i++) {
        // Fundo colorido
        DrawRectangleRec(fases[i].area, Fade(fases[i].cor, 0.4f));
        DrawRectangleLinesEx(fases[i].area, 2, fases[i].cor);

        // Botão invisível e Texto
        if (GuiButton(fases[i].area, fases[i].nome)) {
            proximaTela = fases[i].telaDestino;
        }
    }
    
    // Restaura o tamanho original da fonte para não afetar outras telas
    GuiSetStyle(DEFAULT, TEXT_SIZE, tamanhoOriginal);

    DrawText("Aperte 'M' para voltar ao Jogo", 10, ALTURA - 30, 15, GRAY);
    
    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_TAB)) {
        return TELA_JOGO;
    }

    return proximaTela;
}
