#!/usr/bin/env bash
# script para configurar a variavel local de biblioteca, permitindo a compilacao

requisitos=("gcc" "git") 

for i in "${!requisitos[@]}"; do
    printf "> verificando ${requisitos[i]}..."

    if ! command -v ${requisitos[i]} >/dev/null 2>&1; then
        printf " \033[91;1m${requisitos[i]} não encontrado\033[0m\n"
        exit 1
    fi
    printf " \033[92;1mok\033[0m\n"
done

if ! [ -d bibliotecas ]; then
    printf "> ./bibliotecas/ não existe. \033[93;1mcriando\033[0m\n"
    mkdir bibliotecas
else
    printf "> ./bibliotecas/ existe. \033[93;1mpulando\033[0m\n"
fi

cd bibliotecas

if ! [ -d raylib ]; then
    printf "> baixando raylib..."
    git clone --depth=1 https://github.com/raysan5/raylib >/dev/null 2>&1
    if [ "$?" -ne 0 ]; then
        printf "\t\033[91;1mnão foi possível baixar raylib.\033[0m\n"
        exit 1
    fi

    printf " \033[92;1mok\033[0m\n"
else
    printf "> ./external/raylib exists. \033[93;1mpulando\033[0m\n"
fi

if ! [ -d raygui ]; then
    printf "> baixando raygui..."
    git clone --depth=1 https://github.com/raysan5/raygui >/dev/null 2>&1
    if [ "$?" -ne 0 ]; then
        printf "\t\033[91;1mnão foi possível baixar raygui.\033[0m\n"
        exit 1
    fi

    printf " \033[92;1mok\033[0m\n"
else
    printf "> ./external/raygui existe. \033[93;1mpulando\033[0m\n"
fi

cd raylib/src

printf "> compilando raylib..."
make PLATFORM=PLATFORM_DESKTOP -j4 >/dev/null 2>&1
exitcode=$?

if [ $exitcode -ne 0 ]; then
    printf " \033[91;1mfalhou\n\t\033[0m> \033[91;1;4mpossivelmente falta instalar alguma dependência da biblioteca raylib\033[0m (código de erro $exitcode)\n"
    exit 1
fi

printf " \033[92;1mok\033[0m\n"

cd ../../..

if ! [ -d build ] && ! [ -d saves ]; then
    mkdir build saves
fi

echo ""
echo "feito!"
