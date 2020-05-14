#include "Checkbox.h"

void Checkbox::render(Canvas *canvas) {
    canvas->color(0, 1, 0);
    if (selected) {
        canvas->rectFill(x, y, x + width, y + height);
    } else {
        canvas->rect(x, y, x + width, y + height);
    }
    canvas->color(0, 0, 0);
    canvas->text(x + width, y + height / 2, label);
}

void Checkbox::doClick() {
    selected = !selected;
    if (action != NULL) {
        action();
    }
}

void Checkbox::setSelected(bool selected) {
    this->selected = selected;
}
