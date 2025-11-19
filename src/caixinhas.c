    // main.c
    // versão de teste do Logicus no meu lindo fork

    #include <stdio.h>

    // aqui eu ativo a implementação da raygui
    #define RAYGUI_IMPLEMENTATION

    // bibliotecas da raylib e raygui
    #include "raylib.h"
    #include "raygui.h"

    // por enquanto não vou usar save.h, dialogo.h, recursos.h

    // tamanho da janela do jogo
    #define LARGURA 800
    #define ALTURA  480

    // struct das caixinhas (igual a ideia do Duolingo que a barauna aprovou )
    typedef struct {
        Rectangle area;      // posição e tamanho da caixinha na tela
        const char *texto;   // texto que aparece dentro da caixinha
        int correta;         // 1 se essa for a opção correta, 0 se for errada
        int selecionada;     // 1 se o jogador clicou nessa, 0 se não
    } Caixinha;

    int main(void) {
        // inicializa a janela principal do Logicus
        InitWindow(LARGURA, ALTURA, "Logicus;");
        SetTargetFPS(60);

        // aqui eu preparo as caixinhas das opções do comando em C
        // objetivo: completar "____ numero = 10;"
        Caixinha opcoes[4] = {0};// ESSE AQUI É A STRUCT DENTRO DO TYPEDEF, NOMEEI DE OPÇÕES COMO OPÇÕES.ALGUMA COISA 

        float yCaixas      = 320;
        float larguraCaixa = 150;
        float alturaCaixa  = 40;
        float espacamento  = 20;

        // centralizar as 4 caixinhas
        float totalLargura = 4*larguraCaixa + 3*espacamento;
        float xInicial     = (LARGURA - totalLargura) / 2.0f;

        // opção 0 //Essa é a struct que vai guardar as informações de cada caixinha
        opcoes[0].area        = (Rectangle){ xInicial + 0*(larguraCaixa + espacamento), yCaixas, larguraCaixa, alturaCaixa };
        opcoes[0].texto       = "printf";
        opcoes[0].correta     = 0;
        opcoes[0].selecionada = 0;

        // opção 1//essa é a segunda caixinha
        opcoes[1].area        = (Rectangle){ xInicial + 1*(larguraCaixa + espacamento), yCaixas, larguraCaixa, alturaCaixa };
        opcoes[1].texto       = "return";
        opcoes[1].correta     = 0;
        opcoes[1].selecionada = 0;

        // opção 2//essa é a terceira caixinha
        opcoes[2].area        = (Rectangle){ xInicial + 2*(larguraCaixa + espacamento), yCaixas, larguraCaixa, alturaCaixa };
        opcoes[2].texto       = "if";
        opcoes[2].correta     = 0;
        opcoes[2].selecionada = 0;

        // opção 3 – essa é a correta//essa é a quarta caixinha
        opcoes[3].area        = (Rectangle){ xInicial + 3*(larguraCaixa + espacamento), yCaixas, larguraCaixa, alturaCaixa };
        opcoes[3].texto       = "int";
        opcoes[3].correta     = 1;
        opcoes[3].selecionada = 0;

        // mensagem de feedback pro jogador depois que ele clica em VERIFICAR
         char *mensagem   = "";//aqui eu criei um ponteiro de char que vai guardar a mensagem que aparece depois que o jogador clicar em verificar
        Color       corMensagem = BLACK;

        // botão de verificar (gui)//esse botao foi feito com a raygui, verifiquei na doc mas tem que confirmar com o kinas
        Rectangle botaoVerificar = { (LARGURA - 200)/2.0f, 380, 200, 40 };

        // loop principal do jogo //kinan disse que isso era pra ser na main, verifiacar com ele 
        while (!WindowShouldClose()) {

            // entrada de mouse: clique nas caixinhas//isso aqui foi feito com a biblioteca raylib(tinha na documentação);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();

                for (int i = 0; i < 4; i++) {
                    if (CheckCollisionPointRec(mouse, opcoes[i].area)) {
                        // se clicou nessa, marco essa como selecionada
                        // e desmarco as outras (só pode uma por vez)
                        for (int j = 0; j < 4; j++) {
                            opcoes[j].selecionada = (j == i) ? 1 : 0;
                        }
                    }
                }
            }
            // desenho da tela//isso aqui foi feito com a biblioteca raylib(tinha na documentação);
            BeginDrawing();
            ClearBackground(RAYWHITE);//confirmar depois se isso aqui realmente é a cor 

            // título da tela
            DrawText("Complete o comando em C:", 40, 40, 28, BLACK);

            // caixinha estilo editor de código//isso aqui foi feito com a biblioteca raylib(tinha na documentação);
            Rectangle caixaCodigo = { 120, 120, 560, 140 };
            DrawRectangleRec(caixaCodigo, (Color){230, 230, 230, 255});
            DrawRectangleLinesEx(caixaCodigo, 2, DARKGRAY);

            int xCodigo = 150;
            int yCodigo = 160;

            // comentário explicando o que esse comando faz
            DrawText("// declarar uma variavel inteira chamada numero", xCodigo, yCodigo - 30, 18, DARKGRAY);

            // linha com o buraco para o tipo
            DrawText("____", xCodigo, yCodigo, 28, GRAY);
            DrawText(" numero = 10;", xCodigo + 80, yCodigo, 28, BLACK);

            // se alguma opção estiver selecionada, desenho ela por cima do underline
            for (int i = 0; i < 4; i++) {
                if (opcoes[i].selecionada) {//esse aqui tem que ser a opção que o usuario clicou 
                    DrawText(opcoes[i].texto, xCodigo, yCodigo, 28, DARKBLUE);
                }
            }

            // desenhando as caixinhas de opções
            for (int i = 0; i < 4; i++) {//isso aqui foi feito com a biblioteca raylib(tinha na documentação);
                Caixinha *c = &opcoes[i];

                Color fundo = LIGHTGRAY;//depois alinhar com os meninos pra ver se vai ser essa cor mesmo 
                Color borda = DARKGRAY;//depois alinhar com os meninos pra ver se vai ser essa cor mesmo 
                Color texto = BLACK;//depois alinhar com os meninos pra ver se vai ser essa cor mesmo 

                if (c->selecionada) {//isso aqui é pra quando o usuario clicar na caixinha
                    fundo = YELLOW;
                    borda = ORANGE;
                }

                DrawRectangleRec(c->area, fundo);//desenha o fundo da caixinha
                DrawRectangleLinesEx(c->area, 2, borda);//desenha a borda da caixinha

                int textWidth = MeasureText(c->texto, 20);//medir a largura do texto pra centralizar dentro da caixinha
                float textX = c->area.x + (c->area.width - textWidth)/2.0f;//centraliza o texto na caixinha
                float textY = c->area.y + (c->area.height - 20)/2.0f;//centraliza o texto na caixinha

                DrawText(c->texto, (int)textX, (int)textY, 20, texto);
            }

            // botão VERIFICAR com raygui
            if (GuiButton(botaoVerificar, "VERIFICAR")) {
                int indiceSelecionado = -1;

                for (int i = 0; i < 4; i++) {
                    if (opcoes[i].selecionada) {
                        indiceSelecionado = i;
                        break;
                    }
                }

                if (indiceSelecionado == -1) {
                    mensagem    = "Escolhe um comando primeiro.";
                    corMensagem = RED;
                } else if (opcoes[indiceSelecionado].correta) {
                    mensagem    = "Perfeito! vc é o mago dos magos da prr toda.";
                    corMensagem = DARKGREEN;
                } else {
                    mensagem    = "ta errado ein, a princesa vai ser pega pelo mago c.";
                    corMensagem = MAROON;
                }
            }

            // mensagem de feedback na parte de baixo
            if (mensagem[0] != '\0') {
                DrawText(mensagem, 70, 440, 20, corMensagem);
            }

            EndDrawing();//a funcao disso é finalizar o desenho na tela
        }

        CloseWindow();//a funcao disso é fechar a janela do jogo
        return 0;
    }
