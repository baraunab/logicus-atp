#!/usr/bin/env bash
# script para configurar a variavel local de biblioteca, permitindo a compilacao

if [ ! -d "bibliotecas" ]; then
    echo "Criando ./bibliotecas/..."
    mkdir bibliotecas
fi

if [ ! -d "build" ]; then
    echo "Criando ./build/..."
    mkdir build
fi

echo "Limpando bibliotecas antigas..."
rm -rf ./bibliotecas/*

echo "Baixando RayGui..."
git clone --depth=1 https://github.com/raysan5/raylib ./bibliotecas/raylib

echo "Baixando RayLib..."
git clone --depth=1 https://github.com/raysan5/raygui ./bibliotecas/raygui

cd bibliotecas/raylib/src
make -j4

echo "Configuracao finalizada!!"
