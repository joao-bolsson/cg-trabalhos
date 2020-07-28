#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "AbstractButton.h"

class Button : public AbstractButton {
public:
    Button();
    Button(char *label, int x, int y, unsigned width, unsigned height);
    void render();
};

#endif