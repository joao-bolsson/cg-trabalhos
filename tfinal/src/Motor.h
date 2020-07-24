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
    Motor(Point center);

    void render();
    void transform();
    void translate(Point p);
    void rotate(float angX, float angY, float angZ);
    void setDistance(int d);

    float calcAngPistao();
};

#endif
