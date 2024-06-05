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
A execução e explicação detalhada destes programas encontra-se [aqui](#funcionalidades)
### Generator
- Programa de execução imediata (sem interação).
- Criação de ficheiros formatados com a primitiva gerada para execução.

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
- Será criada a pasta ```build``` dentro da fase compilada com todos os artifactos da compilação (incluindo os executáveis).
- Este comando também gera automaticamente as primitivas necessárias para os testes dessa fase.
- As pastas ```build``` podem ser apagadas.
- Porém e recomendado fazer isso apenas quando necessário visto que contém ficheiros de cache que aceleram o processo de compilação.

### Generator
Este programa gera as primitivas em formato ```.3d``` para serem lidos pela engine.
- Para executar, no [diretório de execução](#diretórios) basta executar o comando
```console
./Release/generator "type" [args] "local_de_saida"
```
- Precisa de ser dado o local de saída que deve ser a pasta ```out``` da fase N (por predefinição os testes da engine usam essa pasta) como será exemplificado de seguida

#### Tipos de primitivas
##### Plano
- Um plano precisa do seu tamanho L (lado) e de divisões X (será criado um plano de lado L com X por X divisões
- Pode ser gerado assim:
```console
./Release/generator plane 2 3 ../FASEN/out/nome_do_ficheiro.3d
```

##### Caixa
- Uma caixa precisa das mesmas coisas que um plano visto que a caixa é constituída por 6 planos.
- Pode ser gerado assim:
```console
./Release/generator box 2 3 ../FASEN/out/nome_do_ficheiro.3d
```

##### Esfera
- Uma esfera precisa do seu raio, de slices e stacks. As stacks representam "linhas de latitude" e slices representam quantas divisões constituem cada stack
- Pode ser gerado assim:
```console
./Release/generator sphere 1 10 10 ../FASEN/out/nome_do_ficheiro.3d
```

##### Cone
- Um cone precisa de um raio da base, altura, slices e stacks (como a esfera)
- Pode ser gerado assim:
```console
./Release/generator cone 1 2 4 3 ../FASEN/out/nome_do_ficheiro.3d
```

##### Anel
- Um anel precisa de um raio interno, um raio externo e de divisões (quanto mais divisões mais detalhado o anel fica)
- Pode ser gerado assim:
```console
./Release/generator ring 1.5 2 40 ../FASEN/out/nome_do_ficheiro.3d
```

##### Patch
- O generator suporta geração de figuras através de patches de bezier. Este lê os pontos de control e cria os pontos da figura de acordo.
- Os pontos de controlo devem estar num ficheiro de formato .patch na pasta ```patches```.
- Precisa do ficheiro patch e da tesselação (tamanho das divisões, quanto mais, maior detalhe e menor performance).
- Pode ser gerado assim:
```console
./Release/generator patch ../FASEN/patches/teapot.patch 10 FASEN/out/bezier_10.3d
```

### Engine
Este programa cria cenas visuais com as primitivas geradas pelo gerador.
- Para executar a engine basta executar o comando no [diretório de execução](#diretórios):
```console
./Release/engine "xml_teste"
```
#### Ficheiros XML
As cenas devem ser escritas num ficheiro XML com um formato específico onde são dadas informações sobre a camera, luz, possíveis transformações nas figuras e cor.
- Os ficheiros de teste foram evoluindo ao longo das fases, logo não existir retrocompatibilidade entre as fases.
- A fase 4 contém todos os ficheiros de teste XML onde pode ser analisada a sua estrutura (pastas ```test```).
- Na fase 4 qualquer teste pode ser executado, tendo que ser o caminho para ele especificado.
- Por exemplo:
```console
./Release/engine ../test_files_4/test_4_3.xml
```
- A engine abrirá com a cena visual correspondente ao teste.

#### Controlos da engine
É possível interagir com a engine através de binds implementadas para isso:
  - Rodar a camera:
    - ```W```: Mover a camera para baixo
    - ```S```: Mover a camera para cima
    - ```A```: Mover a camera para direita
    - ```D```: Mover a camera para esquerda
  
  - Modo de visualização:
    - ```F```: Alterar para modo fill
    - ```L```: Alterar para o modo line (visualizar os triângulos)
    - ```P```: Alterar para o modo ponto (visualizar os pontos individuais)
   
  - Modo de desenho:
    - ```V```: Ativar/Desativar modo [VBO](#vbo)

  - Extra:
    - ```C```: Ativar/Desativar visualização das curvas de Catmull-Rom

#### VBO
A engine suporta dois modos de desenho das cenas:
- VBO Off:
  - Também conhecido como "modo clássico", desenha os pontos guardados em memória.
  - Performance reduzida, pois precisa de processamento para aceder à memória para ler os pontos.

- VBO On:
  - Carrega os pontos para a GPU (permite rápido acesso visto que as funcionalidades de desenho acontecem lá).
  - Considerável aumento da performance.

## Conclusão
Trabalho realizado por Pedro Silva, António Silva, Diogo Barros e Duarte Leitão no âmbito da UC de Computação Gráfica.
