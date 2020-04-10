#include "MainWindow.h"

#include "Constants.h"
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Rectangle.h"
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

void stopDrawing() {
    points.clear();
    drawLine = false;
    drawRectangle = false;
    mouseMoved = false;
    drawCurve = false;
    demo = new Shape();
    shapeCopy = new Shape();
    selectedPointCopy = Point(-1, -1);
    indexPoint = -2;
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

void mousePressEvent(int x, int y) {
    Point point = Point(x, y);
    // apenas adiciona pontos se tiver alguma coisa sendo desenhada
    if (drawLine || drawRectangle) {
        points.push_back(point);
    } else {
        selectedShape = new Shape();
        mousePointPressed = point;

        for (unsigned int i = 0; i < shapes.size(); i++) {
            if (shapes[i]->isSelected(mousePointPressed)) {
                selectedShape = shapes[i];
            }
        }
    }
}

void mouseReleaseEvent(int x, int y) {
    shapeCopy = new Shape();
    selectedPointCopy = Point(-1, -1);
    indexPoint = -2;
    if (!mouseMoved && !drawCurve) {
        stopDrawing();
    }

    // apenas adiciona pontos se tiver alguma coisa sendo desenhada
    if (drawLine || drawRectangle) {
        points.push_back(Point(x, y));

        if (points.size() == 2) {
            Point p1 = points[0];
            Point p2 = points[1];
            if (drawLine) {
                shapes.push_back(new Line(p1, p2));
            } else if (drawRectangle) {
                shapes.push_back(new RectangleC(p1, p2));
            }
            stopDrawing();
        }
    }
}

void mouseMoveEvent(int mX, int mY) {
    canvas->ConvertMouseCoord(-2, -2, -2, -2, mX, mY);
    Point p = canvas->getMousePoint();

    int x = p.getX();
    int y = p.getY();

    mouseMoved = true;
    Point mousePoint = Point(x, y);
    // desenha uma previa
    if (points.size() > 0) {
        Point p1 = points[0];

        if (drawLine) {
            demo = new Line(p1, mousePoint);
        } else if (drawRectangle) {
            demo = new RectangleC(p1, mousePoint);
        }
    } else {
        // move figura selecionada

        // shapeCopy é feita com base na shape selecionada onde o mouse foi clicado
        // shapeCp é usada como auxiliar para fazer o calculo de translacao
        // shapeCopy soh eh sobrescrito quando o mouse for largado
        if (shapeCopy->getId() == SHAPE) {
            Shape *cp = selectedShape->copy();
            shapeCopy = cp;
        }

        if (Line *line = dynamic_cast<Line *>(selectedShape)) {
            Line *shapeCp = dynamic_cast<Line *>(shapeCopy);

            Point p1 = shapeCp->getP1();
            Point p2 = shapeCp->getP2();

            int width = mousePointPressed.getX() - mousePoint.getX();
            int height = mousePointPressed.getY() - mousePoint.getY();

            line->setP1(Point(p1.getX() - width, p1.getY() - height));
            line->setP2(Point(p2.getX() - width, p2.getY() - height));

            if (RectangleC *rect = dynamic_cast<RectangleC *>(line)) {
                if (RectangleC *rectCopy = dynamic_cast<RectangleC *>(shapeCp)) {
                    Point p3 = rectCopy->getP3();
                    Point p4 = rectCopy->getP4();

                    rect->setP3(Point(p3.getX() - width, p3.getY() - height));
                    rect->setP4(Point(p4.getX() - width, p4.getY() - height));
                }
            }
        }
    }
}

void mouseClick(int button, int state, int mX, int mY) {
    canvas->mouseClick(button, state, mX, mY);
    Point p = canvas->getMousePoint();

    int x = p.getX();
    int y = p.getY();

    if (state == 0) {
        mousePressEvent(x, y);
    } else {
        mouseReleaseEvent(x, y);
    }
}

void mouseWheelCB(int wheel, int direction, int x, int y) {
    canvas->mouseWheelCB(wheel, direction, x, y);
}

void special(int key, int, int) {
    canvas->keyboard(key + 100);
}

void specialUp(int key, int, int) {
    canvas->keyboardUp(key + 100);
}

void MainWindow::renderComponents() {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw(canvas);
    }

    demo->draw(canvas);
    demo->drawSelectionBox(canvas);
    selectedShape->drawSelectionBox(canvas);
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
    glutPassiveMotionFunc(mouseMoveEvent);
    glutMotionFunc(mouseMoveEvent);
    glutMouseWheelFunc(mouseWheelCB);
}

void MainWindow::show() {
    canvas->setWindow(this);
    canvas->initCanvas(&width, &height, title);
    init();
    canvas->runCanvas();
}