#include "Button.h"
#include "gl_canvas2d.h"

void Button::render() {
    color(0, 1, 0);
    rectFill(x, y, x + width, y + height);
    color(0, 0, 0);
    text(x + 5, y + height / 2, label);
}