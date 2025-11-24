CFLAGS = -Wall

ifeq ($(OS),Windows_NT)
    DEPS = -lraylib -lm -lopengl32 -lgdi32 -lwinmm
else
    DEPS = -lraylib -lm
endif

CC = gcc

INCLUDE = ./include 

RL_LDD = $(PWD)/bibliotecas/raylib/src
RL_INC = ./bibliotecas/raylib/src
RG_INC = ./bibliotecas/raygui/src

OBJS = recursos.o save.o dialogo.o main.o mudarTela.o telaInicial.o telaMenu.o telaJogo.o telaMapa.o

all: ./build/logicus

./build/logicus: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o ./build/logicus -L$(RL_LDD) -Wl,-rpath=$(RL_LDD) $(DEPS)

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -I$(RL_INC) -I$(RG_INC) -I$(INCLUDE)

save.o: ./src/save.c
	$(CC) $(CFLAGS) -c ./src/save.c

dialogo.o: ./src/dialogo.c
	$(CC) $(CFLAGS) -c ./src/dialogo.c

recursos.o: ./src/recursos.c
	$(CC) $(CFLAGS) -c ./src/recursos.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC)
	
mudarTela.o: ./src/mudarTela.c
	$(CC) $(CFLAGS) -c ./src/mudarTela.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)

telaInicial.o: ./src/telaInicial.c
	$(CC) $(CFLAGS) -c ./src/telaInicial.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)

telaMenu.o: ./src/telaMenu.c
	$(CC) $(CFLAGS) -c ./src/telaMenu.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)

telaJogo.o: ./src/telaJogo.c
	$(CC) $(CFLAGS) -c ./src/telaJogo.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)

telaMapa.o: ./src/telaMapa.c
	$(CC) $(CFLAGS) -c ./src/telaMapa.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)


clean:
	@rm *.o ./build/logicus
	@echo "limpeza feita!"
