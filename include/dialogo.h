#ifndef DIALOGO_H
#define DIALOGO_H

struct dialogo {
    char nome[256];
    char texto[256];
};

int contaLinhas (FILE *arquivo);

struct dialogo *carregarDialogo (FILE *arquivo, int linhas, int *totalDialogos);

#endif // DIALOGO_H
