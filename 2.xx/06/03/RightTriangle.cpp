#include "RightTriangle.h"
#include <iostream>

RightTriangle::RightTriangle() {
    a = 10;
    b = 20;
    c = 30;
    A = 50;
    B = 60;
    C = 90;
}

void RightTriangle::print_info() {
    std::cout << "Прямоугольный треугольник:" << std::endl;
    Triangle::print_info();
}