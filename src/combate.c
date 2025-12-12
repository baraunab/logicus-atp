#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "raygui.h"
#include "combate.h"

// Cores
#define COR_HP_ALTO     CLITERAL(Color){ 112, 248, 168, 255 }
#define COR_HP_MEDIO    CLITERAL(Color){ 248, 224, 56, 255 }
#define COR_HP_BAIXO    CLITERAL(Color){ 248, 88, 56, 255 }
#define COR_PAINEL      CLITERAL(Color){ 240, 240, 240, 255 }
#define COR_BORDA       CLITERAL(Color){ 60, 60, 60, 255 }
#define COR_TERMINAL    CLITERAL(Color){ 20, 20, 30, 255 }

static SistemaCombate batalha;
static bool editMode = true;
// Guardamos uma cópia dos dados originais para poder sortear os ataques
static DadosCombateInimigo dadosInimigoAtual; 

// --- FUNÇÕES AUXILIARES ---

bool ContemTexto(const char *texto, const char *palavra) {
    return (strstr(texto, palavra) != NULL); 
}

// Inicializa o combate
void IniciarCombate(DadosCombateInimigo dados) {
    // Copia dados do inimigo
    dadosInimigoAtual = dados; // Salva para consultar os ataques depois
    strcpy(batalha.nomeInimigo, dados.nome);
    batalha.vidaInimigoMax = dados.vidaMax;
    batalha.vidaInimigoAtual = dados.vidaMax;
    
    // Configura Jogador (Padrão)
    batalha.vidaJogadorMax = 100;
    batalha.vidaJogadorAtual = 100;

    // Adiciona feitiço básico se o grimório estiver vazio
    if (batalha.qtdFeiticos == 0) {
        AdicionarFeiticoJogador("pancada();", 10, "O grimório ainda serve de porrete!");
    	AdicionarFeiticoJogador("for(i = 1, i != 0, misseis magicos);", 20, "Chuva de misseis magicos!");
		AdicionarFeiticoJogador("if(inimigoVivo){aniquilar};", 30, "Sinta a fúria do Grimorio");
	}

    // Estado Inicial
    batalha.faseAtual = FASE_INIMIGO_PREPARA;
    batalha.timerAnimacao = 0;
    strcpy(batalha.bufferInput, "");
    strcpy(batalha.logTerminal, "Use o Grimório do Herói para superar este desafio!");
}

// Permite ensinar novos ataques ao jogador antes ou durante o jogo
void AdicionarFeiticoJogador(const char *comando, int dano, const char *desc) {
    if (batalha.qtdFeiticos < MAX_FEITICOS_JOGADOR) {
        FeiticoJogador f;
        strcpy(f.comando, comando);
        strcpy(f.descricao, desc);
        f.dano = dano;
        batalha.grimorio[batalha.qtdFeiticos] = f;
        batalha.qtdFeiticos++;
    }
}

void DesenharStatusBox(int x, int y, char *nome, int hpAtual, int hpMax, bool isPlayer) {
    DrawRectangleRounded((Rectangle){x, y, 260, 70}, 0.2f, 10, Fade(COR_PAINEL, 0.9f));
    DrawRectangleRoundedLines((Rectangle){x, y, 260, 70}, 0.2f, 10, COR_BORDA);

    DrawText(nome, x + 15, y + 10, 20, BLACK);
    
    DrawRectangle(x + 40, y + 40, 200, 15, LIGHTGRAY);
    DrawRectangleLines(x + 40, y + 40, 200, 15, GRAY);

    float porcento = (float)hpAtual / hpMax;
    Color corHp = COR_HP_ALTO;
    if (porcento < 0.5f) corHp = COR_HP_MEDIO;
    if (porcento < 0.2f) corHp = COR_HP_BAIXO;
    if (porcento < 0) porcento = 0;

    DrawRectangle(x + 40, y + 40, (int)(200 * porcento), 15, corHp);

    DrawText("VIDA", x + 5, y + 42, 8, RED); 
    
    if (isPlayer) {
        DrawText(TextFormat("%d / %d", hpAtual, hpMax), x + 140, y + 58, 10, DARKGRAY);
    }
}

EstadoTela AtualizarCombate(Imagens *imagens, int LARGURA, int ALTURA) {
    
    batalha.timerAnimacao += GetFrameTime();

    // --- LÓGICA ---
    switch (batalha.faseAtual) {
        
        case FASE_INIMIGO_PREPARA:
            if (batalha.timerAnimacao > 1.5f) {
                // Sorteia um ataque da lista personalizada do inimigo
                if (dadosInimigoAtual.qtdAtaques > 0) {
                    int indexAtaques = GetRandomValue(0, dadosInimigoAtual.qtdAtaques - 1);
                    batalha.ataqueAtualInimigo = dadosInimigoAtual.ataques[indexAtaques];
                    
                    // Atualiza mensagens
                    strcpy(batalha.declaracaoCodigoInimigo, batalha.ataqueAtualInimigo.codigoVisual);
                    strcpy(batalha.logTerminal, batalha.ataqueAtualInimigo.mensagemAviso);
                }
                
                strcpy(batalha.bufferInput, "");
                batalha.faseAtual = FASE_JOGADOR_DEFESA;
                batalha.timerAnimacao = 0;
            }
            break;

        case FASE_JOGADOR_DEFESA:
            if (IsKeyPressed(KEY_ENTER)) {
                bool sucesso = false;
                TipoAtaqueInimigo tipo = batalha.ataqueAtualInimigo.tipo;

                // Validação Genérica baseada no TIPO
                if (tipo == ATAQUE_FISICO) {
                    if (ContemTexto(batalha.bufferInput, "printf") && (ContemTexto(batalha.bufferInput, "(escudo);") || ContemTexto(batalha.bufferInput, "(defesa);"))){
						sucesso = true;
					}
                } 
                else if (tipo == ATAQUE_LOOP) {
                    if (ContemTexto(batalha.bufferInput, "break")){
						sucesso = true;
					}
                }
                else if (tipo == ATAQUE_MAGICO) {
                    if (ContemTexto(batalha.bufferInput, "conjurar") && (ContemTexto(batalha.bufferInput, "(contramagia)") || ContemTexto(batalha.bufferInput, "(anular)"))){
						sucesso = true;
					} 
                }

                if (sucesso) {
                    strcpy(batalha.logTerminal, "SUCESSO: Sintaxe correta. Bloqueado!");
                } else {
                    int dano = batalha.ataqueAtualInimigo.danoSeFalhar;
                    batalha.vidaJogadorAtual -= dano;
                    sprintf(batalha.logTerminal, "ERRO DE SINTAXE: Voce tomou %d de dano.", dano);
                }

                batalha.faseAtual = FASE_RESULTADO_DEFESA;
                batalha.timerAnimacao = 0;
            }
            break;

        case FASE_RESULTADO_DEFESA:
            if (batalha.timerAnimacao > 2.0f) {
                if (batalha.vidaJogadorAtual <= 0) {
                    batalha.faseAtual = FASE_DERROTA;
                } else {
                    batalha.faseAtual = FASE_JOGADOR_ACAO;
                    strcpy(batalha.bufferInput, "");
                    strcpy(batalha.logTerminal, "SUA VEZ! Digite uma funcao de ataque.");
                }
                batalha.timerAnimacao = 0;
            }
            break;

        case FASE_JOGADOR_ACAO:
            if (IsKeyPressed(KEY_ENTER)) {
                bool atacou = false;
                
                // Percorre o Grimório do jogador para ver se o input CONTÉM algum comando conhecido
                for (int i = 0; i < batalha.qtdFeiticos; i++) {
                    
                    // MUDANÇA: Usando ContemTexto em vez de strcmp
                    if (ContemTexto(batalha.bufferInput, batalha.grimorio[i].comando)) {
                        
                        int dano = batalha.grimorio[i].dano;
                        batalha.vidaInimigoAtual -= dano;
                        
                        sprintf(batalha.logTerminal, "EXECUCAO: %s (%d dano)", batalha.grimorio[i].descricao, dano);
                        atacou = true;
                        break; // Para de procurar assim que achar um match
                    }
                }

                if (!atacou) {
                    strcpy(batalha.logTerminal, "RUNTIME ERROR: Funcao nao encontrada.");
                }

                batalha.faseAtual = FASE_RESULTADO_ACAO;
                batalha.timerAnimacao = 0;
            }
            break;

        case FASE_RESULTADO_ACAO:
            if (batalha.timerAnimacao > 2.0f) {
                if (batalha.vidaInimigoAtual <= 0) {
                    batalha.faseAtual = FASE_VITORIA;
                } else {
                    batalha.faseAtual = FASE_INIMIGO_PREPARA;
                    strcpy(batalha.logTerminal, "Inimigo esta compilando novo ataque...");
                }
                batalha.timerAnimacao = 0;
            }
            break;

        case FASE_VITORIA:
            if (batalha.timerAnimacao > 3.0f){
            	DrawTexture((*imagens).cenario[CREDITOS_FINAL], LARGURA * 0, ALTURA * 0, WHITE);
			} 
            break;

        case FASE_DERROTA:
            if (batalha.timerAnimacao > 3.0f) return TELA_MENU;
            break;
    }

    //DESENHO
    DrawRectangle(0, 0, LARGURA, ALTURA, RAYWHITE);
    
    // Sombras
    DrawEllipse(LARGURA - 150, 220, 100, 30, Fade(LIGHTGRAY, 0.5f));
    DrawEllipse(180, 350, 120, 40, Fade(LIGHTGRAY, 0.5f));

    // Sprites
    //DrawRectangle(LARGURA - 200, 80, 100, 100, MAROON); 
    //DrawRectangle(130, 210, 100, 100, BLUE);
    DrawTexture((*imagens).personagem[LORDC_COMBATE], LARGURA * 0.67, ALTURA * 0, WHITE);
    DrawTexture((*imagens).personagem[BECKY2], LARGURA * 0, ALTURA * 0, WHITE);

    // Painéis
    DesenharStatusBox(50, 30, batalha.nomeInimigo, batalha.vidaInimigoAtual, batalha.vidaInimigoMax, false);
    DesenharStatusBox(LARGURA - 290, 250, "Becky", batalha.vidaJogadorAtual, batalha.vidaJogadorMax, true);

    // Balão Inimigo
    if (batalha.faseAtual == FASE_INIMIGO_PREPARA || batalha.faseAtual == FASE_JOGADOR_DEFESA) {
        DrawRectangleRounded((Rectangle){LARGURA - 380, 80, 170, 60}, 0.5f, 0, BLACK);
        DrawTriangle((Vector2){LARGURA - 210, 110}, (Vector2){LARGURA - 200, 100}, (Vector2){LARGURA - 210, 90}, BLACK); 
        DrawText("// CÓDIGO INIMIGO:", LARGURA - 370, 90, 10, GREEN);
        DrawText(batalha.declaracaoCodigoInimigo, LARGURA - 370, 105, 18, GREEN);
    }

    // Terminal
    int yConsole = ALTURA - 140;
    DrawRectangle(0, yConsole, LARGURA, 140, COR_TERMINAL);
    DrawRectangleLines(0, yConsole, LARGURA, 140, COR_BORDA);
    DrawRectangle(0, yConsole - 20, LARGURA, 20, COR_BORDA);
    DrawText(" TERMINAL DE BATALHA - gcc logicus.c", 10, yConsole - 15, 10, WHITE);

    if (batalha.faseAtual == FASE_JOGADOR_DEFESA || batalha.faseAtual == FASE_JOGADOR_ACAO) {
        if (batalha.faseAtual == FASE_JOGADOR_DEFESA) 
            DrawText("  Escreva sua defesa:", 20, yConsole + 20, 20, LIGHTGRAY);
        else 
            DrawText("  Escreva seu ataque:", 20, yConsole + 20, 20, LIGHTGRAY);

        DrawText(">", 20, yConsole + 60, 20, GREEN);
        
        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, ColorToInt(COR_TERMINAL));
        GuiSetStyle(TEXTBOX, TEXT_COLOR_PRESSED, ColorToInt(GREEN));
        GuiSetStyle(TEXTBOX, BORDER_COLOR_PRESSED, ColorToInt(BLANK)); 
        
        Rectangle areaInput = { 40, yConsole + 55, LARGURA - 150, 30 };
        if (GuiTextBox(areaInput, batalha.bufferInput, 64, editMode)) editMode = true;

        if ((int)(GetTime() * 2) % 2 == 0) {
            int larguraTexto = MeasureText(batalha.bufferInput, 20); 
            DrawText("_", 45 + larguraTexto, yConsole + 60, 20, GREEN);
        }
        
        // Botão RUN visual
        if (GuiButton((Rectangle){LARGURA - 100, yConsole + 55, 80, 30}, "RUN")) { }

    } else {
        DrawText(batalha.logTerminal, 30, yConsole + 50, 20, WHITE);
        
        if (batalha.faseAtual == FASE_VITORIA) DrawText("VITORIA! ENTER p/ sair", LARGURA - 250, ALTURA - 30, 20, GREEN);
        else if (batalha.faseAtual == FASE_DERROTA) DrawText("DERROTA... ENTER p/ menu", LARGURA - 250, ALTURA - 30, 20, RED);
    }

    return TELA_COMBATE;
}