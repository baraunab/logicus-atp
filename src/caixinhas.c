#include "raygui.h"
#include <stdbool.h>
#include <stdlib.h>

#include "telas.h"
#include "caixinhas.h"

#define LARGURA 800
#define ALTURA  480

// Função principal da tela do desafio das caixinhas
EstadoTela RodarDesafioCaixinhas(void) {
    // essas variáveis estáticas ficam salvas entre um frame e outro
    static int iniciado = 0;

    static Caixinha opcoes[4];      // as 4 caixinhas de opção
    static Rectangle botaoReset;    // botão "TENTE NOVAMENTE"

    static const char *mensagem = "";  // texto de feedback (acertou/errou)
    static Color corMensagem = WHITE;  // cor do texto de feedback

    static int  indiceSelecionado  = -1;  // qual opção foi clicada
    static int  indiceCorreto      = 3;   // índice da opção correta (int)
    static bool respostaVerificada = false; // se já mostrou o resultado

    // variáveis de efeito visual
    static float fadeCorreto = 0.0f;   // controla o aparecimento do "int"
    static float flashTimer  = 0.0f;   // controla o flash verde de acerto
    static float shakeTimer  = 0.0f;   // controla o tremor da opção errada

    // esse bloco roda só na primeira vez que a tela é aberta
    if (!iniciado) {

        // tamanho e posicionamento das caixinhas na tela
        float larguraCaixa = 140;
        float alturaCaixa  = 45;
        float espacamento  = 22;

        float totalLargura = 2 * larguraCaixa + espacamento;
        float xEsquerda    = (LARGURA - totalLargura) / 2.0f;
        float yTopo        = 255.0f;

        // distribui as 4 caixinhas em uma grade 2x2
        for (int i = 0; i < 4; i++) {
            int linha  = i / 2;
            int coluna = i % 2;

            float x = xEsquerda + coluna * (larguraCaixa + espacamento);
            float y = yTopo     + linha  * (alturaCaixa  + 18);

            opcoes[i].area        = (Rectangle){ x, y, larguraCaixa, alturaCaixa };
            opcoes[i].selecionada = 0;
            opcoes[i].correta     = 0;
        }

        // textos das opções
        opcoes[0].texto   = "printf";
        opcoes[1].texto   = "return";
        opcoes[2].texto   = "if";
        opcoes[3].texto   = "int";
        opcoes[3].correta = 1;  // marca "int" como opção correta

        // botão de tentar novamente
        botaoReset = (Rectangle){ (LARGURA - 200)/2.0f, 410, 200, 34 };

        iniciado = 1;
    }

    // aqui tratamos o clique do mouse nas caixinhas
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 m = GetMousePosition();

        for (int i = 0; i < 4; i++) {
            if (CheckCollisionPointRec(m, opcoes[i].area)) {

                // toda vez que clicar de novo, limpamos os efeitos antigos
                mensagem    = "";
                fadeCorreto = 0.0f;
                flashTimer  = 0.0f;
                shakeTimer  = 0.0f;

                indiceSelecionado = i;

                // garante que só uma opção fica marcada como selecionada
                for (int j = 0; j < 4; j++)
                    opcoes[j].selecionada = 0;

                opcoes[i].selecionada = 1;

                // assim que clica, já considera que a resposta foi "verificada"
                respostaVerificada = true;

                // se acertou a opção correta
                if (indiceSelecionado == indiceCorreto) {
                    mensagem    = "Acertou! Boa!";
                    corMensagem = GREEN;
                    fadeCorreto = 0.0f;
                    flashTimer  = 0.7f;  // ativa flash de acerto
                } else {
                    // se errou
                    mensagem    = "Errou. Tenta outra.";
                    corMensagem = RED;
                    shakeTimer  = 0.4f;  // ativa tremor na opção errada
                }
            }
        }
    }

    // começa o desenho na tela
    BeginDrawing();
    ClearBackground((Color){8, 10, 30, 255});

    // barra de título
    DrawRectangle(0, 0, LARGURA, 60, (Color){18, 22, 60, 255});
    DrawText("DESAFIO DAS CAIXINHAS", 140, 18, 32, RAYWHITE);

    // painel onde fica o código de exemplo
    Rectangle painel = (Rectangle){ 80, 80, 640, 130 };
    DrawRectangleRounded(painel, 0.08f, 8, (Color){235,235,245,255});
    DrawRectangleRoundedLines(painel, 0.08f, 8, (Color){180,180,210,255});

    DrawText("// declarar uma variavel inteira chamada numero",
             100, 95, 20, (Color){120,120,150,255});

    DrawText("tipo", 100, 135, 28, (Color){130,130,130,255});
    DrawText("____ numero = 10;", 160, 135, 28, (Color){10,10,10,255});

    // verifica se o jogador acertou a opção correta
    bool acertou = (respostaVerificada && indiceSelecionado == indiceCorreto);

    // quando acerta, o "int" aparece no código com um efeito de fade
    if (acertou) {
        fadeCorreto += 0.05f;
        if (fadeCorreto > 1.0f) fadeCorreto = 1.0f;
        Color c = (Color){0,200,255,(unsigned char)(fadeCorreto*255)};
        DrawText("int", 160, 135, 28, c);
    }

    // desenha as 4 caixinhas de opção
    for (int i = 0; i < 4; i++) {
        Rectangle r = opcoes[i].area;

        // se errou, a opção escolhida treme um pouco
        if (shakeTimer > 0 && respostaVerificada && !acertou && indiceSelecionado == i) {
            r.x += GetRandomValue(-4, 4);
            r.y += GetRandomValue(-2, 2);
        }

        bool hover = CheckCollisionPointRec(GetMousePosition(), r);

        Color fundo = (Color){190,190,200,255};
        Color borda = (Color){40,40,60,255};
        Color texto = (Color){15,15,25,255};

        // cor quando está selecionada (antes de verificar)
        if (opcoes[i].selecionada && !respostaVerificada) fundo = (Color){255,230,120,255};

        // cor quando passa o mouse por cima (antes de verificar)
        if (hover && !respostaVerificada) fundo = (Color){220,220,230,255};

        // se errou, a opção errada escolhida fica vermelha
        if (respostaVerificada && !acertou && indiceSelecionado == i) {
            fundo = (Color){230,90,90,255};
            texto = RAYWHITE;
        }

        DrawRectangleRounded(r, 0.20f, 6, fundo);
        DrawRectangleRoundedLines(r, 0.20f, 6, borda);

        int tw = MeasureText(opcoes[i].texto, 22);
        DrawText(opcoes[i].texto, r.x + (r.width - tw)/2, r.y + 10, 22, texto);
    }

    // mostra a mensagem de "acertou" ou "errou" embaixo
    if (mensagem && mensagem[0] != '\0')
        DrawText(mensagem, 80, ALTURA - 40, 24, corMensagem);

    // botão "TENTAR NOVAMENTE" aparece só depois de já ter verificado
    if (respostaVerificada) {

        // diminui a fonte só desse botão
        GuiSetStyle(DEFAULT, TEXT_SIZE, 11);

        if (GuiButton(botaoReset, "TENTE NOVAMENTE")) {
            // reseta tudo para jogar de novo
            respostaVerificada = false;
            mensagem    = "";
            fadeCorreto = 0.0f;
            flashTimer  = 0.0f;
            shakeTimer  = 0.0f;
            indiceSelecionado = -1;

            for (int i = 0; i < 4; i++)
                opcoes[i].selecionada = 0;
        }

        // volta o tamanho de fonte padrão para não afetar o resto
        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
    }

    // diminui o tempo do efeito de tremor até zerar
    if (shakeTimer > 0) {
        shakeTimer -= 0.05f;
        if (shakeTimer < 0) shakeTimer = 0;
    }

    // controla o efeito de flash verde quando acerta
    if (flashTimer > 0) {
        int alpha = (int)(flashTimer * 200);
        DrawRectangle(0,0,LARGURA,ALTURA,(Color){0,255,80,(unsigned char)alpha});
        flashTimer -= 0.04f;
        if (flashTimer < 0) flashTimer = 0;
    }

    // finaliza o desenho da tela
    EndDrawing();
    return TELA_CAIXINHAS;
}
