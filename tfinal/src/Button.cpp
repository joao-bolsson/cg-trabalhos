#include "Button.h"

Button::Button() : AbstractButton() {
    // empty
}

Button::Button(char *label, int x, int y, unsigned width, unsigned height) : AbstractButton(label, x, y, width, height) {
    // empty
}

void Button::render() {
    color(0, 1, 0);
    rectFill(x, y, x + width, y + height);
    color(0, 0, 0);
    text(x + 5, y + height / 2, label);
}