#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "Object.h"
#include "Virabrequim.h"
#include "Biela.h"
#include "Pistao.h"

class Motor : public Object {
private:
    Virabrequim *virabrequim;
    Biela *biela;
    Pistao *pistao;

public:
    Motor(Point center, int viraLength, int pistaoLength, int pistaoRadius);

    void render();
    void transform();
    void translate(Point p);
    void rotate(double angX, double angY, double angZ);
    void setDistance(int d);

    double calcAngPistao();
};

#endif
