CFLAGS = -Wall
DEPS = -lraylib -lm

CC = gcc

INCLUDE = ./include 

RL_LDD = $(PWD)/bibliotecas/raylib-5.5_linux_amd64/lib
RL_INC = ./bibliotecas/raylib-5.5_linux_amd64/include
RG_INC = ./bibliotecas/raygui-4.0/src

OBJS = save.o dialogo.o main.o

all: ./build/logicus

./build/logicus: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o ./build/logicus -L$(RL_LDD) -Wl,-rpath=$(RL_LDD) $(DEPS)

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -I$(RL_INC) -I$(RG_INC) -I$(INCLUDE)

save.o: ./src/save.c
	$(CC) $(CFLAGS) -c ./src/save.c

dialogo.o: ./src/dialogo.c
	$(CC) $(CFLAGS) -c ./src/dialogo.c

clean:
	@rm *.o ./build/logicus
	@echo "limpeza feita!"
