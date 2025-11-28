#ifndef CAIXINHAS_H
#define CAIXINHAS_H

#include "raylib.h"
// estrutura para representar cada caixinha/opção
typedef struct {
    Rectangle area;
    const char *texto;
    int correta;
    int selecionada;
} Caixinha;
// função principal para rodar o desafio das caixinhas
EstadoTela RodarDesafioCaixinhas(void);

#endif // CAIXINHAS_H
