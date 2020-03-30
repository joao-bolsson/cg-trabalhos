#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gl_canvas2d.h"

#include "AbstractButton.h"
#include "Button.h"
#include "Bmp.h"
#include "Image.h"
#include "Pixel.h"
#include "Util.h"

#define PATH_TO_IMG "./t1-jvmarques/resources/img.bmp"
#define SCREEN_X 900
#define SCREEN_Y 300
#define RECT_SIZE 10
#define TEXT_COORD 2

Bmp *img;
unsigned char *imgData = NULL;

// TODO: how iterate through this array without knowing its size
AbstractButton **buttons = NULL;
int numberOfBtns = 2;

Image *image = NULL;
Pixel **pixels = NULL;

//variavel global para selecao do que sera exibido na canvas.
int opcao = 50;
int screenWidth = 800, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;                        //variaveis globais do mouse para poder exibir dentro da render().

void render() {
    clear(0, 0, 0);
    image->render();

    for (int i = 0; i < numberOfBtns; i++) {
        buttons[i]->render();
    }
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key) {
    printf("\nTecla: %d", key);
    if (key < 200) {
        opcao = key;
    }

    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key) {
    printf("\nLiberou: %d", key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    if (state == 0) {
        // TODO: verificar se o x, y está sobre algum botao, se está, chamar bt->doClick()
    }
}

int main(void) {
    initCanvas(&screenWidth, &screenHeight, "Trabalho 1 - Pressione 1, 2, 3");

    img = new Bmp(PATH_TO_IMG);
    img->convertBGRtoRGB();
    imgData = img->getImage();

    pixels = Util::getImagePixels(imgData, img->getWidth(), img->getHeight());

    image = new Image(pixels, 50, 50, img->getWidth(), img->getHeight());

    buttons = new AbstractButton *[2];
    buttons[0] = new Button("Ampliar", screenWidth - 100, (screenHeight / 2) - 25, 100, 50);
    buttons[1] = new Button("Reduzir", screenWidth - 100, (screenHeight / 2) + 25, 100, 50);

    runCanvas();
}
