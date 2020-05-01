#include "Shape.h"

Shape::Shape() {
    // empty
}

void Shape::draw(Canvas *canvas) {
    // do nothing
}

void Shape::drawSelectionBox(Canvas *canvas) {
    // do nothing
}

bool Shape::isSelected(Point x) {
    return false;
}

char Shape::getId() {
    return id;
}

Point Shape::getPivo() {
    return pivo;
}

void Shape::translate(int x, int y) {
    // empty
}

void Shape::rotate(bool d) {
    // empty
}

Shape *Shape::copy() {
    return new Shape();
}
