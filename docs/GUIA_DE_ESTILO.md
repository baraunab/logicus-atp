# Guia de Estilo
Este guia serve de referência para o estilo de código adotado nesse projeto, a fim de padronizar o aspecto geral da codebase.

# 1.0 Identação e espaços
- Utilizar identação de quatro caracteres de espaços.
- Exceto ao chamar funções, utilizar espaço em parênteses, chaves iniciais e operadores lógicos.
```c
// ruim
for(int i=0;i<666;++i){
    printf("%d\n", i);
}

// bom
for (int i = 0; i < 666; ++i) {
    printf("%d\n", i);
}
```

## 1.1 Ponteiros
- Evitar referenciação e desreferenciação com operadores `&` e `*` quando desnecessários e comprometem clareza do código.
```c
// ruim
int n[5];
*(n + 3) = 2;

// bom
n[3] = 2;
```

# 2.0 Condicionais, funções e laços
- Evitar o uso de condicionais ou laços de uma única linha:
```c
// ruim
if (a == b) return true;

while (a > b) a--;

// bom
if (a == b) {
    return true;
}

while (a > b) {
    a--;
}
```

# 3.0 Prototipação
- Evitar deixar parametros sem nome, pois isso deixa a definição confusa.
```c
// ruim
int soma(int, int);

// bom
int soma(int n1, int n2);
```

# 4.0 Nomes de variáveis
- Utilizar camel case e nomes desccritivos.
- Constantes e macros podem ter underline.
```c
// ruim
int nome_de_variavel;
float NomeDeVariavel;

// bom
int nomeDeVariavel;
#define NOME_DE_CONSTANTE 0
```

# 5.0 Comentários
- Sempre comente para o máximo de clareza, exceto se a instrução for totalmente auto descritiva.
```c
// comentário de uma única linha.

/*
    comentário de múltiplas linhas
    devem ser escritos dessa forma.
*/
```
