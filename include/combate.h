#ifndef COMBATE_H
#define COMBATE_H

#include "raylib.h"
#include "recursos.h"
#include "telas.h"

#define MAX_ATAQUES_INIMIGO 5
#define MAX_FEITICOS_JOGADOR 10

// --- ENUMS ---
typedef enum {
    ATAQUE_FISICO,      // Counter: "printf escudo"
    ATAQUE_LOOP,        // Counter: "break;"
    ATAQUE_MAGICO  // Counter: "free"
} TipoAtaqueInimigo;

typedef enum {
    FASE_INIMIGO_PREPARA,
    FASE_JOGADOR_DEFESA,
    FASE_RESULTADO_DEFESA,
    FASE_JOGADOR_ACAO,
    FASE_RESULTADO_ACAO,
    FASE_VITORIA,
    FASE_DERROTA
} FaseCombate;

// --- ESTRUTURAS DE PERSONALIZAÇÃO ---

// 1. Definição de UM ataque do inimigo
typedef struct {
    TipoAtaqueInimigo tipo;
    char codigoVisual[64];   // Ex: "while(true);" ou "malloc(999);"
    char mensagemAviso[64];  // Ex: "LOOP DETECTADO!"
    int danoSeFalhar;        // Quanto machuca se o player não defender
} AtaqueInimigo;

// 2. Definição do Inimigo completo
typedef struct {
    const char *nome;
    int vidaMax;
    // Lista de ataques que este inimigo sabe usar
    AtaqueInimigo ataques[MAX_ATAQUES_INIMIGO];
    int qtdAtaques; 
} DadosCombateInimigo;

// 3. Definição de um Feitiço do Jogador
typedef struct {
    char comando[32];   // O que digitar. Ex: "atacar();" ou "cast(FOGO);"
    int dano;           // Quanto tira de vida do inimigo
    char descricao[64]; // Texto de feedback. Ex: "Bola de fogo lançada!"
} FeiticoJogador;

// --- ESTRUTURA DO SISTEMA ---
typedef struct {
    // Estado Inimigo
    char nomeInimigo[64];
    int vidaInimigoAtual;
    int vidaInimigoMax;
    
    // Ataque atual que o inimigo escolheu
    AtaqueInimigo ataqueAtualInimigo;

    char declaracaoCodigoInimigo[64];

    // Estado Jogador
    int vidaJogadorAtual;
    int vidaJogadorMax;
    FeiticoJogador grimorio[MAX_FEITICOS_JOGADOR]; // Lista de magias conhecidas
    int qtdFeiticos;

    // Controle
    FaseCombate faseAtual;
    char bufferInput[64];
    char logTerminal[128];
    float timerAnimacao;
} SistemaCombate;

// --- FUNÇÕES ---
void IniciarCombate(DadosCombateInimigo dadosInimigo);
void AdicionarFeiticoJogador(const char *comando, int dano, const char *desc);
EstadoTela AtualizarCombate(Imagens *imagens, int LARGURA, int ALTURA);

#endif // COMBATE_H