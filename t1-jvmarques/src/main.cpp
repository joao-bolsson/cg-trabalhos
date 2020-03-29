#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gl_canvas2d.h"

#include "Bmp.h"
#include "Relogio.h"
#include "Botao.h"
#include "Pixel.h"
#include "Util.h"

#define PATH_TO_IMG "./t1-jvmarques/resources/img.bmp"
#define SCREEN_X 900
#define SCREEN_Y 300
#define RECT_SIZE 10
#define TEXT_COORD 2

Bmp *img;
unsigned char *imgData = NULL;

Pixel **pixels = NULL;
Relogio *r = NULL;
Botao *bt = NULL; //se a aplicacao tiver varios botoes, sugiro implementar um manager de botoes.

//variavel global para selecao do que sera exibido na canvas.
int opcao = 50;
int screenWidth = 500, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;                        //variaveis globais do mouse para poder exibir dentro da render().

void drawImage()
{
   if (img != NULL && imgData != NULL)
   {
      int size = img->getImageSize();
      for (int i = 0; i < size; i++)
      {
         printf("data[%d]: %d", i, imgData[i]);
      }
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

   // drawImage();

   DrawMouseScreenCoords();

   bt->Render();

   DesenhaLinhaDegrade();

   if (opcao == 49) //'1' -> relogio
   {
      r->anima();
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

   img = new Bmp(PATH_TO_IMG);
   img->convertBGRtoRGB();
   imgData = img->getImage();

   pixels = Util::getImagePixels(imgData, img->getWidth(), img->getHeight());

   for (int i = 0; i < img->getHeight(); i++)
   {
      for (int j = 0; j < img->getWidth(); j++)
      {
         Pixel p = pixels[i][j];
      }
   }

   r = new Relogio();
   bt = new Botao(200, 400, 140, 50, "Sou um botao");

   runCanvas();
}
