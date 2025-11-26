#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// estrutura com campos de informacao de um save especifico
typedef struct {
    char nomeUsuario[64];

    int pontuacao;
    int fase;
    int numeroDialogo;
    bool ativo;

    int slot;
} SaveEstado;

// relaciona espacos no arquivo binario com os indices do vetor saveSlots
void inicializarSistemaDeSave(SaveEstado *estado) {
    for (int i = 0; i < 3; ++i) {
        (estado + i)->slot = i;
    }
}


bool salvarEstadoDeJogo(SaveEstado estado) {
    // TODO: nome do arquivo nao deve ser estatico. Encontrar uma maneira melhor de fazer isso.
    char *arquivo = "./build/saves/save.data";
    FILE *f = fopen(arquivo, "r+");
    
    // validacao se arquivo pode ser encontrado/aberto
    if (f == NULL) {
        fprintf(stderr, "ERRO: impossivel escrever arquivo: %s\n", arquivo);
        exit(1);
    }
    
    // encontrar slot desejado pelo indice da posicao inicial
    fseek(f, sizeof(SaveEstado) * estado.slot, SEEK_SET);

    // ler dados e armazenar no estado passado para a funcao
    fwrite(&estado, sizeof(SaveEstado), 1, f);

    // fechar arquivo
    fclose(f);

    return 0;
}

bool carregarEstadoDeJogo(SaveEstado *estado) {
    // TODO: nome do arquivo nao deve ser estatico. Encontrar uma maneira melhor de fazer isso.
    char *arquivo = "./build/saves/save.data";

    // abrir arquivo binario para leitura
    FILE *f = fopen(arquivo, "rb");

    // validacao se arquivo pode ser encontrado/aberto
    if (f == NULL) {
        fprintf(stderr, "ERRO: impossivel abrir arquivo: %s\n", arquivo);
        exit(1);
    }
    
    // encontrar slot desejado pelo indice da posicao inicial
    fseek(f, sizeof(SaveEstado) * estado->slot, SEEK_SET);

    // ler dados e armazenar no estado passado para a funcao
    fread(estado, sizeof(SaveEstado), 1, f);
    
    // fechar arquivo
    fclose(f);

    return true;
}
