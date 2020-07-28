#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "AbstractButton.h"

#define CHECKBOX_SIZE 15

class Checkbox : public AbstractButton {

protected:
    bool selected = false;

public:
    Checkbox();
    Checkbox(char *label, int x, int y, bool selected = false);
    void render();
    void doClick() override;

    void setSelected(bool selected);
};

#endif