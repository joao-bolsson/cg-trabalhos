#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Motor.h"
#include "Button.h"

#define BTN_HEIGHT 40
#define ANGLE_FACTOR 0.05
#define DISTANCE_FACTOR 1
#define MOVE_FACTOR 5

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

Motor *motor;

vector<AbstractButton *> buttons;

// CÓDIGO TESTE APENAS PARA TRAB FINAL
float ang = 0;
void motorDemo() {
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
    for (auto button : buttons) {
        button->render();
    }

    if (showMotorDemo) {
        motorDemo();
        return;
    }

    if (rotateZ) {
        motor->rotate(motor->getAngX(), motor->getAngY(), motor->getAngZ() + ANGLE_FACTOR);
    }
    motor->render();
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
    case '0':
        motor->rotate(0, 0, PI / 2);

        break;
    case ' ':
        rotateZ = !rotateZ;
        break;

    case 'r': // reseta
        motor->rotate(0, 0, 0);

        break;

    case '1':
        showMotorDemo = !showMotorDemo;
        break;

    case KEY_ROTATE_X_UP:
        angX = motor->getAngX() + ANGLE_FACTOR;
        angY = motor->getAngY();
        angZ = motor->getAngZ();
        motor->rotate(angX, angY, angZ);

        break;

    case KEY_ROTATE_X_DOWN:
        angX = motor->getAngX() - ANGLE_FACTOR;
        angY = motor->getAngY();
        angZ = motor->getAngZ();
        motor->rotate(angX, angY, angZ);

        break;

    case KEY_ROTATE_Y_UP:
        angX = motor->getAngX();
        angY = motor->getAngY() + ANGLE_FACTOR;
        angZ = motor->getAngZ();
        motor->rotate(angX, angY, angZ);

        break;

    case KEY_ROTATE_Y_DOWN:
        angX = motor->getAngX();
        angY = motor->getAngY() - ANGLE_FACTOR;
        angZ = motor->getAngZ();
        motor->rotate(angX, angY, angZ);
        break;

    case KEY_ROTATE_Z_UP:
        angX = motor->getAngX();
        angY = motor->getAngY();
        angZ = motor->getAngZ() + ANGLE_FACTOR;
        motor->rotate(angX, angY, angZ);
        break;

    case KEY_ROTATE_Z_DOWN:
        angX = motor->getAngX();
        angY = motor->getAngY();
        angZ = motor->getAngZ() - ANGLE_FACTOR;
        motor->rotate(angX, angY, angZ);
        break;

    case KEY_INCREASE_D:
        motor->setDistance(motor->getDistance() + DISTANCE_FACTOR);
        break;

    case KEY_DECREASE_D:
        motor->setDistance(motor->getDistance() - DISTANCE_FACTOR);
        break;

    default:
        return;
    }
}

void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    // printf("button: %d, st: %d, wh: %d, dir: %d\n", button, state, wheel, direction);

    if (button == 0 && state == 0) { // click
        for (auto btn : buttons) {
            if (btn->isPointOver(x, y)) {
                btn->doClick();
                return;
            }
        }
    }
}

void btnMoveLeft() {
    printf("[info] Button to move left pressed\n");
    Point p = motor->getTranslatePoint();
    p.setX(p.getX() - MOVE_FACTOR);
    motor->translate(p);
}

void btnMoveRight() {
    printf("[info] Button to move right pressed\n");
    Point p = motor->getTranslatePoint();
    p.setX(p.getX() + MOVE_FACTOR);
    motor->translate(p);
}

void btnMoveUp() {
    printf("[info] Button to move up pressed\n");
    Point p = motor->getTranslatePoint();
    p.setY(p.getY() + MOVE_FACTOR);
    motor->translate(p);
}

void btnMoveDown() {
    printf("[info] Button to move down pressed\n");
    Point p = motor->getTranslatePoint();
    p.setY(p.getY() - MOVE_FACTOR);
    motor->translate(p);
}

int main() {
    int btnY = screenHeight - BTN_HEIGHT;
    Button *buttonMoveLeft = new Button("<-", (screenWidth / 2) - 15, btnY, 30, BTN_HEIGHT);
    Button *buttonMoveRight = new Button("->", (screenWidth / 2) + 15, btnY, 30, BTN_HEIGHT);
    Button *buttonMoveUp = new Button("up", (screenWidth / 2) + 60, btnY, 30, BTN_HEIGHT);
    Button *buttonMoveDown = new Button("down", (screenWidth / 2) + 90, btnY, 50, BTN_HEIGHT);

    buttonMoveLeft->setAction(btnMoveLeft);
    buttonMoveRight->setAction(btnMoveRight);
    buttonMoveUp->setAction(btnMoveUp);
    buttonMoveDown->setAction(btnMoveDown);

    buttons.push_back(buttonMoveLeft);
    buttons.push_back(buttonMoveRight);
    buttons.push_back(buttonMoveUp);
    buttons.push_back(buttonMoveDown);

    // z+ para dentro da tela
    Point center = Point(0, 0, 0);

    int viraLength = 40;
    int pistaoLength = 20;
    int pistaoRadius = 10;

    motor = new Motor(center, viraLength, pistaoLength, pistaoRadius);
    motor->translate(Point(300, 300, 0));

    initCanvas(&screenWidth, &screenHeight, "Trabalho Final");
    runCanvas();
}
