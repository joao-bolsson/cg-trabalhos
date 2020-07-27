#include "Biela.h"

Biela::Biela(int radius, int length, Point center) : Object(center) {
    this->length = length;

    double step = 0.35; // 20 graus

    double height = length;

    double yBegin = center.getY();

    for (int h = 0; h <= height; h += 10) {
        vector<Point> line;
        for (double teta = 0; teta <= 2 * PI; teta += step) {
            double x = radius * sin(teta);
            double y = yBegin + h;
            double z = radius * cos(teta);

            Point p = Point(x, y, z);

            line.push_back(p);
        }
        points.push_back(line);
    }
}

void Biela::render() {
    if (1 > 0) { // desenha 2d
        color(0, 0, 1);
        line(pVirabrequim.getX(), pVirabrequim.getY(), pPistaoTransf.getX(), pPistaoTransf.getY());

        color(1, 0, 0);
        circle(pVirabrequim.getX(), pVirabrequim.getY(), 3, 10);

        color(0, 1, 0);
        circle(pPistaoTransf.getX(), pPistaoTransf.getY(), 3, 10);
        return;
    }
    ///////////// mesmo codigo de cylinder::render
    for (unsigned int l = 0; l < transformed.size(); l++) {
        color(1, 0, 0);
        vector<Point> points = transformed[l];
        double r = 0.1, g = 0.2, b = 0.3;
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
    // projeta o ponto do virabrequim
    Point p = pConectionVira.copy();
    p.translate(0, 0, 150);
    p.project(distance);
    p.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pVirabrequim = p;

    // projeta o ponto do pistão
    Point pTemp = pPistao.copy();
    pTemp.translate(0, 0, 150);
    pTemp.project(distance);
    pTemp.translate(translatePoint.getX(), translatePoint.getY(), translatePoint.getZ());

    pPistaoTransf = pTemp;

    // não pode deformar
    double d1 = sqrt(pow(pPistao.getX() - pConectionVira.getX(), 2) + pow(pPistao.getY() - pConectionVira.getY(), 2) + pow(pPistao.getZ() - pConectionVira.getZ(), 2));
    printf("distance: %.1f\n", d1);

    Object::transform();
}

void Biela::connect(Point ptConnection, double ang) {
    // TODO: angZ = ang
    pConectionVira = ptConnection.copy();

    double xPistao = length * cos(ang) + pConectionVira.getX();
    double yPistao = length * sin(ang) + pConectionVira.getY();
    double zPistao = length * tan(ang) + pConectionVira.getZ();

    pPistao = Point(xPistao, yPistao, pConectionVira.getZ());
    pPistao.translate(-pConectionVira.getX(), -pConectionVira.getY(), -pConectionVira.getZ());
    pPistao.rotateY(angY);
    pPistao.rotateX(angX);
    pPistao.translate(pConectionVira);

    angZ = ang - PI / 2;
    transform();
}

int Biela::getLength() {
    return length;
}

Point Biela::getConnectionPistao() {
    return pPistao;
}

Point Biela::getConnectionPistaoTranf() {
    return pPistaoTransf;
}
