// se alterar, favor manter a ordem das includes de bibliotecas
#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "raygui.h"
#include "dialogo.h"
#include "recursos.h"
// telas.h obrigatoriamente há de estar após recursos.h, senão dá erro ao não saber o que é uma Texture2D
#include "telas.h"
#include "save.h"

// FOLHA DE ESTILO ---------------------------------------------------------------------------------------

    Color
        corStrPular = WHITE,
        corStrSalvamentos = WHITE;
    
// FIM DA FOLHA DE ESTILO --------------------------------------------------------------------------------


// VARIAVEIS DE CONTROLE ---------------------------------------------------------------------------------
     
    // int dialogoAtual; // inicia os indices de dialogos a serem lidos
    
    // usar laço for() para realizar a quebra de linhas
    
// FIM DAS VARIAVEIS DE CONTROLE -------------------------------------------------------------------------

EstadoTela telaJogo(EstadoTela *tela, Imagens *imagens, int LARGURA, int ALTURA) {
    
    // VARIÁVEIS USADAS NA LEITURA DE ARQUIVO DOS DIÁLOGOS -----------------------------------------------
    
    /* 
       declaração feita dentro do escopo da função para serem usadas 
       pelas outras funções referentes ao sistema de diálogos
       para evitar o erro de "initializer element is not constant" 
    */

    // caminho do arquivo do diálogo
    char *nomeArquivo = "./dialogos/dialogos.txt";
    int totalDialogos = 0;      // quantidade de dialogos que será definida em carregarDialogo
    bool esperaInput = true;    // verifica se ainda há inputs a serem recebidos na troca de dialogos
    
    // quantidade de linhas no arquivo
    int linhas = contaLinhas(nomeArquivo);
    
    // carrega os diálogos
    Dialogo *dialogos = carregarDialogo(nomeArquivo, linhas, &totalDialogos);
    
    // FIM DAS VARIÁVEIS DO DIÁLOGO ----------------------------------------------------------------------

    /* levando em consideração que:
        typedef struct Rectangle {
            float x;      // posição horizontal (eixo X)
            float y;      // posição vertical (eixo Y)
            float width;  // largura do retângulo
            float height; // altura do retângulo
        } Rectangle;
    */
    /* TESTANDO REDIMENSIONAMENTO DO SPRITE DE PERSONAGENS
    Rectangle src = { 0, 0, 100, 100};
    Rectangle dst = { 0, 0, 100, 100};
    Vector2 origin = {100, 100 };
    DrawTexturePro((*imagens).personagem[MAGA_COSTAS], src, dst, origin, PURPLE);
    */

    DrawTexture((*imagens).interface[IMAGEM_FUNDO], 0, 0, WHITE);
    Rectangle fundoDeTela = {0, ALTURA * 0.04, 800, 480};

    // calcula área de clique baseada no tamanho do texto
    int larguraPular = MeasureText("Pular", 12);
    int larguraSalvar = MeasureText("Salvar", 12);
    int espacoInterno = 12;
    int offset = 0;

    Rectangle areaPular = {((LARGURA / 2) - larguraPular - espacoInterno) - offset, 8, larguraPular, 12};
    Rectangle areaSalvamentos = {((LARGURA / 2) + espacoInterno) - offset, 8, larguraSalvar, 12};

    // desenha a palavra
    DrawText("Pular", areaPular.x, areaPular.y, 12, corStrPular);
    DrawText("Salvar", areaSalvamentos.x, areaSalvamentos.y, 12, corStrSalvamentos);


    if (dialogoAtual == 5) { DrawTexture((*imagens).personagem[MAGA_COSTAS], 90, 20, WHITE); }

    // CAIXA DE DIALOGO
    DrawRectangleRounded((Rectangle){LARGURA * 0.01, ALTURA * 0.65, LARGURA * 0.98, ALTURA * 0.33}, 0.3f, 10, (Color){0, 0, 0, (255)/1.5});

    // CAIXA DO NOME 
    DrawRectangleRounded((Rectangle){ LARGURA * 0.055, (ALTURA * 0.6) + 1, (LARGURA * 0.3) + 27, (ALTURA * 0.05) + 12}, 0.3f, 12, BLACK);

    // PULAR
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaPular)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrPular = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            printf("Pular\n");
            printf("Abrindo tela de input...\n");
            return TELA_INPUT;
        }

    } else {
        corStrPular = WHITE;
    }

    // SALVAMENTOS
    // detecta o mouse dentro da área do texto
    if (CheckCollisionPointRec(GetMousePosition(), areaSalvamentos)) {
        
        // mudar cor do texto ao passar o mouse por cima
        corStrSalvamentos = (Color){ 0, 255, 255, 255 };
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            saveEmUso->dialogoAtual = saveEmUso->dialogoAtual;
            salvarEstadoDeJogo(saveEmUso, slotAtivo);
        }

    } else {
        corStrSalvamentos = WHITE;
    }

    // se (clicar na tela) OU apertar Enter OU apertar Espaçamento
    if ((CheckCollisionPointRec(GetMousePosition(), fundoDeTela) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        // verifica o indicie do dialogo lido
        if (saveEmUso->dialogoAtual < totalDialogos - 1) {
            // incrementa ao receber uma interação
            dialogoAtual++;
            printf("%d\nClique na tela/Enter/Espaçamento\n", dialogoAtual);

            if (dialogoAtual == 4) { // se o siálogo for maior que 1
                // troca a imagem de fundo atual por essa do endereço
                imagens->interface[IMAGEM_FUNDO] = carregarImagem(IMAGEM_FUNDO, "./imagens/dungeon.jpeg");
            } else if (dialogoAtual == 6){
                imagens->interface[IMAGEM_FUNDO] = carregarImagem(IMAGEM_FUNDO, "./imagens/arte_splash.png");
            }

        } else {
            // verifica o fim da leitura do arquivo
            esperaInput = false;
        }
    }


    // TEXTO DO NOME
    DrawText(dialogos[saveEmUso->dialogoAtual].nome, (LARGURA * 0.06) + 5, (ALTURA * 0.6) + 8, 24, WHITE);
    
    // TEXTO DO DIÁLOGO
    DrawText(dialogos[saveEmUso->dialogoAtual].texto, LARGURA * 0.04, ALTURA * 0.7, 20, WHITE);
    
    // se não houver mais interação, confirma o fim da leitura do arquivo
    if (!esperaInput) {
        printf("fim da leitura do arquivo");
    }
    
    return *tela;
} 
