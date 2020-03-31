#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gl_canvas2d.h"

#include "AbstractButton.h"
#include "Button.h"
#include "Checkbox.h"
#include "Bmp.h"
#include "Image.h"
#include "Pixel.h"
#include "Histogram.h"
#include "Util.h"

#define PATH_TO_IMG "./t1-jvmarques/resources/img.bmp"
#define BTN_HEIGHT 40

Bmp *img;
unsigned char *imgData = NULL;

// TODO: how iterate through this array without knowing its size
AbstractButton **buttons = NULL;
int numberOfBtns = 8;

Image *image = NULL;
Pixel **pixels = NULL;
Histogram *histogram = NULL;

//variavel global para selecao do que sera exibido na canvas.
int opcao = 50;
int screenWidth = 800, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;                        //variaveis globais do mouse para poder exibir dentro da render().

void render() {
    image->render();
    histogram->render();

    for (int i = 0; i < numberOfBtns; i++)
        buttons[i]->render();
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
        for (int i = 0; i < numberOfBtns; i++) {
            if (buttons[i]->isPointOver(x, y)) {
                buttons[i]->doClick();
                break;
            }
        }
    }
}

void zoomIn() {
    float currentScale = image->getScale();
    image->scale(currentScale * 2);
}

void zoomOut() {
    float currentScale = image->getScale();
    image->scale(currentScale / 2);
}

void showImgRed() {
    image->turnRedChannel();
}

void showImgGreen() {
    image->turnGreenChannel();
}

void showImgBlue() {
    image->turnBlueChannel();
}

void turnImgLuminance() {
    image->turnLuminance();
}

void addListeners() {
    buttons[0]->setAction(zoomIn);
    buttons[1]->setAction(zoomOut);

    buttons[4]->setAction(showImgRed);
    buttons[5]->setAction(showImgGreen);
    buttons[6]->setAction(showImgBlue);
    buttons[7]->setAction(turnImgLuminance);
}

int main(void) {
    initCanvas(&screenWidth, &screenHeight, "Trabalho 1 - Pressione 1, 2, 3");

    img = new Bmp(PATH_TO_IMG);
    img->convertBGRtoRGB();
    imgData = img->getImage();

    pixels = Util::getImagePixels(imgData, img->getWidth(), img->getHeight());

    image = new Image(pixels, 50, 50, img->getWidth(), img->getHeight());

    buttons = new AbstractButton *[numberOfBtns];
    buttons[0] = new Button("Ampliar", screenWidth - 100, (screenHeight / 2) - (BTN_HEIGHT / 2), 100, BTN_HEIGHT);
    buttons[1] = new Button("Reduzir", screenWidth - 100, (screenHeight / 2) + (BTN_HEIGHT / 2), 100, BTN_HEIGHT);

    // buttons to rotate, left and right
    buttons[2] = new Button("<-", (screenWidth / 2) - 15, screenHeight - BTN_HEIGHT, 30, BTN_HEIGHT);
    buttons[3] = new Button("->", (screenWidth / 2) + 15, screenHeight - BTN_HEIGHT, 30, BTN_HEIGHT);

    // r, g, b, y buttons
    buttons[4] = new Checkbox("R", image->getX(), image->getY() - CHECKBOX_SIZE);
    int space = CHECKBOX_SIZE + 15;
    buttons[5] = new Checkbox("G", image->getX() + space, image->getY() - CHECKBOX_SIZE);
    buttons[6] = new Checkbox("B", image->getX() + space * 2, image->getY() - CHECKBOX_SIZE);
    buttons[7] = new Checkbox("Y", image->getX() + space * 3, image->getY() - CHECKBOX_SIZE);

    histogram = new Histogram(image, image->getX() + image->getWidth() + 50, image->getY(), 300, 300);

    addListeners();
    runCanvas();
}
