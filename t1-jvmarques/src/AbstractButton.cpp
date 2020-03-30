#include "AbstractButton.h"

AbstractButton::AbstractButton() {
    // empty
}

AbstractButton::AbstractButton(char *label, int x, int y, unsigned width, unsigned height) {
    this->label = label;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void AbstractButton::doClick() {
    if (action != NULL) {
        action();
    }
}

bool AbstractButton::isPointOver(int mx, int my) {
    if (mx >= x && mx <= (x + width) && my >= y && my <= (y + height)) {
        return true;
    }
    return false;
}

void AbstractButton::setX(int x) {
    this->x = x;
}

void AbstractButton::setY(int y) {
    this->y = y;
}

void AbstractButton::setWidth(int width) {
    this->width = width;
}

void AbstractButton::setHeight(int height) {
    this->height = height;
}

void AbstractButton::setAction(function<void(void)> action) {
    this->action = action;
}

int AbstractButton::getWidth() {
    return width;
}

int AbstractButton::getHeight() {
    return height;
}

int AbstractButton::getX() {
    return x;
}

int AbstractButton::getY() {
    return y;
}

char *AbstractButton::getLabel() {
    return label;
}
