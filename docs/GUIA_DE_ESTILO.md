# Guia de Estilo
Este guia serve de referência para o estilo de código adotado nesse projeto, a fim de padronizar o aspecto geral da _codebase_.

# Estilo do Código
## 1.0 Identação e espaços
- Utilizar identação de quatro caracteres de espaços.
- Exceto ao chamar funções, utilizar espaço em parênteses, chaves iniciais, operadores lógicos e declaração de variáveis.
```c
// ruim
for(int i=0;i<666;++i){
    printf("%d\n", i);
}

int i=0;

// bom
for (int i = 0; i < 666; ++i) {
    printf("%d\n", i);
}

int i = 0;
```

## 2.0 Condicionais, funções e laços
- Evitar o uso de condicionais ou laços de uma única linha ou sem chaves:
```c
// ruim
if (a == b) return true;

while (a > b) a--;

for (int i = 0; i < 10; ++i)
    printf("%d\n", i);

// bom
if (a == b) {
    return true;
}

while (a > b) {
    a--;
}

for (int i = 0; i < 10; ++i) {
    printf("%d\n", i);
}

```

## 3.0 Prototipação
- Evitar protótipos de função com parâmetro sem nome, pois isso deixa a definição confusa.
```c
// ruim
int soma(int, int);

// bom
int soma(int n1, int n2);
```

## 4.0 Nomes de variáveis
- Utilizar camel case e nomes descritivos.
- Constantes e macros podem ter underline.
```c
// ruim
int nome_de_variavel;
float NomeDeVariavel;

char *nmPers = "Lorde C";

// bom
int nomeDeVariavel;
#define NOME_DE_CONSTANTE 0

char *nomeDePersonagem = "Lorde C";
```

## 5.0 Ponteiros
- Evitar referenciação e desreferenciação com operadores `&` e `*` quando desnecessários e comprometem clareza do código.
```c
// ruim
int n[5];
*(n + 3) = 2;

// bom
n[3] = 2;
```

## 6.0 Comentários
- Sempre comente para o máximo de clareza, exceto se a instrução for totalmente auto descritiva.
```c
// comentário de uma única linha.

/*
    comentário de múltiplas linhas
    devem ser escritos dessa forma.
*/
```

# Nomeação de Branches
- Branches devem seguir ser nomeadas no padrão `CATEGORIA/NOME`.
- Nomes devem ser descritivos e separados por hífen.
    - Exemplo: `feature/sistema-de-dialogo`.
- Nas categorias bugfix e hotfix, inicie o nome com o número do issue.
    - Exemplo: `bugfix/2-script-de-configuracao`.

Categoria | Propósito
--- | ---
feature | Adição de nova funcionalidade.
bugfix | Correção de bugs encontrados na secção de Issues.
hotfix | Bugs críticos que já estão em produção.
docs | Adição/correção de documentação e descrições do repositório.

## 1.0
