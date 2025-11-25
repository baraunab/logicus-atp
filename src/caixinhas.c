// caixinhas.c
#include "caixinhas.h"
#include "raygui.h"   // para GuiButton

#define LARGURA 800
#define ALTURA  480
// estrutura para representar cada caixinha/opção
void RodarDesafioCaixinhas(void) {
    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    static Color corMensagem = BLACK;

    static float yCaixas = 320;
    static float larguraCaixa = 150;
    static float alturaCaixa = 40;
    static float espacamento = 20;
    static float xInicial = 0;
// inicialização (executa apenas uma vez)( não é looping)
    if (!iniciado) {
        float totalLargura = 4*larguraCaixa + 3*espacamento;
        xInicial = (LARGURA - totalLargura)/2.0f;

        opcoes[0] = (Caixinha){
            .area = (Rectangle){ xInicial + 0*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "printf", .correta = 0, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "return", .correta = 0, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "if", .correta = 0, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "int", .correta = 1, .selecionada = 0
        };

        botaoVerificar = (Rectangle){ (LARGURA-200)/2.0f, 380, 200, 40 };
        iniciado = 1;
    }

    // essa parte aqui é executada toda vez (looping)
// essse ismouse é para clicar na caixa
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        for (int i = 0; i < 4; i++) {
            if (CheckCollisionPointRec(mouse, opcoes[i].area)) {
                for (int j = 0; j < 4; j++) opcoes[j].selecionada = (j == i);
            }
        }
    }

    // -------- DRAW (só desenha; a main já abriu o frame) --------
    DrawText("Complete o comando em C:", 40, 40, 28, BLACK);

    Rectangle caixaCodigo = { 120, 120, 560, 140 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// declarar uma variavel inteira chamada numero", xCodigo, yCodigo-30, 18, DARKGRAY);
    
    DrawText("____", xCodigo, yCodigo, 28, GRAY);
    DrawText(" numero = 10;", xCodigo+80, yCodigo, 28, BLACK);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo-2, yCodigo-2, 90, 32, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo, yCodigo, 28, DARKBLUE);
        }
    }
    // desenha as caixinhas/opções
    for (int i = 0; i < 4; i++) {
        Caixinha *c = &opcoes[i];
        Color fundo = c->selecionada ? YELLOW : LIGHTGRAY;
        Color borda = c->selecionada ? ORANGE : DARKGRAY;

        DrawRectangleRec(c->area, fundo);
        DrawRectangleLinesEx(c->area, 2, borda);

        int textWidth = MeasureText(c->texto, 20);
        float textX = c->area.x + (c->area.width - textWidth)/2.0f;
        float textY = c->area.y + (c->area.height - 20)/2.0f;
        DrawText(c->texto, (int)textX, (int)textY, 20, BLACK);
    }
    // desenha o botão de verificar
    if (GuiButton(botaoVerificar, "VERIFICAR")) {
        int indiceSelecionado = -1;
        for (int i = 0; i < 4; i++) if (opcoes[i].selecionada) { indiceSelecionado = i; break; }

        if (indiceSelecionado == -1) {
            mensagem = "Escolhe um comando primeiro.";
            corMensagem = RED;
        } else if (opcoes[indiceSelecionado].correta) {
            mensagem = "Perfeito! Resposta correta.";
            corMensagem = DARKGREEN;
        } else {
            mensagem = "Ta errado. Tenta de novo.";
            corMensagem = MAROON;
        }
    }
    // desenha a mensagem de feedback
    if (mensagem[0] != '\0') {
        DrawText(mensagem, 70, 440, 20, corMensagem);
    }
}
