#include "IsoscelesTriangle.h"
#include <iostream>

IsoscelesTriangle::IsoscelesTriangle() {
    a = 10;
    b = 20;
    c = 10;
    A = 50;
    B = 50;
    C = 80;
}

void IsoscelesTriangle::print_info() {
    std::cout << "Равнобедренный треугольник:" << std::endl;
    Triangle::print_info();
}