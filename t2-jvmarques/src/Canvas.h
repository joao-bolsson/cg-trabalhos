#ifndef __CANVAS__H__
#define __CANVAS__H__

#include "MainWindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#define PI_2 6.28318530717958

#define Y_CANVAS_CRESCE_PARA_CIMA 0

class Canvas {

private:
    MainWindow *window;

public:
    Canvas();
    ~Canvas();

    void setWindow(MainWindow *window);

    void point(int x, int y);
    void line(int x1, int y1, int x2, int y2);

    void rect(int x1, int y1, int x2, int y2);
    void rectFill(int x1, int y1, int x2, int y2);

    void polygon(float vx[], float vy[], int n_elems);
    void polygonFill(float vx[], float vy[], int n_elems);

    void circle(int x, int y, int raio, int div);
    void circleFill(int x, int y, int raio, int div);

    void color(float r, float g, float b);
    void clear(float r, float g, float b);

    void text(int x, int y, const char *t);

    //funcoes de CALLBACK da biblioteca ()
    void keyboard(int key);
    void keyboardUp(int key);
    void specialUp(int key);
    void mouse(int bt, int st, int wheel, int direction, int x, int y);
    void render();
    void mouseWheelCB(int wheel, int direction, int x, int y);
    void mouseClick(int button, int state, int x, int y);
    void reshape(int w, int h);
    void inicializa();
    void display();
    void ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y);

    //funcao de inicializacao da Canvas2D. Recebe a largura e altura
    void initCanvas(int *w, int *h, const char *title);

    void runCanvas();
};

#endif
