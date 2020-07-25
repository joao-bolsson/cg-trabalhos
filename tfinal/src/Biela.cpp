#include "Biela.h"

Biela::Biela(int radius, int length, Point center) : Object(center) {
    this->length = length;

    float step = 0.35; // 20 graus

    float height = length;

    float yBegin = center.getY();

    for (int h = 0; h <= height; h += 10) {
        vector<Point> line;
        for (float teta = 0; teta <= 2 * PI; teta += step) {
            // constroi deitado, se quiser em pe, troca x <-> y
            float x = radius * sin(teta);
            float y = yBegin + h;
            float z = radius * cos(teta);

            Point p = Point(x, y, z);

            line.push_back(p);
        }
        points.push_back(line);
    }
}

void Biela::render() {
    if (1 > 2) { // desenha 2d
        color(0, 0, 1);
        line(pVirabrequim.getX(), pVirabrequim.getY(), pPistaoTransf.getX(), pPistaoTransf.getY());
        return;
    }
    ///////////// mesmo codigo de cylinder::render
    for (unsigned int l = 0; l < transformed.size(); l++) {
        color(1, 0, 0);
        vector<Point> points = transformed[l];
        float r = 0.1, g = 0.2, b = 0.3;
        for (unsigned int c = 0; c < points.size() - 1; c++) {
            Point p1 = points[c];
            Point p2 = points[c + 1];

            line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

            if (l < transformed.size() - 1) {
                color(r, g, b);
                p2 = transformed[l + 1][c];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());

                p2 = transformed[l + 1][c + 1];
                line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
            }
            r += 0.02;
            g += 0.01;
            b += 0.02;
        }
        // connect the last with the first
        Point first = points[0];
        Point last = points[points.size() - 1];
        line(first.getX(), first.getY(), last.getX(), last.getY());

        if (l < transformed.size() - 1) {
            last = transformed[l + 1][0];
            line(first.getX(), first.getY(), last.getX(), last.getY());

            int size = transformed[l + 1].size();
            last = transformed[l + 1][size - 1];
            line(first.getX(), first.getY(), last.getX(), last.getY());
        }
    }

    //////////////////
}

void Biela::transform() {
    Object::transform();
}

void Biela::connect(Point ptConnection, float ang) {
    //// dois pontos para checar se a biela deforma ou nao
    Point pViraTest, pPistaoTest;

    // recebe o ponto de conexão com o virabrequim e transforma
    Point p = ptConnection.copy();

    // move to origin
    p.translate(-center.getX(), -center.getY(), -center.getZ());

    p.rotateZ(angZ);
    p.rotateY(angY);
    p.rotateX(angX);

    pViraTest = p.copy();
    pViraTest.translate(center.getX(), center.getY(), center.getZ());

    p.translate(0, 0, 150);

    p.project(distance);

    // return back to the original center
    p.translate(center.getX(), center.getY(), center.getZ());

    // centralizing in another point on screen
    p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pVirabrequim = p;

    // calcula o ponto de conexão com o pistao  /// esta fazendo a mesma coisa q o pViraTest
    Point pConTemp = ptConnection.copy();
    pConTemp.translate(-center.getX(), -center.getY(), -center.getZ());

    pConTemp.rotateZ(angZ);
    pConTemp.rotateY(angY);
    pConTemp.rotateX(angX);

    pConTemp.translate(center.getX(), center.getY(), center.getZ());

    float xVirabrequim = pConTemp.getX();
    float yVirabrequim = pConTemp.getY();
    float cateto = sqrt(length * length - xVirabrequim * xVirabrequim);

    float xPistao = center.getX(); // 0
    float yPistao = cateto + yVirabrequim;

    Point pTemp = Point(xPistao, yPistao, pConTemp.getZ());
    pPistao = pTemp.copy();

    pTemp.translate(0, 0, 150);

    pTemp.project(distance);

    pTemp.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pPistaoTransf = pTemp;

    // pPistaoTransf
    // TODO: não pode deformar
    float d1 = sqrt(pow(pPistao.getX() - pViraTest.getX(), 2) + pow(pPistao.getY() - pViraTest.getY(), 2) + pow(pPistao.getZ() - pViraTest.getZ(), 2));
    printf("distance: %.1f\n", d1);
}

Point Biela::getConnectionPistao() {
    return pPistao;
}