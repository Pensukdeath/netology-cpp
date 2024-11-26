#include "Triangle.h"
#include <iostream>

Triangle::Triangle() {
    a = 10; b = 10; c = 10;
    A = 60; B = 60; C = 60;
}

void Triangle::print_info() {
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << std::endl;
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << std::endl;
}