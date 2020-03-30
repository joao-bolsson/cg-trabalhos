#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "AbstractButton.h"

class Button : public AbstractButton {
public:
    Button() : AbstractButton() {
        // empty
    }
    Button(char *label, int x, int y, unsigned width, unsigned height) : AbstractButton(label, x, y, width, height) {
        this->label = label;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    void doClick();
    void render();
};

#endif