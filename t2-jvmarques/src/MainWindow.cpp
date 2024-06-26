#include "MainWindow.h"

#include "Constants.h"
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Rectangle.h"
#include "Curve.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool drawLine = false, drawRectangle = false, drawCurve = false, drawSelected = false;
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

string filePath = "./t2-jvmarques/resources/teste.jv";
fstream file;

MainWindow::MainWindow(int width, int height, char *title) {
    canvas = new Canvas();
}

void stopDrawing() {
    points.clear();
    drawSelected = false;
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
    if (!drawLine && !drawRectangle && !drawCurve) {
        printf("[info] Button to draw line pressed\n");
        drawLine = true;
        drawRectangle = false;
        clearSelection();
    } else {
        printf("[warn] There is another shape being drawn.\n");
    }
}

/**
 * @brief Method call to clear the canvas.
 */
void btnClear() {
    printf("[debug] Button to clear the screen pressed\n");
    stopDrawing();
    shapes.clear();
    clearSelection();
}

/**
 * @brief Method called to start drawing a rectangle. 
 */
void btnRectangle() {
    if (!drawLine && !drawRectangle && !drawCurve) {
        printf("[info] Button to draw rectangle pressed\n");
        drawRectangle = true;
        drawLine = false;
        drawCurve = false;
        clearSelection();
    } else {
        printf("[warn] There is another shape being drawn.\n");
    }
}

/**
 * @param d If true - rotate to the left, false - right.
 * @param shape
 */
void rotate(bool d, Shape *shape) {
    Point pivo = shape->getPivo();

    // leva para a origem
    shape->translate(-pivo.getX(), -pivo.getY());

    // rotaciona
    shape->rotate(d);

    // leva de volta
    shape->translate(pivo.getX(), pivo.getY());

    shapeCopy = shape->copy();
}

void btnRotateLeft() {
    printf("[debug] Button to rotate left pressed\n");
    drawLine = false;
    drawRectangle = false;
    drawCurve = false;
    rotate(true, selectedShape);
}

void btnRotateRight() {
    printf("[debug] Button to rotate right pressed\n");
    drawLine = false;
    drawRectangle = false;
    drawCurve = false;
    rotate(false, selectedShape);
}

void btnCurve() {
    if (!drawLine && !drawRectangle && !drawCurve) {
        printf("[debug] Button to draw a curve pressed\n");
        clearSelection();
        drawLine = false;
        drawRectangle = false;
        drawCurve = true;
    } else {
        printf("[warn] There is another shape being drawn.\n");
    }
}

void btnDelete() {
    if (selectedShape->getId() != SHAPE) {
        printf("[debug] Button to delete the selected shape was pressed\n");
        for (unsigned int i = 0; i < shapes.size(); i++) {
            if (shapes[i] == selectedShape) {
                shapes.erase(shapes.begin() + i);
                stopDrawing();
                clearSelection();
                return;
            }
        }
    }
}

void btnOpen() {
    printf("[debug] Button to open the file was pressed\n");
    btnClear();

    file.open(filePath, ios::in | ios::binary);

    if (!file) {
        printf("[error] File couldn't be opened or it's empty\n");
        return;
    }

    unsigned int size;
    file.read(reinterpret_cast<char *>(&size), sizeof(size));

    for (unsigned int i = 0; i < size; i++) {
        char id;
        file.read(reinterpret_cast<char *>(&id), sizeof(id));

        Shape *shape;
        switch (id) {
        case LINE: {
            int p[4];
            file.read(reinterpret_cast<char *>(p), 4 * sizeof(int));

            shape = new Line(Point(p[0], p[1]), Point(p[2], p[3]));
            break;
        }
        case RECTANGLE: {
            int p[8];
            file.read(reinterpret_cast<char *>(p), 8 * sizeof(int));

            RectangleC *rect = new RectangleC(Point(p[0], p[1]), Point(p[2], p[3]));
            rect->setP3(Point(p[4], p[5]));
            rect->setP4(Point(p[6], p[7]));

            shape = rect;
            break;
        }
        case CURVE: {
            // numero de pontos de controle da curva
            unsigned int sizeCtrl;
            file.read(reinterpret_cast<char *>(&sizeCtrl), sizeof(sizeCtrl));

            // a cada dois int eh um point
            int pAux[sizeCtrl * 2];

            file.read(reinterpret_cast<char *>(pAux), sizeCtrl * 2 * sizeof(int));

            Curve *curve = new Curve();

            for (unsigned int j = 0; j < (sizeCtrl * 2); j++) {
                int x = pAux[j];
                int y = pAux[++j];

                curve->addPoint(new Point(x, y));
            }

            shape = curve;
            break;
        }
        }
        shapes.push_back(shape);
    }

    file.close();
}

void btnSave() {
    printf("[debug] Button to save the file was pressed\n");
    auto size = (unsigned int)shapes.size();
    file.open(filePath, ios::out | ios::binary);

    if (!file) {
        printf("[error] File couldn't be opened\n");
        return;
    }

    // grava o número de shapes
    file.write(reinterpret_cast<char *>(&size), sizeof(size));

    for (unsigned int i = 0; i < shapes.size(); i++) {
        Shape *shape = shapes[i];

        // grava o id da shape
        char id = shape->getId();
        file.write(reinterpret_cast<char *>(&id), sizeof(id));

        switch (id) {
        case LINE: {
            Line *line = dynamic_cast<Line *>(shape);

            int p[4];

            p[0] = line->getP1().getX();
            p[1] = line->getP1().getY();
            p[2] = line->getP2().getX();
            p[3] = line->getP2().getY();

            file.write(reinterpret_cast<char *>(p), 4 * sizeof(int));
            break;
        }
        case RECTANGLE: {
            RectangleC *rect = dynamic_cast<RectangleC *>(shape);

            // escreve os 4 pontos do retangulo

            int p[8];
            p[0] = rect->getP1().getX();
            p[1] = rect->getP1().getY();

            p[2] = rect->getP2().getX();
            p[3] = rect->getP2().getY();

            p[4] = rect->getP3().getX();
            p[5] = rect->getP3().getY();

            p[6] = rect->getP4().getX();
            p[7] = rect->getP4().getY();

            file.write(reinterpret_cast<char *>(p), 8 * sizeof(int));
            break;
        }
        case CURVE: {
            Curve *curve = dynamic_cast<Curve *>(shape);

            vector<Point *> ctrlPoints = curve->getControlPts();
            // numero de pontos de controle
            unsigned int sizeCtrl = ctrlPoints.size();

            file.write(reinterpret_cast<char *>(&sizeCtrl), sizeof(sizeCtrl));

            int pAux[sizeCtrl * 2];
            int indexP = 0;
            // insere pontos de controle
            for (unsigned int j = 0; j < ctrlPoints.size(); j++) {
                Point *p = ctrlPoints[j];

                pAux[indexP] = p->getX();
                pAux[++indexP] = p->getY();
                indexP++;
            }
            file.write(reinterpret_cast<char *>(pAux), sizeCtrl * 2 * sizeof(int));
            break;
        }
        }
    }

    file.flush();
    file.close();
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

    switch (key) {
    case KEY_4_LINE:
        btnLine();
        return;

    case KEY_4_RECTANGLE:
        btnRectangle();
        return;

    case KEY_4_CURVE:
        btnCurve();
        return;

    case KEY_4_CLEAR:
        btnClear();
        return;

    case KEY_4_ROTATE_LEFT:
        btnRotateLeft();
        return;

    case KEY_4_ROTATE_RIGHT:
        btnRotateRight();
        return;

    case KEY_4_DELETE:
        btnDelete();
        return;

    case KEY_4_OPEN:
        btnOpen();
        return;

    case KEY_4_SAVE:
        btnSave();
        return;

    default:
        return;
    }
}

void keybUp(unsigned char key, int, int) {
    canvas->keyboardUp(key);
}

void mousePressEvent(int x, int y) {
    Point point = Point(x, y);
    // apenas adiciona pontos se tiver alguma coisa sendo desenhada
    if (drawLine || drawRectangle || drawCurve) {
        points.push_back(point);

        if (drawCurve && points.size() == 4) {
            Curve *curve = new Curve();

            for (unsigned int i = 0; i < points.size(); i++) {
                curve->addPoint(new Point(points[i].getX(), points[i].getY()));
            }

            shapes.push_back(curve);
            stopDrawing();
        }
    } else {
        selectedShape = new Shape();
        mousePointPressed = point;
        drawSelected = false;

        for (unsigned int i = 0; i < shapes.size(); i++) {
            if (shapes[i]->isSelected(mousePointPressed)) {
                selectedShape = shapes[i];
                drawSelected = true;
                break;
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
    drawSelected = false;
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
    } else if (drawSelected) {
        // move figura selecionada

        // shapeCopy é feita com base na shape selecionada onde o mouse foi clicado
        // shapeCp é usada como auxiliar para fazer o calculo de translacao
        // shapeCopy soh eh sobrescrito quando o mouse for largado
        if (shapeCopy->getId() == SHAPE) {
            Shape *cp = selectedShape->copy();
            shapeCopy = cp;
        }

        if (Curve *curve = dynamic_cast<Curve *>(selectedShape)) {
            Curve *shapeCp = dynamic_cast<Curve *>(shapeCopy);

            int width = mousePointPressed.getX() - mousePoint.getX();
            int height = mousePointPressed.getY() - mousePoint.getY();

            // verifica se nao ta editando um ponto de control

            if (indexPoint == -2) {
                // verifica apenas se nao tiver editando um ponto de controle
                indexPoint = curve->isSelectedPointCtrl(mousePointPressed);
            }

            if (indexPoint != -1) {
                // move ponto de controle
                if (selectedPointCopy.getX() == -1 && selectedPointCopy.getY() == -1) {
                    Point *p = curve->getControlPts()[indexPoint];

                    selectedPointCopy = Point(p->getX(), p->getY());
                }

                curve->changePoint(indexPoint, selectedPointCopy.getX() - width, selectedPointCopy.getY() - height);
            } else {
                if (Curve *curveCopy = dynamic_cast<Curve *>(shapeCp)) {
                    vector<Point *> ptsCp = curveCopy->getControlPts();
                    for (unsigned int i = 0; i < ptsCp.size(); i++) {
                        Point *p = ptsCp[i];
                        curve->changePoint(i, p->getX() - width, p->getY() - height);
                    }
                }
            }
        } else if (Line *line = dynamic_cast<Line *>(selectedShape)) {
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

    if (drawCurve) {
        // desenha os pontos de controle
        for (unsigned int i = 0; i < points.size(); i++) {
            canvas->color(1, 0, 0);
            canvas->circleFill(points[i].getX(), points[i].getY(), 5, 10);
        }
    }
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