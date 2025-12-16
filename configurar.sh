#!/usr/bin/env bash
# script para configurar a variavel local de biblioteca, permitindo a compilacao

set -e

if [ ! -d "build" ]; then
    mkdir build
fi

if [ ! -d "saves" ]; then
    mkdir saves
fi

if [ ! -d "bibliotecas" ]; then
    mkdir bibliotecas
    cd bibliotecas

    echo "[LOG] Baixando raygui..."
    git clone --depth=1 https://github.com/raysan5/raylib raylib > /dev/null 2>&1

    echo "[LOG] Baixando raylib..."
    git clone --depth=1 https://github.com/raysan5/raygui raygui > /dev/null 2>&1
    cd ..
else
    echo "[LOG] 'bibliotecas/' já existe."
fi


cd bibliotecas/raylib/src
if [ ! -f "libraylib.a" ]; then
    echo "[LOG] Compilando raylib..."
    make -j4 > /dev/null 2>&1
else
    echo "[LOG] 'libraylib.a' já existe. Para reinstalação, apague a pasta 'bibliotecas/'"
fi

echo ""
echo "[LOG] Configuração finalizada!"
