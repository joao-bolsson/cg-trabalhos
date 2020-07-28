#include "Checkbox.h"

Checkbox::Checkbox() : AbstractButton() {
    // empty
}
Checkbox::Checkbox(char *label, int x, int y, bool selected) : AbstractButton(label, x, y, CHECKBOX_SIZE, CHECKBOX_SIZE) {
    this->selected = selected;
}

void Checkbox::render() {
    color(0, 1, 0);
    if (selected) {
        rect(x, y, x + width, y + height);
        rectFill(x + width / 4, y + height / 4, x + 3 * width / 4, y + 3 * height / 4);
    } else {
        rect(x, y, x + width, y + height);
    }
    color(0, 0, 0);
    text(x + width, y + height / 2, label);
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
