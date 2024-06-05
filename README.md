<h1 align="center">Projeto da UC de Computação Gráfica - 2023/2024</h1>
<h2 align="center">Engine 3D</h2>

## Definição
Engine 3D gráfica para visualização de primitivas (figuras geométricas) e criação de cenas gráficas.

## Notas do repositório
- Neste repositório existem 4 versões deste projeto representando as 4 fases.
- As fases 1, 2 e 3 representam etapas do projeto que não foram alteradas desde a sua entrega (sendo estas as menos instáveis).
- Estas fases também contém testes especificados para cada uma, que mostram o estado do projeto em cada fase.
- A fase 4 é a fase final e a mais estável e contém os testes de todas as fases (a fase que deve ser usada para execução do projeto).
- Cada fase é compatível com todas as fases seguintes, mas não existe retrocompatibilidade entre fases (testes da fase N não funcionam em qualquer fase < N).

## Visão geral dos programas
### Generator
- Programa de execução imediata (sem interação).
- Criação de ficheiros formatados com a primitiva gerada para execução (detalhado em [Funcionalidades](#funcionalidades)).

### Engine
- Programa que cria cenas visuais das primitivas geradas pelo gerador.
- É interativa.

## Funcionalidades
### Diretórios
Nota: Todos os comandos que serão listados aqui podem assumir dois ```PWD```: 
- Para compilação o ```PWD``` é a raiz deste repositório.
- Para execução, o ```PWD``` deve ser alterado para ```/FASEN/build```
```console
cd FASEN
cd build
```
Onde ```N``` representa o número da fase.

### Compilação
Nota: Este projeto utiliza o CMake para compilação pelo que deve ser instalado.
- Cada fase pode ser compilada individualmente com o comando
```console
make build_fN
```
Onde ```N``` representa o número da fase.
- Ou então é possível compilar tudo ao mesmo tempo com o comando
```console
make
```

### Generator

### Engine

## Conclusão
Trabalho realizado por Pedro Silva, António Silva, Diogo Barros e Duarte Leitão no âmbito da UC de Computação Gráfica.
