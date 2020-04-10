#include "MainWindow.h"

#include "Constants.h"
#include "Shape.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool drawLine = false, drawRectangle = false, drawCurve = false;
bool mouseMoved = false;
vector<Shape *> shapes;

// pressed point on canvas
vector<Point> points;

Shape *demo = new Shape();
Shape *selectedShape = new Shape();
Shape *shapeCopy = new Shape();

Point mousePointPressed = Point(-1, -1);

Point selectedPointCopy = Point(-1, -1);

// index do ponto de controle da curva que esta sendo editado -2: nenhum sendo editado
int indexPoint = -2;

Canvas *canvas;

MainWindow::MainWindow(int width, int height, char *title) {
    canvas = new Canvas();
}

/**
 * @brief  Method called to clear any selection on canvas.
 */
void clearSelection() {
    mousePointPressed = Point(-1, -1);
    selectedShape = new Shape();
    selectedPointCopy = Point(-1, -1);
    indexPoint = -2;
}

/**
 * @brief Method called to start drawing a line. 
 */
void btnLine() {
    printf("[debug] Button to draw line pressed\n");
    drawLine = true;
    drawRectangle = false;
    clearSelection();
}

MainWindow::~MainWindow() {
    delete canvas;
}

void reshape(int w, int h) {
    canvas->reshape(w, h);
}

void display() {
    canvas->display();
}

void keyb(unsigned char key, int, int) {
    canvas->keyboard(key);
    if (key == KEY_4_LINE) {
        btnLine();
        return;
    }
}

void keybUp(unsigned char key, int, int) {
    canvas->keyboardUp(key);
}

void mouseClick(int button, int state, int x, int y) {
    canvas->mouseClick(button, state, x, y);
}

void mouseWheelCB(int wheel, int direction, int x, int y) {
    canvas->mouseWheelCB(wheel, direction, x, y);
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

void MainWindow::renderComponents() {
    // TODO: render
    canvas->color(1, 0, 1);
    canvas->rect(10, 10, 100, 200);
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
    canvas->setWindow(this);
    canvas->initCanvas(&width, &height, title);
    init();
    canvas->runCanvas();
}