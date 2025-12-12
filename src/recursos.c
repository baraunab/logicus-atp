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
	imagens->interface[TORRE] = carregarImagem(TORRE, "./imagens/torre.jpeg");
    imagens->interface[BOTAO_NORMAL] = carregarImagem(BOTAO_NORMAL, "./imagens/botao_normal.png");
    imagens->interface[BOTAO_FOCADO] = carregarImagem(BOTAO_FOCADO, "./imagens/botao_focado.png");
    imagens->interface[BOTAO_PRESSIONADO] = carregarImagem(BOTAO_FOCADO, "./imagens/botao_pressionado.png");

    imagens->interface[BOTAO_APAGAR_SAVE] = carregarImagem(BOTAO_APAGAR_SAVE, "./imagens/apagar_save.png");
    imagens->interface[BOTAO_APAGAR_SAVE_FOCADO] = carregarImagem(BOTAO_APAGAR_SAVE_FOCADO, "./imagens/apagar_save_focado.png");
    imagens->interface[BOTAO_APAGAR_SAVE_INATIVO] = carregarImagem(BOTAO_APAGAR_SAVE_INATIVO, "./imagens/apagar_save_inativo.png");
    imagens->interface[SAVES_FUNDO] = carregarImagem(SAVES_FUNDO, "./imagens/saves_fundo.png");

	//imagens->interface[MAPA_TORRE] = carregarImagem(GRIMORIO, "./imagens/grimorio.png");
    imagens->interface[GRIMORIO] = carregarImagem(GRIMORIO, "./imagens/grimorio.png");

    // imagens de cenario
    imagens->cenario[DUNGEON] = carregarImagem(DUNGEON, "./imagens/dungeon.jpeg");
    imagens->cenario[FUNDO_GENERICO] = carregarImagem(FUNDO_GENERICO, "./imagens/fundo_generico.png");
	imagens->cenario[MASMORRA_ENTRADA] = carregarImagem(MASMORRA_ENTRADA, "./imagens/masmorra.png");
    imagens->cenario[MASMORRA_ENTRADA_SELO] = carregarImagem(MASMORRA_ENTRADA_SELO, "./imagens/masmorra_bloqueada.png");
	imagens->cenario[SALA_ESTATUAS] = carregarImagem(SALA_ESTATUAS, "./imagens/salaestatuas.png");
	imagens->cenario[TOPO_TORRE] = carregarImagem(TOPO_TORRE, "./imagens/topotorre.png");
	imagens->cenario[MORTE] = carregarImagem(MORTE, "./imagens/morte.png");
	imagens->cenario[CREDITOS_FINAL] = carregarImagem(CREDITOS_FINAL, "./imagens/creditos_final.png");
	

    // imagens de personagem
    imagens->personagem[BECKY1] = carregarImagem(BECKY1, "./imagens/becky.png");
    imagens->personagem[BECKY2] = carregarImagem(BECKY2, "./imagens/becky2.png");
    imagens->personagem[BECKY3] = carregarImagem(BECKY3, "./imagens/becky3.png");
    imagens->personagem[ESTATUA] = carregarImagem(ESTATUA, "./imagens/estatua1.png");
    imagens->personagem[ESTATUA_COMBATE] = carregarImagem(ESTATUA_COMBATE, "./imagens/estatua-de-combate1.png");
    imagens->personagem[GOBLIN] = carregarImagem(GOBLIN, "./imagens/goblin_combate.png");
    imagens->personagem[ORNACIO] = carregarImagem(ORNACIO, "./imagens/Ornacio.png");
    imagens->personagem[BANDO_MONSTROS] = carregarImagem(BANDO_MONSTROS, "./imagens/bando_monstros.png");
    imagens->personagem[LORDC] = carregarImagem(LORDC, "./imagens/lordC.png");
    imagens->personagem[LORDC_COMBATE] = carregarImagem(LORDC_COMBATE, "./imagens/lord-C-de-combate.png");
    imagens->personagem[LORDC_ACABADO] = carregarImagem(LORDC_ACABADO, "./imagens/lorde-C-acabado.png");
    
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
