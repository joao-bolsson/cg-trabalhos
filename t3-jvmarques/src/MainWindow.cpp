#include "MainWindow.h"

#include "Constants.h"
#include "Shape.h"
#include "Point.h"
#include "Curve.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool drawCurve = false, drawSelected = false;
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
 * @brief Method call to clear the canvas.
 */
void btnClear() {
    printf("[debug] Button to clear the screen pressed\n");
    stopDrawing();
    shapes.clear();
    clearSelection();
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
    drawCurve = false;
    rotate(true, selectedShape);
}

void btnRotateRight() {
    printf("[debug] Button to rotate right pressed\n");
    drawCurve = false;
    rotate(false, selectedShape);
}

void btnCurve() {
    if (!drawCurve) {
        printf("[debug] Button to draw a curve pressed\n");
        clearSelection();
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

        shapes.push_back(curve);
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
    if (drawCurve) {
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
    if (drawSelected) {
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