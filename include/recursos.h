#ifndef RECURSOS_H
#define RECURSOS_H

// identificadores de elementos de interface
typedef enum {
    SPLASH_ARTE,
    TITULO_ARTE,
    GRIMORIO,
    IMAGEM_FUNDO,
    MAPA_TORRE,
    FUNDO_GENERICO,
    SAVES_FUNDO,
    BOTAO_NORMAL,
    BOTAO_FOCADO,
    BOTAO_PRESSIONADO,
    BOTAO_APAGAR_SAVE,
    BOTAO_APAGAR_SAVE_FOCADO,
    BOTAO_APAGAR_SAVE_INATIVO,
    TORRE,
    QTD_INTERFACES   

} Interfaces;

// identificadores de artes de cenarios
typedef enum {
    // TODO: desenhar e carregar cenarios
    DUNGEON,
    MASMORRA_ENTRADA,
    MASMORRA_ENTRADA_SELO,
    SALA_ESTATUAS,
    TOPO_TORRE,
    MORTE,
    CREDITOS_FINAL,
    QTD_CENARIOS
} Cenarios;

// identificadores de sprites de personagens
typedef enum {
    // TODO: desenhar e carregar sprites de personagem
    BECKY1,
    BECKY2,
    BECKY3,
    ESTATUA,
    ESTATUA_COMBATE,
    GOBLIN,
    ORNACIO,
    BANDO_MONSTROS,
    LORDC,
    LORDC_COMBATE,
    LORDC_ACABADO,
    QTD_PERSONAGENS,

} Personagens;

typedef struct {
    Texture2D interface[QTD_INTERFACES];
    Texture2D cenario[QTD_CENARIOS];
    Texture2D personagem[QTD_PERSONAGENS];
} Imagens;

// 
Texture2D carregarImagem(int nome, char *arquivo);

// carrega todos os recursos do jogo (cenarios, personagens, elementos de interface, etc)
void carregarRecursos(Imagens *imagens);

// desalocar memoria usada para recursos apos uso
void descarregarRecursos(Imagens *imagens);

#endif // RECURSOS_H
