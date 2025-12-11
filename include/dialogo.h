#ifndef DIALOGO_H
#define DIALOGO_H

#define CARAC_SEG 30.0f
#define TEMPO_CARAC (1.0 / CARAC_SEG)

static int caracteresVisiveis = 0;
static float contadorTempo = 0.0f;
static bool animacaoConcluida = false;

// estrutura para leitura de dialogos e exibição na tela
typedef struct {
    char nome[256];
    char texto[256];
} Dialogo;

// contador de linhas do arquivo
int contaLinhas (char *nomeArquivo);

// função para carregar as linhas de dialogo
Dialogo *carregarDialogo (char *nomeArquivo, int linhas, int *totalDialogos);

// função de gerenciamento de dialogo
bool GerenciarDialogo(Dialogo *dialogos, int *linhaAtual, int totalLinhas, int LARGURA, int ALTURA);
#endif // DIALOGO_H
