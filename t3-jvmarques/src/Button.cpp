#include "Button.h"

void Button::render(Canvas *canvas) {
    canvas->color(0, 1, 0);
    canvas->rectFill(x, y, x + width, y + height);
    canvas->color(0, 0, 0);
    canvas->text(x + 5, y + height / 2, label);
}