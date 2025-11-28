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

OBJS = caixinhas.o recursos.o save.o dialogo.o main.o mudarTela.o telaInicial.o telaMenu.o telaJogo.o telaMapa.o telaInput.o

CPPFLAGS = -I$(RL_INC) -I$(RG_INC) -I$(INCLUDE)

all: ./build/logicus

./build/logicus: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ./build/logicus -L$(RL_LDD) -Wl,-rpath=$(RL_LDD) $(DEPS)

main.o: ./src/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/main.c

save.o: ./src/save.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/save.c

dialogo.o: ./src/dialogo.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/dialogo.c

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

telaInput.o: ./src/telaInput.c
	$(CC) $(CFLAGS) -c ./src/telaInput.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)

telaMapa.o: ./src/telaMapa.c
	$(CC) $(CFLAGS) -c ./src/telaMapa.c -I$(INCLUDE) -I$(RL_INC) -I$(RL_INC) -I$(RG_INC)

	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/recursos.c

# regra nova pro teu módulo
caixinhas.o: ./src/caixinhas.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/caixinhas.c

clean:
	@rm -f $(OBJS) ./build/logicus
	@echo "limpeza feita!"
