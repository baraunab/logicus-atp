#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#include "dialogo.h"


// conta a quantidade de linhas do arquivo
int contaLinhas (char *nomeArquivo) {
    
    // abre arquivo atribuido no parâmetro
    FILE *arquivo = fopen(nomeArquivo, "r");
    if  (arquivo == NULL) {
        printf("dialogo.c/contaLinhas: Erro na abertura de arquivo!");
        exit(1);
    }

    char c; // percorre caractere por caractere no arquivo
    int linhas = 0;
    
    // loop até o final do arquivo
    while (!feof(arquivo)) {
	    c = fgetc(arquivo);
            if (c == '\n') {
		linhas++;
	    }
    }
    
    // fecha arquivo 
    fclose(arquivo);
    
    // retorna o total de linhas
    return linhas;
}

Dialogo *carregarDialogo (char *nomeArquivo, int linhas, int *totalDialogos) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if  (arquivo == NULL) {
        printf("dialogo.c/carregaDialogo: Erro na abertura de arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    // ponteiro que receberá cada linha de dialogo na estrutura
    Dialogo *fala = (Dialogo *) calloc(linhas + 1, sizeof(Dialogo)); // +1 segurança
    char aux[256];      
    int dialogoAtual = 0;
    
    int auxI = 0; 
    
    // laço para a leitura de cada linha do dialogo 
    while (dialogoAtual < linhas && fgets(aux, 256, arquivo) != NULL) {
        
        // Remove pular linha no final, se houver
        aux[strcspn(aux, "\n")] = 0;

        int separadorEncontrado = 0;

        // laço para encontrar o caractere separador ('|')
        for (int i = 0; i < strlen(aux); i++) {
            if (aux[i] == '|') {
                auxI = i; 
                separadorEncontrado = 1;
                break;
            }
        }

        if (separadorEncontrado) {
            // Copia o nome (tudo antes do |)
            strncpy(fala[dialogoAtual].nome, aux, auxI);
            fala[dialogoAtual].nome[auxI] = '\0'; // Garante fim da string

            // Copia o texto (tudo depois do |)
            strcpy(fala[dialogoAtual].texto, &aux[auxI+1]);
            
            dialogoAtual++;
        }
    }
    
    fclose(arquivo); 

    *totalDialogos = dialogoAtual;
    return fala;
}

// função de gerenciamento de dialogo
// Retorna 'true' se o diálogo ainda estiver em andamento, 'false' se tiver terminado.
bool GerenciarDialogo(Dialogo *dialogos, int *linhaAtual, int totalLinhas, int LARGURA, int ALTURA) {
    
    bool esperaInput = true;
	
	// Verifica se a linha atual está fora do limite antes de processar
    if (*linhaAtual >= totalLinhas) {
        return false;
    }

    // 1. Lógica de pular animação (se o texto não terminou de aparecer)
    if (esperaInput && !animacaoConcluida) {
        if (IsKeyPressed(KEY_SPACE)) {
            animacaoConcluida = true;
            // Força que todos os caracteres sejam visíveis imediatamente
            caracteresVisiveis = strlen(dialogos[*linhaAtual].texto);
        }
    }
    
    // 2. Lógica de avanço de linha (ocorre apenas se a animação tiver terminado)
    if (animacaoConcluida) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            (*linhaAtual)++;
            
            // Verifica se chegou ao fim (Fim da leitura do arquivo)
            if (*linhaAtual >= totalLinhas) {
                // Reset de variáveis de controle para o próximo uso
                animacaoConcluida = false;
                caracteresVisiveis = 0;
                contadorTempo = 0.0f;
                return false; // Sinaliza que o diálogo terminou
            }
            
            // Reset de variáveis para a nova linha começar a animar
            animacaoConcluida = false;
            caracteresVisiveis = 0;
            contadorTempo = 0.0f;
            
            // Continua no loop da tela, aguardando o próximo frame
            return true;
        }
    } 
    
    // 3. Lógica de animação de timing (incrementa caracteresVisiveis)
    if (!animacaoConcluida) {
        contadorTempo += GetFrameTime();
        if (contadorTempo >= TEMPO_CARAC) {
            contadorTempo -= TEMPO_CARAC;
            caracteresVisiveis++;
            
            // Garante que o contador não exceda o tamanho real do texto
            if (caracteresVisiveis >= strlen(dialogos[*linhaAtual].texto)) {
                animacaoConcluida = true;
                caracteresVisiveis = strlen(dialogos[*linhaAtual].texto); 
            }
        }
    }

    // Desenhos
    // Desenha a caixa de diálogo de fundo 
    DrawRectangleRounded((Rectangle){ LARGURA * 0.01, ALTURA * 0.65, LARGURA * 0.98, ALTURA * 0.33}, 0.3f, 10, (Color){0, 0, 0, (255)/1.5});

    // Caixa de Nome 
    DrawRectangleRounded((Rectangle){ LARGURA * 0.055, (ALTURA * 0.6) + 1, (LARGURA * 0.3) + 27, (ALTURA * 0.05) + 12}, 0.3f, 12, BLACK);

    // Texto do Nome
    DrawText(dialogos[*linhaAtual].nome, (LARGURA * 0.06) + 5, (ALTURA * 0.6) + 8, 24, WHITE);
    
    // Desenho animado do dialogo
    char textoVisivel[256];
    
    // Garante que apenas os caracteres visíveis sejam copiados
    strncpy(textoVisivel, dialogos[*linhaAtual].texto, caracteresVisiveis);
    textoVisivel[caracteresVisiveis] = '\0';

    // TEXTO DO DIÁLOGO
    DrawText(textoVisivel, LARGURA * 0.04, ALTURA * 0.7, 20, WHITE);
    
    // Indicador de "Próximo"
    if (animacaoConcluida && esperaInput) {
        // Exibe prompt para avançar
        DrawText(">>", LARGURA * 0.95, ALTURA * 0.92, 20, WHITE); 
    }

    return true; // Sinaliza que o diálogo continua
}