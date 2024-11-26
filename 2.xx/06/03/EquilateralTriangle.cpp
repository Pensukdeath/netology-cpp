#include "EquilateralTriangle.h"
#include <iostream>

EquilateralTriangle::EquilateralTriangle() {
    a = 30;
    b = 30;
    c = 30;
    A = 60;
    B = 60;
    C = 60;
}

void EquilateralTriangle::print_info() {
    std::cout << "Равносторонний треугольник:" << std::endl;
    Triangle::print_info();
}