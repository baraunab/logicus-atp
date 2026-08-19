CC=gcc

OBJS=main.o caixinhas.o combate.o desafioCaixinhas.o dialogo.o mudarTela.o recursos.o salas.o save.o telaGrimorio.o telaInicial.o telaInput.o telaJogo.o telaMenu.o telaSala.o
TARGET=linux

ifeq ($(TARGET), windows)
	LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm
endif

LIBS=-lraylib -lm -lX11

all: logicus

logicus: $(OBJS)
	$(CC) -c src/main.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude -Lbibliotecas/raylib/src
	gcc -o logicus $(OBJS) -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude -Lbibliotecas/raylib/src $(LIBS)

telaSala.o: src/telaSala.c
	$(CC) -c src/telaSala.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude
	
caixinhas.o: src/caixinhas.c
	$(CC) -c src/caixinhas.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

recursos.o: src/recursos.c
	$(CC) -c src/recursos.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude -Lbibliotecas/raylib/src $(LIBS)

save.o: src/save.c
	$(CC) -c src/save.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

dialogo.o: src/dialogo.c
	$(CC) -c src/dialogo.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

mudarTela.o: src/mudarTela.c
	$(CC) -c src/mudarTela.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

telaInicial.o: src/telaInicial.c
	$(CC) -c src/telaInicial.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

telaMenu.o: src/telaMenu.c
	$(CC) -c src/telaMenu.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

telaJogo.o: src/telaJogo.c
	$(CC) -c src/telaJogo.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

telaInput.o: src/telaInput.c
	$(CC) -c src/telaInput.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

salas.o: src/salas.c
	$(CC) -c src/salas.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

combate.o: src/combate.c
	$(CC) -c src/combate.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

desafioCaixinhas.o: src/desafioCaixinhas.c
	$(CC) -c src/desafioCaixinhas.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

telaGrimorio.o: src/telaGrimorio.c
	$(CC) -c src/telaGrimorio.c -Ibibliotecas/raylib/src -Ibibliotecas/raygui/src -Iinclude

clean:
	del *.o
