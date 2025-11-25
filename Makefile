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


CPPFLAGS = -I$(RL_INC) -I$(RG_INC) -I$(INCLUDE)

#isso aqui são os arquivos objeto, essa parte eu entendi
OBJS = recursos.o save.o dialogo.o caixinhas.o main.o

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
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/recursos.c

# regra nova pro teu módulo
caixinhas.o: ./src/caixinhas.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ./src/caixinhas.c

clean:
	@rm -f $(OBJS) ./build/logicus
	@echo "limpeza feita!"
