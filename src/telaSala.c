#include <stdio.h>
#include "raylib.h"
#include "recursos.h"
#include "telas.h"
#include "dialogo.h"

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
    DrawRectangle(0, 0, LARGURA, ALTURA, PURPLE);
    DrawText("ENIGMA DAS VARIAVEIS", 50, 50, 30, WHITE);
    DrawText("Declare seu destino...", 50, 100, 20, LIGHTGRAY);
    
    // Aqui conectamos com o minigame das caixinhas depois!
    
    if (IsKeyPressed(KEY_M)) return TELA_MAPA;
    return TELA_ENIGMA;
}

// 3. Baú Estranho
EstadoTela telaBau(Imagens *imagens, int LARGURA, int ALTURA) {
    DrawRectangle(0, 0, LARGURA, ALTURA, GOLD);
    DrawText("BAU ESTRANHO", 50, 50, 30, BLACK);
    DrawText("O que sera que tem dentro? (printf)", 50, 100, 20, DARKGRAY);
    
    if (IsKeyPressed(KEY_M)) return TELA_MAPA;
    return TELA_BAU;
}

// 4. Labirinto Condicional
EstadoTela telaLabirinto(Imagens *imagens, int LARGURA, int ALTURA) {
    DrawRectangle(0, 0, LARGURA, ALTURA, DARKBLUE);
    DrawText("LABIRINTO CONDICIONAL", 50, 50, 30, WHITE);
    DrawText("Se (IF) for direita, senao (ELSE)...", 50, 100, 20, LIGHTGRAY);
    
    if (IsKeyPressed(KEY_M)) return TELA_MAPA;
    return TELA_LABIRINTO;
}

// 5. Batalha dos Laços
EstadoTela telaLacos(Imagens *imagens, int LARGURA, int ALTURA) {
    DrawRectangle(0, 0, LARGURA, ALTURA, MAROON);
    DrawText("BATALHA DOS LACOS", 50, 50, 30, WHITE);
    DrawText("Enquanto (WHILE) voce tiver vida...", 50, 100, 20, LIGHTGRAY);
    
    if (IsKeyPressed(KEY_M)) return TELA_MAPA;
    return TELA_LACOS;
}