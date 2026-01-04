#include "Shape.h"

Shape::Shape() : color("red") {}

Shape::Shape(std::string color) {
    if (!valid_color(color))
        throw std::invalid_argument("color invalido");
    this->color = color;
}

std::string Shape::get_color() const {
    return color;
}

void Shape::set_color(std::string c) {
    if (!valid_color(c))
        throw std::invalid_argument("color invalido");
    color = c;
}

