#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gl_canvas2d.h"
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Virabrequim.h"
#include "Pistao.h"
#include "Biela.h"

#define ANGLE_FACTOR 0.05
#define DISTANCE_FACTOR 1

#define KEY_ROTATE_X_UP 'i'
#define KEY_ROTATE_X_DOWN 'o'
#define KEY_ROTATE_Y_UP 'k'
#define KEY_ROTATE_Y_DOWN 'l'
#define KEY_ROTATE_Z_UP 'n'
#define KEY_ROTATE_Z_DOWN 'm'

#define KEY_INCREASE_D 'w'
#define KEY_DECREASE_D 's'

//variavel global para selecao do que sera exibido na canvas.
int screenWidth = 800, screenHeight = 500; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;                        //variaveis globais do mouse para poder exibir dentro da render().

bool rotateZ = false;
bool showMotorDemo = false;

Virabrequim *vira;
Pistao *pistao;
Biela *biela;

vector<Object *> objects;

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

    ang += ANGLE_FACTOR;
}

void render() {
    if (showMotorDemo) {
        motor();
        return;
    }

    for (auto o : objects) {
        if (rotateZ) {
            o->rotate(o->getAngX(), o->getAngY(), o->getAngZ() + ANGLE_FACTOR);
        }
    }

    // TODO: passar o ponto original e transformar lá na biela
    // pega esse ponto original, adiciona a altura  e transforma
    biela->connect(vira->getPtConnection(), 0);
    pistao->connect(biela->getConnectionPistao());

    for (auto o : objects) {
        o->render();
    }
}

void keyboard(int key) {
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

void keyboardUp(int key) {
    float angX = 0, angY = 0, angZ = 0;

    switch (key) {
    case ' ':
        rotateZ = !rotateZ;
        break;

    case '1':
        showMotorDemo = !showMotorDemo;
        break;

    case KEY_ROTATE_X_UP:
        for (auto o : objects) {
            angX = o->getAngX() + ANGLE_FACTOR;
            angY = o->getAngY();
            angZ = o->getAngZ();
            o->rotate(angX, angY, angZ);
        }
        break;

    case KEY_ROTATE_X_DOWN:
        for (auto o : objects) {
            angX = o->getAngX() - ANGLE_FACTOR;
            angY = o->getAngY();
            angZ = o->getAngZ();
            o->rotate(angX, angY, angZ);
        }
        break;

    case KEY_ROTATE_Y_UP:
        for (auto o : objects) {
            angX = o->getAngX();
            angY = o->getAngY() + ANGLE_FACTOR;
            angZ = o->getAngZ();
            o->rotate(angX, angY, angZ);
        }
        break;

    case KEY_ROTATE_Y_DOWN:
        for (auto o : objects) {
            angX = o->getAngX();
            angY = o->getAngY() - ANGLE_FACTOR;
            angZ = o->getAngZ();
            o->rotate(angX, angY, angZ);
        }
        break;

    case KEY_ROTATE_Z_UP:
        for (auto o : objects) {
            angX = o->getAngX();
            angY = o->getAngY();
            angZ = o->getAngZ() + ANGLE_FACTOR;
            o->rotate(angX, angY, angZ);
        }
        break;

    case KEY_ROTATE_Z_DOWN:
        for (auto o : objects) {
            angX = o->getAngX();
            angY = o->getAngY();
            angZ = o->getAngZ() - ANGLE_FACTOR;
            o->rotate(angX, angY, angZ);
        }
        break;

    case KEY_INCREASE_D:
        for (auto o : objects) {
            o->setDistance(o->getDistance() + DISTANCE_FACTOR);
        }
        break;

    case KEY_DECREASE_D:
        for (auto o : objects) {
            o->setDistance(o->getDistance() - DISTANCE_FACTOR);
        }
        break;

    default:
        return;
    }
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;
}

int main() {
    // z+ para dentro da tela
    Point center = Point(0, 0, 0);

    vira = new Virabrequim(10, 70, center);
    vira->translate(Point(300, 300, 0));

    biela = new Biela(80, center);
    biela->translate(Point(300, 300, 0));

    pistao = new Pistao(center);
    pistao->translate(Point(300, 300, 0));

    objects.push_back(vira);
    objects.push_back(biela);
    // objects.push_back(pistao);

    initCanvas(&screenWidth, &screenHeight, "Trabalho Final");
    runCanvas();
}
