#include "MainWindow.h"

Canvas *canvas;
MainWindow::MainWindow(int width, int height, char *title) {
    canvas = new Canvas();
}

MainWindow::~MainWindow() {
}

void reshape(int w, int h) {
    canvas->reshape(w, h);
}

void display() {
    canvas->display();
}

void keyb(unsigned char key, int, int) {
    canvas->keyboard(key);
}

void keybUp(unsigned char key, int, int) {
    canvas->keyboardUp(key);
}

void mouseClick(int button, int state, int x, int y) {
    canvas->ConvertMouseCoord(button, state, -2, -2, x, y);
}

void mouseWheelCB(int wheel, int direction, int x, int y) {
    canvas->ConvertMouseCoord(-2, -2, wheel, direction, x, y);
}

void motion(int x, int y) {
    canvas->ConvertMouseCoord(-2, -2, -2, -2, x, y);
}

void special(int key, int, int) {
    canvas->keyboard(key + 100);
}

void specialUp(int key, int, int) {
    canvas->keyboardUp(key + 100);
}

void MainWindow::init() {
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyb);
    glutKeyboardUpFunc(keybUp);
    glutSpecialUpFunc(specialUp);
    glutSpecialFunc(special);

    glutIdleFunc(display);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(motion);
    glutMotionFunc(motion);
    glutMouseWheelFunc(mouseWheelCB);
}

void MainWindow::show() {
    canvas->initCanvas(&width, &height, title);
    init();
    canvas->runCanvas();
}