#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle() {
    a = 10;
    b = 20;
    c = a;
    d = b;
    A = 90;
    B = 90;
    C = 90;
    D = 90;
}

void Rectangle::print_info() {
    std::cout << "Прямоугольник:" << std::endl;
    Quadrilateral::print_info();
}