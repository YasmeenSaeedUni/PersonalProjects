#include "RGB.h"

//constructors
//default constructor
RGB::RGB() : red(0), green(0), blue(0) {}

RGB::RGB(int r, int g, int b) : red(r), green(g), blue(b) {}

RGB::RGB(CuColour colour){
    setColour(colour);
}
//getters
int RGB::getR() const {
    return red;
}

int RGB::getG() const {
    return green;
}

int RGB::getB() const {
    return blue;
}

CuColour RGB::getColour() const {
    return (red << 16) + (green << 8) + blue;
}

//setters
void RGB::setR(int r) {
    red = r;
}

void RGB::setG(int g) {
    green = g;
}

void RGB::setB(int b) {
    blue = b;
}

void RGB::setColour(CuColour col) {
    red = (col >> 16) & 0xFF;
    green = (col >> 8) & 0xFF;
    blue = col & 0xFF;
}

//print the RGB values
void RGB::print() const {
    std::cout << "RGB(" << red << ", " << green << ", " << blue << ")\n";
}

//static colors
RGB RGB::WHITE() {
    return RGB(255, 255, 255);
}

RGB RGB::BLACK() {
    return RGB(0, 0, 0);
}

RGB RGB::RED() {
    return RGB(255, 0, 0);
}

RGB RGB::GREEN() {
    return RGB(0, 255, 0);
}

RGB RGB::BLUE() {
    return RGB(0, 0, 255);
}
