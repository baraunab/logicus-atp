#ifndef DIALOGO_H
#define DIALOGO_H

// estrutura para leitura de dialogos e exibição na tela
typedef struct {
    char nome[256];
    char texto[256];
} Dialogo;

// contador de linhas do arquivo
int contaLinhas (char *nomeArquivo);

// função para carregar as linhas de dialogo
Dialogo *carregarDialogo (char *nomeArquivo, int linhas, int *totalDialogos);

#endif // DIALOGO_H
