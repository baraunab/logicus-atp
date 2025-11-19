#ifndef CAIXINHAS_H//esse ifndef é pra evitar que o arquivo seja incluído mais de uma vez
#define CAIXINHAS_H

#include "raylib.h"

typedef struct {
    Rectangle area;
    const char *texto;
    int correta;
    int selecionada;
} Caixinha;

void RodarDesafioCaixinhas(void);//o arquivo no final de tudo, tem que rodar pelo .h e nao pelo .c, lembrar disso

#endif//CAIXINHAS_H
