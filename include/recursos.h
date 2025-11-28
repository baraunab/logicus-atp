#ifndef RECURSOS_H
#define RECURSOS_H

// identificadores de elementos de interface
typedef enum {
    SPLASH_ARTE,
    TITULO_ARTE,
    IMAGEM_FUNDO,
    QTD_INTERFACES
    
} Interfaces;

// identificadores de artes de cenarios
typedef enum {
    // TODO: desenhar e carregar cenarios
    DUNGEON,
    TORRE,
    QTD_CENARIOS
} Cenarios;

// identificadores de sprites de personagens
typedef enum {
    // TODO: desenhar e carregar sprites de personagem
    MAGA_COSTAS,
    QTD_PERSONAGENS
} Personagens;

typedef struct {
    Texture2D interface[QTD_INTERFACES];
    Texture2D cenario[QTD_CENARIOS];
    Texture2D personagem[QTD_PERSONAGENS];
} Imagens;

// carrega todos os recursos do jogo (cenarios, personagens, elementos de interface, etc)
void carregarRecursos(Imagens *imagens);

// desalocar memoria usada para recursos apos uso
void descarregarRecursos(Imagens *imagens);

#endif // RECURSOS_H
