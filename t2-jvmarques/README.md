## Instruções para uso
---
O programa é capaz de desenhar 3 tipos de figuras:  

1 - Retângulo  
2 - Linha  
3 - Curva com 2 pontos de controle

### Arquivo para ler/salvar
---
O arquivo se encontra em `./resources/teste.jv` e já possui algumas figuras salvas. Todas as operações com arquivos (carregar e salvar) são realizadas sobre esse arquivo.

### Teclas para Comandos
---
As teclas usadas para dar comandos (emulando cliques em botões) estão no arquivo `Constants.h`.

**1** Clique para desenhar uma linha  
**2** Clique para desenhar um retângulo  
**3** Clique para desenhar uma curva  
**r** Rotaciona a figura selecionada para a direita  
**l** Rotaciona a figura selecionada para a esquerda  
**c** Remove todas as figuras da tela (limpa tela)  
**d** Remove a figura selecionada da tela  
**o** Carrega as figuras salvas no arquivo  
**s** Salva as figuras desenhas no arquivo  


### Como desenhar
---
Linhas e retângulos são desenhdos da mesma forma: clica no primeiro ponto, segura e arrasta até o segundo ponto.

Ao clicar para desenhar uma figura não será possível desenhar outra figura até que a figura seja desenhada.

**Linha e Retângulo** 
Clique e segure no primeiro ponto e arraste até o segundo ponto.

**Curva**
A curva é composta por 4 pontos: 1 ponto inicial, um ponto final e 2 de controle.

A ordem dos pontos clicados na tela é: inicial, controle, controle, final.

Portanto, quando quiser desenhar uma curva cliquena tela para fazer a marcação dos pontos. Ao clicar na tela vai aarecer um ponto indicando que o ponto foi contabilizado. Prossiga até finalizar os 4 pontos.

### Selecionando figuras
---
Todas as figuras são selecionáveis. Se não existem figuras a serem desenhadas na tela, ou seja, se nenhum dos botões para desenhar figuras foi pressionado, cada clique do mouse vai verificar se está sobre a área da figura. 

**Linhas e Retângulos**  
A área selecionável dessas duas figuras é tratada da mesma forma: como um retângulo. A linha é formada por 2 pontos, então sua área selecionada vai ser um retângulo com esses dois pontos. Com o retângulo acontece da mesma forma.

**Obs**.: Todas as figuras selecionadas são desenhadas com pontos em suas extremidades da área selecionável. Ao desenhar uma linha vão ser desenhados 4 pontos que compõem o retângulo de sua área selecionável, mas que desaparecem após a figura ser desselecionada.

**Curva**  
A área da curva é semelhante: um retângulo circunscrito na curva.

### Movendo figuras
---
Uma vez selecionada, a figura pode ser movida. Para isso basta selecionar a figura com o mouse, pressionar e arrastar.
