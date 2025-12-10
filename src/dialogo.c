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

// função que aloca os dialogos lidos do arquivo
Dialogo *carregarDialogo (char *nomeArquivo, int linhas, int *totalDialogos) {
    
    // abre arquivo atribuido no parâmetro
    FILE *arquivo = fopen(nomeArquivo, "r");
    if  (arquivo == NULL) {
        printf("dialogo.c/carregaDialogo: Erro na abertura de arquivo!");
        exit(1);
    }

    
    // ponteiro que receberá cada linha de dialogo na estruturai
    Dialogo *fala = (Dialogo *) calloc(linhas, sizeof(Dialogo));
    char aux[256]; // auxiliar para a separação do nome e texto      
    int dialogoAtual = 0; // contador
    
    int acm = 0; // acumulador para definir o tamanho da string copiada
    int auxI = 0; // auxiliar para definir o tamanho do nome
    
    // laço para a leitura de cada linha do dialogo 
    for (dialogoAtual = 0; dialogoAtual < linhas; dialogoAtual++) {
	// auxiliar copia a linha no indicie atual
        fgets(aux, 256, arquivo);
	
        // laço para encontrar o caractere separador ('|') entre nome e texto
	for (int i = 0; i < strlen(aux); i++) {
	    if (aux[i] == '|') {
		auxI = i; // armazena o indicie do separador 
		break;
	    }
	acm++; // acumula a quantidade de caracteres do nome 
	}
                // adiciona o nome no indicie atual do vetor de Dialogo
		strncpy(fala[dialogoAtual].nome, aux, acm);

                // adiciona o texto a partir do caractere seguinte ao separador
		strcpy(fala[dialogoAtual].texto, &aux[auxI+1]);	
		acm = 0; // acumulador zerado para próxima leitura de linha
	}
    
    // fecha o arquivo de dialogos
    fclose(arquivo); 

    // passa a quantidade de dialogos para fora da função
    *totalDialogos = dialogoAtual;
    
    // retorna a estrutura com informações lidas
    return fala;
}

// Função que desenha a caixa e gerencia o clique para avançar
bool GerenciarDialogo(Dialogo *dialogos, int *linhaAtual, int totalLinhas, int LARGURA, int ALTURA) {
    
    // Se já acabou as linhas, retorna false
    if (*linhaAtual >= totalLinhas) return false;

    //Desenho da interface
    
    // Caixa de Fundo (Transparente)
    DrawRectangleRounded((Rectangle){LARGURA * 0.01, ALTURA * 0.65, LARGURA * 0.98, ALTURA * 0.33}, 0.3f, 10, (Color){0, 0, 0, 200});

    // Caixa do Nome
    DrawRectangleRounded((Rectangle){ LARGURA * 0.055, (ALTURA * 0.6) + 1, (LARGURA * 0.3) + 27, (ALTURA * 0.05) + 12}, 0.3f, 12, BLACK);

    // Texto do Nome
    DrawText(dialogos[*linhaAtual].nome, (LARGURA * 0.06) + 5, (ALTURA * 0.6) + 8, 24, YELLOW);
    
    // Texto da Fala
    DrawText(dialogos[*linhaAtual].texto, LARGURA * 0.04, ALTURA * 0.7, 20, WHITE);

    DrawText("Clique ou Enter para continuar...", LARGURA - 300, ALTURA - 30, 15, GRAY);

    // Lógica de avançar dialogo
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        (*linhaAtual)++; // Vai para a próxima fala
    }

    return true; // Ainda tem diálogo acontecendo
}

