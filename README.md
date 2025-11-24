# Logicus;
> [!WARNING]
> Em estagio inicial de desenvolvimento!

## Como compilar
### Dependências
- [W64-DevKit](https://github.com/skeeto/w64devkit) - Ambiente de desenvolvimento para C/C++. (Apenas no Windows)
- [RayLib](https://github.com/raysan5/raylib) - Biblioteca gráfica para desenvolvimento de jogos.
- [RayGui](https://github.com/raysan5/raygui) - Extensão da RayLib para desenvolver interfaces.

### Linux
Para compilar no Linux, será necessário instalar pacotes de desenvolvimento exigidos pelo RayLib de acordo com sua distribuição: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux

```bash
$ git clone https://github.com/baraunab/logicus-atp/
$ cd logicus-atp
$ bash ./configurar.sh
$ make
$ ./build/logicus
```
### Windows
```bash
$ git clone https://github.com/baraunab/logicus-atp/
$ cd logicus-atp
$ ./configurar.sh
$ make
$ ./build/logicus.exe
```
