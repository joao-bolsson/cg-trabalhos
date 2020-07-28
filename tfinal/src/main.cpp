#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Motor.h"
#include "Button.h"
#include "Checkbox.h"

#define BTN_HEIGHT 30
#define ANGLE_FACTOR 0.05
#define DISTANCE_FACTOR 2
#define MOVE_FACTOR 5

#define KEY_RESET 'r'
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

bool showVira = true;
bool showBiela = true;
bool showPistao = true;
bool showCamisa = true;

Motor *motor;

vector<AbstractButton *> buttons;

double rpmFactor = 0.05;

void render() {
    for (auto button : buttons) {
        button->render();
    }

    if (rotateZ) {
        motor->rotate(motor->getAngX(), motor->getAngY(), motor->getAngZ() + rpmFactor);
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

void btnReset() {
    motor->rotate(0, 0, 0);
}

void btnRotateXUp() {
    motor->rotate(motor->getAngX() + ANGLE_FACTOR, motor->getAngY(), motor->getAngZ());
}

void btnRotateXDown() {
    motor->rotate(motor->getAngX() - ANGLE_FACTOR, motor->getAngY(), motor->getAngZ());
}

void btnRotateYUp() {
    motor->rotate(motor->getAngX(), motor->getAngY() + ANGLE_FACTOR, motor->getAngZ());
}

void btnRotateYDown() {
    motor->rotate(motor->getAngX(), motor->getAngY() - ANGLE_FACTOR, motor->getAngZ());
}

void btnRotateZUp() {
    motor->rotate(motor->getAngX(), motor->getAngY(), motor->getAngZ() + ANGLE_FACTOR);
}

void btnRotateZDown() {
    motor->rotate(motor->getAngX(), motor->getAngY(), motor->getAngZ() - ANGLE_FACTOR);
}

void keyboardUp(int key) {
    switch (key) {
    case ' ':
        rotateZ = !rotateZ;
        break;

    case KEY_RESET: // reseta
        btnReset();
        break;

    case KEY_ROTATE_X_UP:
        btnRotateXUp();
        break;

    case KEY_ROTATE_X_DOWN:
        btnRotateXDown();
        break;

    case KEY_ROTATE_Y_UP:
        btnRotateYUp();
        break;

    case KEY_ROTATE_Y_DOWN:
        btnRotateYDown();
        break;

    case KEY_ROTATE_Z_UP:
        btnRotateZUp();
        break;

    case KEY_ROTATE_Z_DOWN:
        btnRotateZDown();
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

    if (button == 0 && state == 0) { // click
        for (auto btn : buttons) {
            if (btn->isPointOver(x, y)) {
                btn->doClick();
                return;
            }
        }
    } else if (button == 3) {
        motor->setDistance(motor->getDistance() - DISTANCE_FACTOR);
    } else if (button == 4) {
        motor->setDistance(motor->getDistance() + DISTANCE_FACTOR);
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

void btnRPMUp() {
    printf("[info] Button +RPM pressed\n");
    rpmFactor += ANGLE_FACTOR;
}

void btnRPMDown() {
    printf("[info] Button -RPM pressed\n");
    rpmFactor -= ANGLE_FACTOR;
}

void btnStop() {
    rotateZ = false;
}

void btnPlay() {
    rotateZ = true;
}

void actShowVirabrequim() {
    showVira = !showVira;
    motor->setShowVira(showVira);
}

void actShowBiela() {
    showBiela = !showBiela;
    motor->setShowBiela(showBiela);
}

void actShowPistao() {
    showPistao = !showPistao;
    motor->setShowPistao(showPistao);
}

void actShowCamisa() {
    showCamisa = !showCamisa;
    motor->setShowCamisa(showCamisa);
}

void actShow2d() {
    motor->setShow2d(!motor->isShow2d());
}

int main() {
    int btnY = screenHeight - BTN_HEIGHT;
    Button *buttonMoveLeft = new Button("<-", (screenWidth / 2) - 15, btnY, 30, BTN_HEIGHT);
    Button *buttonMoveRight = new Button("->", (screenWidth / 2) + 15, btnY, 30, BTN_HEIGHT);
    Button *buttonMoveUp = new Button("up", (screenWidth / 2) + 60, btnY, 30, BTN_HEIGHT);
    Button *buttonMoveDown = new Button("down", (screenWidth / 2) + 90, btnY, 50, BTN_HEIGHT);
    Button *buttonRPMUp = new Button("+RPM", 0, btnY, 60, BTN_HEIGHT);
    Button *buttonRPMDown = new Button("-RPM", 70, btnY, 60, BTN_HEIGHT);
    Button *buttonReset = new Button("reset", screenWidth - 60, btnY, 60, BTN_HEIGHT);
    Button *buttonStop = new Button("stop", screenWidth - 60, btnY - BTN_HEIGHT * 3, 60, BTN_HEIGHT);
    Button *buttonPlay = new Button("play", screenWidth - 60, btnY - BTN_HEIGHT * 4, 60, BTN_HEIGHT);

    short gap = 10;
    Button *buttonRotateXDown = new Button("-x", screenWidth - 30, 0, 30, BTN_HEIGHT);
    Button *buttonRotateXUp = new Button("+x", screenWidth - 30, BTN_HEIGHT + gap, 30, BTN_HEIGHT);
    Button *buttonRotateYDown = new Button("-y", screenWidth - 30, (BTN_HEIGHT + gap) * 2, 30, BTN_HEIGHT);
    Button *buttonRotateYUp = new Button("+y", screenWidth - 30, (BTN_HEIGHT + gap) * 3, 30, BTN_HEIGHT);
    Button *buttonRotateZDown = new Button("-z", screenWidth - 30, (BTN_HEIGHT + gap) * 4, 30, BTN_HEIGHT);
    Button *buttonRotateZUp = new Button("+z", screenWidth - 30, (BTN_HEIGHT + gap) * 5, 30, BTN_HEIGHT);

    int yCheckbox = 0;

    Checkbox *checkShowVirabrequim = new Checkbox("Virabrequim", 0, yCheckbox, true);
    Checkbox *checkShowBiela = new Checkbox("Biela", 0, yCheckbox + CHECKBOX_SIZE + gap, true);
    Checkbox *checkShowPistao = new Checkbox("Pistao", 0, yCheckbox + (CHECKBOX_SIZE + gap) * 2, true);
    Checkbox *checkShowCamisa = new Checkbox("Camisa", 0, yCheckbox + (CHECKBOX_SIZE + gap) * 3, true);

    Checkbox *checkShow2d = new Checkbox("mostra 2d", 0, yCheckbox + (CHECKBOX_SIZE + gap) * 5);

    buttonMoveLeft->setAction(btnMoveLeft);
    buttonMoveRight->setAction(btnMoveRight);
    buttonMoveUp->setAction(btnMoveUp);
    buttonMoveDown->setAction(btnMoveDown);
    buttonRPMUp->setAction(btnRPMUp);
    buttonRPMDown->setAction(btnRPMDown);
    buttonReset->setAction(btnReset);
    buttonStop->setAction(btnStop);
    buttonPlay->setAction(btnPlay);

    buttonRotateXDown->setAction(btnRotateXDown);
    buttonRotateXUp->setAction(btnRotateXUp);
    buttonRotateYDown->setAction(btnRotateYDown);
    buttonRotateYUp->setAction(btnRotateYUp);
    buttonRotateZDown->setAction(btnRotateZDown);
    buttonRotateZUp->setAction(btnRotateZUp);

    checkShowVirabrequim->setAction(actShowVirabrequim);
    checkShowBiela->setAction(actShowBiela);
    checkShowPistao->setAction(actShowPistao);
    checkShowCamisa->setAction(actShowCamisa);
    checkShow2d->setAction(actShow2d);

    buttons.push_back(buttonMoveLeft);
    buttons.push_back(buttonMoveRight);
    buttons.push_back(buttonMoveUp);
    buttons.push_back(buttonMoveDown);
    buttons.push_back(buttonRPMUp);
    buttons.push_back(buttonRPMDown);
    buttons.push_back(buttonReset);
    buttons.push_back(buttonStop);
    buttons.push_back(buttonPlay);
    buttons.push_back(buttonRotateXUp);
    buttons.push_back(buttonRotateXDown);
    buttons.push_back(buttonRotateYUp);
    buttons.push_back(buttonRotateYDown);
    buttons.push_back(buttonRotateZUp);
    buttons.push_back(buttonRotateZDown);

    buttons.push_back(checkShowVirabrequim);
    buttons.push_back(checkShowBiela);
    buttons.push_back(checkShowPistao);
    buttons.push_back(checkShowCamisa);
    buttons.push_back(checkShow2d);

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
