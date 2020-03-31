#include "Checkbox.h"
#include "gl_canvas2d.h"

void Checkbox::render() {
    color(0, 1, 0);
    if (selected) {
        rectFill(x, y, x + width, y + height);
    } else {
        rect(x, y, x + width, y + height);
    }
    color(0, 0, 0);
    text(x + width, y + height, label);
}

void Checkbox::doClick() {
    selected = !selected;
    if (action != NULL) {
        action();
    }
}