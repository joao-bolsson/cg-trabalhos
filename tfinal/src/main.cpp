#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gl_canvas2d.h"
#include "Cube.h"

//variavel global para selecao do que sera exibido na canvas.
int screenWidth = 800, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;                        //variaveis globais do mouse para poder exibir dentro da render().

Cube *c;

// CÓDIGO TESTE APENAS PARA TRAB FINAL
float ang = 0;
void motor() {
    color(0, 1, 0);
    float translacao = 100; //posicao onde mostrar na tela.

    //virabrequim - coordenadas polares
    float raioVirabrequim = 50;
    float xVirabrequim = raioVirabrequim * cos(ang);
    float yVirabrequim = raioVirabrequim * sin(ang);
    circle(translacao, translacao, 3, 10);
    line(xVirabrequim + translacao, yVirabrequim + translacao, translacao, translacao);
    circle(xVirabrequim + translacao, yVirabrequim + translacao, 3, 10);

    //pistao - pitagoras
    float hipotenusa = 80;                                                      //hipotenusa representa o comprimento da biela
    float cateto = sqrt(hipotenusa * hipotenusa - xVirabrequim * xVirabrequim); //pitagoras  hip^2 = cat^2 + cat^2
    float xPistao = 0;
    float yPistao = cateto + yVirabrequim;
    circle(xPistao + translacao, yPistao + translacao, 3, 10);

    //biela
    line(xVirabrequim + translacao, yVirabrequim + translacao, xPistao + translacao, yPistao + translacao);

    ang += 0.03;
}

void render() {
    c->render();
    // motor();
}

void keyboard(int key) {
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

void keyboardUp(int key) {
    // empty
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;
}

int main() {
    c = new Cube(100, -50, -50, -50);

    initCanvas(&screenWidth, &screenHeight, "Trabalho Final");
    runCanvas();
}
