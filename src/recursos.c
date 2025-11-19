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
        // imagens de cenario
        imagens->interface[SPLASH_ARTE] = carregarImagem(SPLASH_ARTE, "./imagens/arte_splash.png");
        imagens->interface[TITULO_ARTE] = carregarImagem(TITULO_ARTE, "./imagens/arte_titulo.png");

        // imagens interface
        // ..

        // imagens de personagem
        // ...
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
