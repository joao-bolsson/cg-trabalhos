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

    bool showVira = true;
    bool showBiela = true;
    bool showPistao = true;
    bool showCamisa = true;

public:
    Motor(Point center, int viraLength, int pistaoLength, int pistaoRadius);

    void render();
    void transform();
    void translate(Point p);
    void rotate(double angX, double angY, double angZ);
    void setDistance(int d);
    void setShow2d(bool flag);

    double calcAngPistao();

    void setShowVira(bool flag);
    void setShowBiela(bool flag);
    void setShowPistao(bool flag);
    void setShowCamisa(bool flag);
};

#endif
