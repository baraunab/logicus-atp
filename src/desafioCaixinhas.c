// caixinhas.c
#include "raygui.h"   // para GuiButton
#include "raylib.h"

#include <stdbool.h>

#include "recursos.h"
#include "telas.h"
#include "caixinhas.h"
#include "grimorio.h"

#define LARGURA 800
#define ALTURA  480

Color corRoxo = (Color){ 65, 22, 94, 255 };
Color corRoxoEscuro = (Color){ 42, 0, 70, 255 };

// estrutura para representar cada caixinha/opção
EstadoTela desafioCaixinhas1(void) {
	
    Color corRosa = (Color){ 153, 97, 137, 255 };
    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    Color corMensagem = corRosa;

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
            .texto = "<stdlib.h>", .correta = 0, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "<stdio.h>", .correta = 1, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "<string.h>", .correta = 0, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "<stdbool.h>", .correta = 0, .selecionada = 0
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
    
    ClearBackground(corRoxo);
   
    // DESAFIO 1: SELECAO DA BIBLIOTECA CORRETA

    // -------- DRAW (só desenha; a main já abriu o frame) --------
    DrawText("Desafio 1: Bibliotecas", 40, 40, 28, corRosa);

    Rectangle caixaCodigo = { 120, 120, 560, 140 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// chame a biblioteca correta para entrada e saida de dados", xCodigo, yCodigo-30, 18, DARKGRAY);
    
    DrawText("#include", xCodigo, yCodigo, 28, corRoxo);
    DrawText(" <____>", xCodigo+120, yCodigo, 28, corRoxo);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo+120, yCodigo-2, 95, 32, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo+120, yCodigo, 28, DARKPURPLE);
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
    
	if (IsKeyPressed(KEY_I)) {
		return TELA_GRIMORIO; 
	}		
	
    return TELA_DESAFIO1;
}

EstadoTela desafioCaixinhas2() {
	
    Color corRosa = (Color){ 153, 97, 137, 255 };
    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    Color corMensagem = corRosa;

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
            .texto = "texto;", .correta = 0, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "texto->10;", .correta = 0, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "int;", .correta = 0, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "texto[10];", .correta = 1, .selecionada = 0
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
    
    ClearBackground(corRoxo);

    // -------- DRAW (só desenha; a main já abriu o frame) --------
    DrawText("Desafio 2: Declaração de variáveis", 40, 40, 28, WHITE);

    Rectangle caixaCodigo = { 120, 120, 560, 140 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// declare uma variável de caracteres", xCodigo, yCodigo-30, 18, DARKGRAY);
    
    DrawText("char ", xCodigo, yCodigo, 28, corRoxo);
    DrawText("  _____", xCodigo+60, yCodigo, 28, corRoxo);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo+78, yCodigo-2, 95, 32, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo+78, yCodigo, 28, DARKPURPLE);
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
    
	if (IsKeyPressed(KEY_I)) {
		return TELA_GRIMORIO; 
	}		
	
    return TELA_DESAFIO2;
}

EstadoTela desafioCaixinhas3() {

    Color corRosa = (Color){ 153, 97, 137, 255 };

    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    Color corMensagem = corRosa;

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
            .texto = "\%f", .correta = 1, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "\%d", .correta = 0, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "\%p", .correta = 0, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "\%c", .correta = 0, .selecionada = 0
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

    ClearBackground(corRoxo);

    // -------- DRAW (só desenha; a main já abriu o frame) --------
    DrawText("Desafio 3: Entrada de dados", 40, 40, 28, WHITE);

    Rectangle caixaCodigo = { 120, 120, 560, 140 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// Considere a variável declarada. \n// Imprima ela usando o formatador equivalente ", xCodigo-20, yCodigo-30, 18, DARKGRAY);
    
    DrawText("float poderDasSombras = 1000;", xCodigo, yCodigo+15, 20, corRoxo);

    DrawText("printf(\"Poder Sombrio: ___ \", poderDasSombras)", xCodigo, yCodigo+40, 20, corRoxo);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo+238, yCodigo+40, 40, 32, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo+242, yCodigo+40, 20, DARKPURPLE);
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
    
	if (IsKeyPressed(KEY_I)) {
		return TELA_GRIMORIO; 
	}		
	
    return TELA_DESAFIO3;
}

EstadoTela desafioCaixinhas4() {
	
    Color corRosa = (Color){ 153, 97, 137, 255 };
    
    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    Color corMensagem = corRosa;

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
            .texto = "vida;", .correta = 0, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "\"Morto\";", .correta = 0, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "false;", .correta = 1, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "if;", .correta = 0, .selecionada = 0
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

    ClearBackground(corRoxo);

    // -------- DRAW (só desenha; a main já abriu o frame) --------

    DrawText("Desafio 4: Condicional", 40, 40, 28, WHITE);
    
    Rectangle caixaCodigo = { 120, 120, 560, 150 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// Considere a condição. \n// Retorne o variavel correta.", xCodigo-20, yCodigo-30, 18, DARKGRAY);
    
    DrawText("bool estadoVivo = true;", xCodigo, yCodigo+15, 20, corRoxo);

    DrawText("if (vida == 0) {", xCodigo, yCodigo+40, 20, corRoxo);
    DrawText("return  ____ ", xCodigo+25, yCodigo+61, 20, corRoxo);
    DrawText("}", xCodigo, yCodigo+81, 20, corRoxo);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo+104, yCodigo+61, 55, 32, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo+104, yCodigo+61, 20, DARKPURPLE);
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
    
	if (IsKeyPressed(KEY_I)) {
		return TELA_GRIMORIO; 
	}		
	
    return TELA_DESAFIO4;
}

EstadoTela desafioCaixinhas5() {
    	
    Color corRosa = (Color){ 153, 97, 137, 255 };
    
    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    Color corMensagem = corRosa;

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
            .texto = "i < 15;", .correta = 1, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "i != 10;", .correta = 0, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "i == 20;", .correta = 0, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "i > 0;", .correta = 0, .selecionada = 0
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

    ClearBackground(corRoxo);
    
     DrawText("Desafio 5: Laço de Repetição", 40, 40, 28, WHITE);
    
    Rectangle caixaCodigo = { 120, 120, 560, 150 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// Considere o laço de repetição. \n// Defina quantas vezes ele irá se repetir.", xCodigo-20, yCodigo-30, 18, DARKGRAY);
    
    DrawText("for (int i = 0; ______ i++) {", xCodigo, yCodigo+15, 20, corRoxo);
    DrawText("printf(\"Ataque %d\", i + 1);", xCodigo+25, yCodigo+40, 20, corRoxo);
    DrawText("}", xCodigo, yCodigo+61, 20, corRoxo);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo+138, yCodigo+15, 70, 20, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo+144, yCodigo+15, 20, DARKPURPLE);
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
    
	if (IsKeyPressed(KEY_I)) {
		return TELA_GRIMORIO; 
	}		
	
    return TELA_DESAFIO5;
}

// desafioCaixinhas
EstadoTela desafioCaixinhasS2() {
	
    Color corRosa = (Color){ 153, 97, 137, 255 };
    
    static int iniciado = 0;
    static Caixinha opcoes[4];
    static Rectangle botaoVerificar;
    static const char *mensagem = "";
    Color corMensagem = corRosa;

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
            .texto = "float", .correta = 0, .selecionada = 0
        };

        opcoes[1] = (Caixinha){
            .area = (Rectangle){ xInicial + 1*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "int", .correta = 1, .selecionada = 0
        };

        opcoes[2] = (Caixinha){
            .area = (Rectangle){ xInicial + 2*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "false", .correta = 0, .selecionada = 0
        };

        opcoes[3] = (Caixinha){
            .area = (Rectangle){ xInicial + 3*(larguraCaixa+espacamento), yCaixas, larguraCaixa, alturaCaixa },
            .texto = "for", .correta = 0, .selecionada = 0
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

    ClearBackground(corRoxo);

    // -------- DRAW (só desenha; a main já abriu o frame) --------

    Rectangle caixaCodigo = { 120, 120, 560, 150 };
    DrawRectangleRec(caixaCodigo, (Color){230,230,230,255});
    DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

    int xCodigo = 150;
    int yCodigo = 160;
    // linha de código com espaço para a caixinha
    DrawText("// Determine o tipo das variáveis a seguir.", xCodigo-20, yCodigo-30, 18, DARKGRAY);
    
    DrawText("main () {", xCodigo, yCodigo+15, 20, corRoxo);

    DrawText("__ a = 5, b = 7;", xCodigo+25, yCodigo+40, 20, corRoxo);
    DrawText("}", xCodigo, yCodigo+61, 20, corRoxo);

    for (int i = 0; i < 4; i++) {
        if (opcoes[i].selecionada) {
            DrawRectangle(xCodigo+25, yCodigo+40, 55, 32, (Color){230,230,230,255});
            DrawText(opcoes[i].texto, xCodigo+22, yCodigo+40, 20, DARKPURPLE);
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
    
	if (IsKeyPressed(KEY_ENTER)) {
		return TELA_BAU; 
	}		
	
    return TELA_DESAFIOS2;
}
