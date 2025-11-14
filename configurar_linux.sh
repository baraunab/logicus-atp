#!/usr/bin/env bash
# script para configurar a variavel local de biblioteca, permitindo a compilacao

mkdir bibliotecas
mkdir build

wget https://github.com/raysan5/raygui/archive/refs/tags/4.0.zip -P ./bibliotecas 
wget https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz -P ./bibliotecas

unzip ./bibliotecas/4.0.zip -d ./bibliotecas/
tar -xvf ./bibliotecas/raylib-5.5_linux_amd64.tar.gz -C ./bibliotecas/
