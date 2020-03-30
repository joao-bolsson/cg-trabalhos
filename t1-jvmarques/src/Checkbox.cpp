#include "Checkbox.h"
#include "gl_canvas2d.h"

void Checkbox::doClick() {
    // TODO
}

void Checkbox::render() {
    color(0, 1, 0);
    rect(x, y, x + width, y + height);
    color(0, 0, 0);
    text(x + width, y + height, label);
}