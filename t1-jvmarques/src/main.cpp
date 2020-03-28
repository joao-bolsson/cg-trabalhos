#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gl_canvas2d.h"

#include "Bmp.h"
#include "Bola.h"
#include "Relogio.h"
#include "Botao.h"

#define SCREEN_X 900
#define SCREEN_Y 300
#define RECT_SIZE 10
#define TEXT_COORD 2

Bmp *img1;
unsigned char *data;

Bola *b = NULL;
Relogio *r = NULL;
Botao *bt = NULL; //se a aplicacao tiver varios botoes, sugiro implementar um manager de botoes.

//variavel global para selecao do que sera exibido na canvas.
int opcao = 50;
int screenWidth = 500, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;                        //variaveis globais do mouse para poder exibir dentro da render().

void DesenhaSenoide()
{
   float x = 0, y;
   color(0, 1, 0);
   for (float i = 0; i < 68; i += 0.001)
   {
      y = sin(i) * 50;
      point((int)x, (int)y + 100);
      x += 0.01;
   }
}

void DesenhaLinhaDegrade()
{
   for (float i = 0; i < 350; i++)
   {
      color(i / 200, i / 200, i / 200);
      point((int)(i + 100), (int)(240));
   }
}

void DrawMouseScreenCoords()
{
   char str[100];
   sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
   text(10, 300, str);
   sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
   text(10, 320, str);
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
void render()
{
   text(20, 500, "Trabalho 1 - isso é um texto");

   DrawMouseScreenCoords();

   bt->Render();

   DesenhaLinhaDegrade();

   if (opcao == 49) //'1' -> relogio
   {
      r->anima();
   }
   if (opcao == '2') //50 -> bola
   {
      b->anima();
   }
   if (opcao == 51) //'3' -> senoide
   {
      DesenhaSenoide();
   }
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   printf("\nTecla: %d", key);
   if (key < 200)
   {
      opcao = key;
   }

   switch (key)
   {
   case 27:
      exit(0);
      break;

      //seta para a esquerda
   case 200:
      b->move(-10);
      break;

   //seta para a direita
   case 202:
      b->move(10);
      break;
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d", key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   // printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction, x, y);

   if (state == 0) //clicou
   {
      if (bt->Colidiu(x, y))
      {
         printf("\nClicou no botao\n");
      }
   }
}

int main(void)
{
   initCanvas(&screenWidth, &screenHeight, "Trabalho 1 - Pressione 1, 2, 3");

   img1 = new Bmp(".\\gl_1_canvas\\resources\\img.bmp");
   img1->convertBGRtoRGB();
   data = img1->getImage();

   b = new Bola();
   r = new Relogio();
   bt = new Botao(200, 400, 140, 50, "Sou um botao");

   runCanvas();
}
