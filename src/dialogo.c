#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "../../src/raygui.h"
#include "dialogo.h"

int contaLinhas (FILE *arquivo) {
    char c;
    int linhas = 0;
    while (!feof(arquivo)) {
	    c = fgetc(arquivo);
	    if (c == '\n') {
		linhas++;
	    }
    }

    rewind(arquivo);

    return linhas;
}

struct dialogo *carregarDialogo (FILE *arquivo, int linhas, int *totalDialogos) {
    struct dialogo *fala = (struct dialogo*) calloc(linhas, sizeof(struct dialogo));
    char aux[256];
    int dialogoAtual = 0;
    
    int acm = 0;
    int auxI = 0;
	
    for (dialogoAtual = 0; dialogoAtual < linhas; dialogoAtual++) {
	fgets(aux, 256, arquivo);
	
	for (int i = 0; i < strlen(aux); i++) {
	    if (aux[i] == '|') {
		auxI = i;
		break;
	    }
	acm++;
	}
		strncpy(fala[dialogoAtual].nome, aux, acm);
		strcpy(fala[dialogoAtual].texto, &aux[auxI+1]);	
		acm = 0;
	}
    fclose(arquivo);
    *totalDialogos = dialogoAtual;
    
    return fala;
}

