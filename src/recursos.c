#include <stdlib.h>

#include "raylib.h"

#include "recursos.h"

// carrega uma imagem especifica a partir do caminho para o arquivo e atribui ao identificador `nome`
Texture2D carregarImagem(int nome, char *arquivo) {
    Image imagem = LoadImage(arquivo);
    Texture2D textura = LoadTextureFromImage(imagem);
    UnloadImage(imagem);

    return textura;
}

void carregarRecursos(Imagens *imagens) {
    // imagens interface
    imagens->interface[SPLASH_ARTE] = carregarImagem(SPLASH_ARTE, "./imagens/arte_splash.png");
    imagens->interface[TITULO_ARTE] = carregarImagem(TITULO_ARTE, "./imagens/arte_titulo.png");
    imagens->interface[IMAGEM_FUNDO] = carregarImagem(IMAGEM_FUNDO, "./imagens/torre.jpeg");

    // imagens de cenario
    imagens->cenario[DUNGEON] = carregarImagem(DUNGEON, "./imagens/dungeon.jpeg");
    imagens->cenario[TORRE] = carregarImagem(TORRE, "./imagens/torre.jpeg");

    // imagens de personagem
    imagens->personagem[MAGA_COSTAS] = carregarImagem(MAGA_COSTAS, "./imagens/maga_costas_teste.png");
}

void descarregarRecursos(Imagens *imagens) {
    for (int id = 0; id < QTD_INTERFACES; ++id) {
        UnloadTexture(imagens->interface[id]);
    }

    for (int id = 0; id < QTD_CENARIOS; ++id) {
        UnloadTexture(imagens->cenario[id]);
    }

    for (int id = 0; id < QTD_PERSONAGENS; ++id) {
        UnloadTexture(imagens->personagem[id]);
    }
}
