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
    imagens->interface[SAVES_FUNDO] = carregarImagem(SAVES_FUNDO, "./imagens/saves_fundo.png");

    imagens->interface[BOTAO_NORMAL] = carregarImagem(BOTAO_NORMAL, "./imagens/botao_normal.png");
    imagens->interface[BOTAO_FOCADO] = carregarImagem(BOTAO_FOCADO, "./imagens/botao_focado.png");
    imagens->interface[BOTAO_PRESSIONADO] = carregarImagem(BOTAO_FOCADO, "./imagens/botao_pressionado.png");

    imagens->interface[BOTAO_APAGAR_SAVE] = carregarImagem(BOTAO_APAGAR_SAVE, "./imagens/apagar_save.png");
    imagens->interface[BOTAO_APAGAR_SAVE_FOCADO] = carregarImagem(BOTAO_APAGAR_SAVE_FOCADO, "./imagens/apagar_save_focado.png");
    imagens->interface[BOTAO_APAGAR_SAVE_INATIVO] = carregarImagem(BOTAO_APAGAR_SAVE_INATIVO, "./imagens/apagar_save_inativo.png");

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
