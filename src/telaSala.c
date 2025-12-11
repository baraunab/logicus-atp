#include <stdio.h>
#include "raylib.h"
#include "raygui.h"
#include "recursos.h"
#include "telas.h"
#include "dialogo.h"
#include "combate.h"

//Dados dos combates pré-declarados------------------------------------------------------------
 
const DadosCombateInimigo LORD_C = {
   	.nome = "Lord C",
   	.vidaMax = 200,
   	.qtdAtaques = 5, // Define quantos ataques ele tem
   	.ataques = {
       	//Loop Infinito
       	{
           	.tipo = ATAQUE_LOOP,
           	.codigoVisual = "while(true);",
           	.mensagemAviso = "LOOP INFINITO! Quebre com 'break;'",
           	.danoSeFalhar = 25
       	},
       	//Físico
       	{
           	.tipo = ATAQUE_FISICO,
           	.codigoVisual = "acao = SOCO;",
           	.mensagemAviso = "Ataque direto! Use 'printf escudo'",
           	.danoSeFalhar = 15
       	},
       	//Lança ígnea
       	{
           	.tipo = ATAQUE_MAGICO,
           	.codigoVisual = "printf(Lança ígnea);",
           	.mensagemAviso = "Uma lança flamejante, use 'printf(contramagia);'",
           	.danoSeFalhar = 15
       	},
       	//Portal monstruoso
       	{
           	.tipo = ATAQUE_LOOP,
           	.codigoVisual = "while(portal = true);",
           	.mensagemAviso = "Enfrente um enxame de monstros",
           	.danoSeFalhar = 15
       	},
       	//Condenação
       	{
           	.tipo = ATAQUE_MAGICO,
           	.codigoVisual = "BeckyHP = END;",
           	.mensagemAviso = "Sobreviva se for capaz",
           	.danoSeFalhar = 60
       	}
   	}
};

const DadosCombateInimigo ESTATUAS = {
    .nome = "Trindade de Pedra", 
    .vidaMax = 180,              
    .qtdAtaques = 3,             
    .ataques = {
        //O Olhar Petrificante
        {
            .tipo = ATAQUE_MAGICO,
            .codigoVisual = "cast(PETRIFICAR);", 
            .mensagemAviso = "Olhar brilhante! Use 'printf contramagia'",
            .danoSeFalhar = 30
        },
        //Esmagar
        {
            .tipo = ATAQUE_FISICO,
            .codigoVisual = "acao = DESMORONAR;", 
            .mensagemAviso = "Elas vao cair! Use 'printf escudo'",
            .danoSeFalhar = 25
        },
        //Tremor 
        {
            .tipo = ATAQUE_FISICO,
            .codigoVisual = "chao->tremer = 1;", 
            .mensagemAviso = "Terremoto! Use 'printf escudo'",
            .danoSeFalhar = 20
        }
    }
};

const DadosCombateInimigo GOBLIN = {
    .nome = "Goblin Saqueador",
    .vidaMax = 80,
    .qtdAtaques = 3,
    .ataques = {
        { ATAQUE_FISICO, "acao = MORDIDA;", "O Goblin tenta morder!", 10 },
        { ATAQUE_FISICO, "alvo = Flecha;", "O Goblin dispara uma flecha contra o jogador!", 15},
        { ATAQUE_LOOP, "while(correr);", "O Goblin corre em circulos!", 15 }
    }
};

//Fim dos dados de combate---------------------------------------------------------------------

// Estrutura local para os desafios do labirinto
typedef struct {
    const char *codigo;      // O código C para interpretar
    bool respostaEsquerda;   // true = Esquerda é a certa, false = Direita é a certa
} DesafioLabirinto;


//1. Entrada da Masmorra
EstadoTela telaEntrada(Imagens *imagens, int LARGURA, int ALTURA) {
	
	static int estagioDesafio = 0;
    // Variáveis Estáticas (mantêm o valor entre os frames)
    static Dialogo *falasEntrada = NULL;
    static int totalFalas = 0;
    static int linhaAtual = 0;
    static bool carregado = false;

    // Carrega o arquivo apenas na primeira vez
    if (!carregado) {
        int linhas = contaLinhas("./dialogos/entrada.txt"); 
        falasEntrada = carregarDialogo("./dialogos/entrada.txt", linhas, &totalFalas);
        carregado = true;
    }

    DrawTexture(imagens->cenario[DUNGEON], 0, 0, WHITE);
    DrawText("SALA: ENTRADA", 20, 20, 20, LIGHTGRAY);
    
    //Game states dentro da sala
    switch (estagioDesafio) {
        
        case 0: // Checa o diálogo e, caso tenha acabado, chama o desafio de input
            if (!GerenciarDialogo(falasEntrada, &linhaAtual, totalFalas, LARGURA, ALTURA)) {
                
                // Diálogo acabou, mostra instruções
                DrawText("PRIMEIRO DESAFIO: Biblioteca Padrão", 170, 350, 20, GOLD);
                DrawText("Pressione ENTER para iniciar.", 200, 380, 20, WHITE);

                if (IsKeyPressed(KEY_ENTER)) {
                    // Configura o desafio de input para a primeira pergunta
                    configurarInput(
                        "Declare a biblioteca padrão\nde entrada e saida!", // Pergunta
                        "#include <stdio.h>",          // Resposta
                        TELA_ENTRADA,   // Se acertar, volta pra cá (cai no case 1)
                        TELA_ENTRADA    // Se errar, volta pra cá (cai no case 1)
                    );
                    estagioDesafio = 1; // Avança o estado para esperar o resultado
                    return TELA_INPUT;  // Troca de tela
                }
            }
            break;

        case 1: // Verificação da pergunta 1
            if (UltimoInputFoiSucesso) {
                // Acertou a primeira
                DrawText("PRIMEIRA BARREIRA ROMPIDA!", 160, 200, 30, GREEN);
                DrawText("Pressione ENTER para o segundo desafio.", 170, 250, 20, WHITE);

                if (IsKeyPressed(KEY_ENTER)) {
                    // Configura o input pra segunda pergunta
                    configurarInput(
                        "Declare a função principal\npresente em todos os feitiços!", 
                        "main()", 
                        TELA_ENTRADA, 
                        TELA_ENTRADA
                    );
                    estagioDesafio = 2; // Verifica a resposta da 2
                    return TELA_INPUT;
                }
            } else {
                // Errou a primeira
                DrawText("VOCE FALHOU NO PRIMEIRO TESTE.", 200, 200, 30, RED);
                DrawText("Pressione ENTER para tentar novamente.", 200, 250, 20, WHITE);
                
                if (IsKeyPressed(KEY_ENTER)) {
                    estagioDesafio = 0; // Volta para o início (ou apenas relança a pergunta)
                    linhaAtual = totalFalas; // Pula o diálogo pra não ter que ler tudo de novo
                }
            }
            break;

        case 2: // Verifica resposta da 2
            if (UltimoInputFoiSucesso) {
                // Acertou a segunda
                estagioDesafio = 3; 
            } else {
                // Errou a segunda
                DrawText("VOCE FALHOU NO SEGUNDO TESTE.", 200, 200, 30, RED);
                DrawText("Pressione ENTER para tentar novamente.", 200, 250, 20, WHITE);
                
                if (IsKeyPressed(KEY_ENTER)) {
                    // Reconfigura a pergunta 2
                    configurarInput(
						"Declare a função principal,\npresente em todos os feitiços!",
						"main()", 
						TELA_ENTRADA, 
						TELA_ENTRADA
					);
					
                    return TELA_INPUT;
                }
            }
            break;

        case 3: // VITÓRIA / PORTA ABERTA
            DrawText("ACESSO CONCEDIDO!", 180, 200, 40, GOLD);
            DrawText("A torre de Lord C aguarda...", 225, 260, 20, WHITE);
            
            DrawText("Pressione 'M' para voltar ao Mapa", 200, 370, 20, LIGHTGRAY);
			
			DrawText("Pressione ENTER para seguir até a próxima sala", 175, 400, 20, LIGHTGRAY);            
            
			if (IsKeyPressed(KEY_M)) {
				return TELA_MAPA;
			}
			
			if (IsKeyPressed(KEY_ENTER)) {
				return TELA_ENIGMA;
			}
            break;
    }
    
    return TELA_ENTRADA;
}

// 2. Enigma das Variáveis
EstadoTela telaEnigma(Imagens *imagens, int LARGURA, int ALTURA) {
    
    static Dialogo *falasEnigma = NULL;
    static int totalFalas = 0;
    static int linhaAtual = 0;
    static bool carregado = false;
    static bool dialogoConcluido = false;

    if (!carregado) {
        int linhas = contaLinhas("./dialogos/enigma.txt"); 
        falasEnigma = carregarDialogo("./dialogos/enigma.txt", linhas, &totalFalas);
        
        carregado = true;
    }

    // Variaveis do puzzle
    static int perguntaAtual = 0; 
    static bool enigmaResolvido = false;


    // Fundo
    DrawTexture(imagens->cenario[DUNGEON], 0, 0, WHITE);
    DrawText("SALA: ENIGMA DAS VARIAVEIS", 20, 20, 20, LIGHTGRAY);


    // Diálogo
    if (!dialogoConcluido) {
        if (!GerenciarDialogo(falasEnigma, &linhaAtual, totalFalas, LARGURA, ALTURA)) {
            dialogoConcluido = true; // Acabou a conversa, libera o puzzle
        } else {
            return TELA_ENIGMA; // Enquanto conversa, não faz mais nada
        }
    }

    // Puzzle entra por aqui
    

    DrawRectangle(0, 0, LARGURA, ALTURA, DARKGREEN);
    DrawText("ENIGMA RESOLVIDO!", LARGURA/2 - 150, ALTURA/2 - 50, 30, WHITE);
    DrawText("Pressione ENTER para pegar o item.", LARGURA/2 - 180, ALTURA/2 + 20, 20, LIGHTGRAY);

    if (IsKeyPressed(KEY_ENTER)) {
        return TELA_BAU; 
    }

    if (IsKeyPressed(KEY_M)) return TELA_MAPA;
    return TELA_ENIGMA;
}

// 3. Baú Estranho
EstadoTela telaBau(Imagens *imagens, int LARGURA, int ALTURA) {
    
    // --- VARIÁVEIS DO DIÁLOGO ---
    static Dialogo *falasBau = NULL;
    static int totalFalas = 0;
    static int linhaAtual = 0;
    static bool carregado = false;
    
    // --- ESTADOS DA SALA ---
    // 0: Diálogo inicial (Lendo a plaquinha)
    // 1: Configurando Desafio 1 (Printf Ornácio)
    // 2: Verificando Desafio 1
    // 3: Transição (Baú abriu, mas a chave é incompreensível)
    // 4: Configurando Desafio 2 (Scanf Chave)
    // 5: Verificando Desafio 2
    // 6: Vitória / Item Pego
    static int estadoSala = 0; 
    
    if (!carregado) {
        int linhas = contaLinhas("./dialogos/bau.txt"); 
        falasBau = carregarDialogo("./dialogos/bau.txt", linhas, &totalFalas);
        
        carregado = true;
    }

    // Desenha o fundo
    DrawRectangle(0, 0, LARGURA, ALTURA, GOLD); 
    DrawText("SALA: O BAU ESTRANHO", 20, 20, 20, BLACK);
    
    switch (estadoSala) {
        
        case 0: // DIÁLOGO INICIAL
            if (!GerenciarDialogo(falasBau, &linhaAtual, totalFalas, LARGURA, ALTURA)) {
                DrawText("A placa diz:", 200, 300, 20, BLACK);
                DrawText("'Diga meu nome usando a Lingua Antiga...'", 200, 330, 20, DARKGRAY);
                DrawText("Pressione ENTER para tentar responder.", 200, 400, 20, WHITE);
                
                if (IsKeyPressed(KEY_ENTER)) {
                    estadoSala = 1; // Vai configurar o desafio
                }
            }
            break;

        case 1: // CONFIGURAR DESAFIO 1 (PRINTF)
            configurarInput(
                "A placa espera que voce DIGA o nome.\nQual comando usamos para SAIDA de texto?", 
                "printf(\"Ornácio\");", 
                TELA_BAU, // Se acertar volta pra cá
                TELA_BAU  // Se errar volta pra cá
            );
            estadoSala = 2; // Avança para esperar o resultado
            return TELA_INPUT;
            break;

        case 2: // VERIFICAR DESAFIO 1
            if (UltimoInputFoiSucesso) {
                estadoSala = 3; // Acertou, vai pra transição
            } else {
                // Errou
                DrawText("O Bau permanece fechado.", 200, 300, 30, RED);
                DrawText("Pressione ENTER para tentar de novo.", 200, 350, 20, WHITE);
                if (IsKeyPressed(KEY_ENTER)) {
                    estadoSala = 1; // Tenta configurar de novo
                }
            }
            break;

        case 3: // TRANSIÇÃO
            DrawText("O BAU SE ABRIU!", 250, 200, 40, DARKGREEN);
            DrawText("Mas a chave brilha de uma forma estranha...", 170, 260, 20, BLACK);
            DrawText("Voce nao consegue pega-la com as maos.", 170, 290, 20, BLACK);
            DrawText("Voce precisa LER a variavel para sua memoria.", 170, 320, 20, BLACK);
            
            DrawText("Pressione ENTER para usar o comando de Leitura.", 170, 400, 20, WHITE);
            
            if (IsKeyPressed(KEY_ENTER)) {
                estadoSala = 4;
            }
            break;

        case 4: // CONFIGURAR DESAFIO 2 (SCANF)
            configurarInput(
                "Para pegar a chave (inteiro), precisamos LER\no valor para o endereço de memoria.", 
                "scanf(\"%d\", &chave);", 
                TELA_LABIRINTO, 
                TELA_BAU
            );
            estadoSala = 5;
            return TELA_INPUT;
            break;

        case 5: // VERIFICAR DESAFIO 2
            if (UltimoInputFoiSucesso) {
                estadoSala = 6; // Vitória total
            } else {
                DrawText("A chave escorrega da sua mente.", 200, 300, 30, RED);
                DrawText("Pressione ENTER para tentar de novo.", 200, 350, 20, WHITE);
                if (IsKeyPressed(KEY_ENTER)){
                	return TELA_MAPA;
				}
            }
            break;

        case 6: // VITÓRIA / SAÍDA
            DrawText("ITEM OBTIDO: CHAVE DO LOOP!", 200, 250, 30, GOLD);
            DrawText("Agora voce pode enfrentar os desafios finais.", 200, 300, 20, BLACK);
            DrawText("Pressione M para voltar ao Mapa.", 200, 400, 20, WHITE);
            
            // Aqui você poderia dar um feitiço extra também
            if (IsKeyPressed(KEY_M)){
            	return TELA_MAPA;
			}
            break;
    }
    
    return TELA_BAU;
}

// 4. Labirinto Condicional
EstadoTela telaLabirinto(Imagens *imagens, int LARGURA, int ALTURA) {
    
    static Dialogo *falasLabirinto = NULL;
    static int totalFalas = 0;
    static int linhaAtual = 0;
    static bool carregado = false;
    static bool dialogoConcluido = false;

    // Dialogo
    if (!carregado) {
        int linhas = contaLinhas("./dialogos/labirinto.txt"); 
        falasLabirinto = carregarDialogo("./dialogos/labirinto.txt", linhas, &totalFalas);
        carregado = true;
    }

    // Variavel que mede o progresso de acertos
    static int progresso = 0; // Quantos acertos (0 a 3)
    
    // IFs e ELSEs a serem interpretados
    static const DesafioLabirinto fases[3] = {
        // Desafio 0
        { 
            "int x = 10;\n\n"
            "if (x > 5) {\n"
            "    caminho = ESQUERDA;\n"
            "} else {\n"
            "    caminho = DIREITA;\n"
            "}", 
            true // Resposta correta: Esquerda
        },
        // Desafio 1
        { 
            "int chave = 0;\n\n"
            "if (!chave) {\n"
            "    caminho = DIREITA;\n"
            "} else {\n"
            "    caminho = ESQUERDA;\n"
            "}", 
            false // Resposta correta: Direita (!0 é verdadeiro)
        },
        // Desafio 2
        { 
            "int a = 5, b = 5;\n\n"
            "if (a + b == 12) {\n"
            "    caminho = ESQUERDA;\n"
            "} else if (a == b) {\n"
            "    caminho = DIREITA;\n"
            "} else {\n"
            "    caminho = ESQUERDA;\n"
            "}", 
            false // Resposta correta: Direita (cai no else if)
        }
    };

    // Cenário com mirroring
    // Mantido no topo para desenhar o fundo antes do diálogo ou do jogo
    Rectangle sourceRec = { 0.0f, 0.0f, (float)imagens->cenario[DUNGEON].width, (float)imagens->cenario[DUNGEON].height };
    
    if (progresso % 2 != 0) {
        sourceRec.width = -sourceRec.width; // Inverte horizontalmente (Mirroring)
    }

    Rectangle destRec = { 0.0f, 0.0f, (float)LARGURA, (float)ALTURA };
    DrawTexturePro(imagens->cenario[DUNGEON], sourceRec, destRec, (Vector2){0,0}, 0.0f, WHITE);

    // Título e Instrução
    DrawText("LABIRINTO CONDICIONAL", 20, 20, 30, LIGHTGRAY);
    DrawText(TextFormat("Sala %d / 3", progresso + 1), 20, 60, 20, YELLOW);

    if (!dialogoConcluido) {
        if (!GerenciarDialogo(falasLabirinto, &linhaAtual, totalFalas, LARGURA, ALTURA)) {
            dialogoConcluido = true;
        } else {
            return TELA_LABIRINTO; // Retorna aqui para não desenhar botões por cima da fala
        }
    }

    // Sucesso
    if (progresso >= 3) {
        // Passou pelos 3 desafios!
        DrawRectangle(0, 0, LARGURA, ALTURA, DARKBLUE);
        DrawText("LABIRINTO VENCIDO!", LARGURA/2 - 150, ALTURA/2 - 50, 30, GREEN);
        DrawText("Pressione ENTER para avançar.", LARGURA/2 - 160, ALTURA/2 + 20, 20, WHITE);
        
        if (IsKeyPressed(KEY_ENTER)) return TELA_LACOS; // Próxima sala
        return TELA_LABIRINTO;
    }

    // Desenho do código
    // Desenha um fundo escuro para o código ficar legível
    DrawRectangleRounded((Rectangle){LARGURA/2 - 200, 100, 400, 250}, 0.1f, 10, Fade(BLACK, 0.8f));
    DrawRectangleRoundedLines((Rectangle){LARGURA/2 - 200, 100, 400, 250}, 0.1f, 10, WHITE);
    
    // Desenha o código do desafio atual
    DrawText(fases[progresso].codigo, LARGURA/2 - 180, 120, 20, GREEN);


    // Botões de escolha
    // Botão Esquerda
    if (GuiButton((Rectangle){100, ALTURA - 100, 200, 60}, "< ESQUERDA")) {
        if (fases[progresso].respostaEsquerda == true) {
            // Acertou
            progresso++; 
        } else {
            // Errou
            IniciarCombate(GOBLIN);
            return TELA_COMBATE;
        }
    }

    // Botão Direita
    if (GuiButton((Rectangle){LARGURA - 300, ALTURA - 100, 200, 60}, "DIREITA >")) {
        if (fases[progresso].respostaEsquerda == false) {
            // Acertou
            progresso++; 
        } else {
            // Errou
            IniciarCombate(GOBLIN);
            return TELA_COMBATE;
        }
    }

    // Menu
    if (IsKeyPressed(KEY_M)) return TELA_MAPA;
    
    return TELA_LABIRINTO;
}

// 5. Batalha dos Laços
EstadoTela telaLacos(Imagens *imagens, int LARGURA, int ALTURA) {
    
    static Dialogo *falasLacos = NULL;
    static int totalFalas = 0;
    static int linhaAtual = 0;
    static bool carregado = false;
    static bool dialogoConcluido = false;
    
    if (!carregado) {
        int linhas = contaLinhas("./dialogos/lord.txt"); 
        falasLacos = carregarDialogo("./dialogos/lord.txt", linhas, &totalFalas);
        carregado = true;
    }

    static bool combateIniciado = false;

    DrawRectangle(0, 0, LARGURA, ALTURA, MAROON);
    DrawText("BATALHA DOS LACOS", 50, 50, 30, WHITE);

    if (!dialogoConcluido) {
        if (!GerenciarDialogo(falasLacos, &linhaAtual, totalFalas, LARGURA, ALTURA)) {
            dialogoConcluido = true; // Diálogo terminou, libera o combate
        } else {
            return TELA_LACOS; // Retorna aqui para focar no diálogo
        }
    }

    // Se o dialogo acabou, inicia o combate
    DrawText("Aperte 'I' para Iniciar o Combate!", 50, 100, 20, LIGHTGRAY);
    
    if (IsKeyPressed(KEY_I) && !combateIniciado) {
        // Inicia o combate com os dados personalizados
        IniciarCombate(LORD_C); 
        
        combateIniciado = true;
        return TELA_COMBATE;
    }

    if (IsKeyPressed(KEY_M)){
    	 return TELA_MAPA;
	}
    return TELA_LACOS;
}