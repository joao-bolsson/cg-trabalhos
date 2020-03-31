#include "Pixel.h"

Pixel::Pixel() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixel::Pixel(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

float Pixel::getRed() {
    return r;
}

float Pixel::getGreen() {
    return g;
}

float Pixel::getBlue() {
    return b;
}

void Pixel::setRed(float r) {
    this->r = r;
}

void Pixel::setGreen(float g) {
    this->g = g;
}

void Pixel::setBlue(float b) {
    this->b = b;
}