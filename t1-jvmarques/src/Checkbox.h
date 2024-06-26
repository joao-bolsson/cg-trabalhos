#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "AbstractButton.h"

#define CHECKBOX_SIZE 15

class Checkbox : public AbstractButton {

protected:
    bool selected = false;

public:
    Checkbox() : AbstractButton() {}
    Checkbox(char *label, int x, int y) : AbstractButton(label, x, y, CHECKBOX_SIZE, CHECKBOX_SIZE) {}
    void render();
    void doClick() override;
};

#endif