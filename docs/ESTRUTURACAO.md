# Estrutura Geral do Projeto
Sub-Diretório | Propósito
--- | ---
include/ | Arquivos _header_ com protótios de funções e structs.
src/ | Arquivos _source_ com implementações do jogo.
dialogos/ | Arquivos texto onde diálogos são armazenados.
imagens/ | Recursos de imagem (artes de menu, cenários, personagens).
bibliotecas/ | Pasta reservada para bibliotecas externas.
docs/ | Documentação e informações adicionais do projeto.
---
```
|- include/
|     |
|     |- save.h
|     |- dialogo.h
|     |- cenas.h
|
|- src/
|   |
|   |- main.c
|   |- engine/
|          |
|          |- save.c
|          |- dialogo.c
|          |- cenas.c
|
|- dialogos/
|     |
|     |- diag.txt
|
|- imagens/
|     |
|     |- icones/
|     |- sprites/
|     |- backgrounds/
|
|- bibliotecas
|       |
|       |- raylib
|       |- raygui
|
|- docs
|   |
|   |- ESTRUTURACAO.md
|   |- GUIA_DE_ESTILO.md
```
