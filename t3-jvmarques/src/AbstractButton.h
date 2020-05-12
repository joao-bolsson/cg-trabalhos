#ifndef __ABSTRACT_BUTTON_H__
#define __ABSTRACT_BUTTON_H__

#include <functional>
#include "Canvas.h"

using namespace std;

class AbstractButton {
protected:
    char *label;
    int x, y;
    unsigned width, height;
    function<void(void)> action = NULL;

public:
    AbstractButton();
    AbstractButton(char *label, int x, int y, unsigned width, unsigned height);

    // method to be implemented
    virtual void doClick();
    virtual void render(Canvas *canvas) = 0;

    bool isPointOver(int mx, int my);
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

    void setAction(function<void(void)> action);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    char *getLabel();
};

#endif