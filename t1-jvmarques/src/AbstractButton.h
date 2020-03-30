#ifndef __ABSTRACT_BUTTON_H__
#define __ABSTRACT_BUTTON_H__

class AbstractButton {
protected:
    char *label;
    int x, y;
    unsigned width, height;

public:
    AbstractButton();
    AbstractButton(char *label, int x, int y, unsigned width, unsigned height);

    // method to be implemented
    virtual void doClick() = 0;
    virtual void render() = 0;

    bool isPointOver(int mx, int my);
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    char *getLabel();
};

#endif