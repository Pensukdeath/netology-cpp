#include "Quadrilateral.h"
#include <iostream>

Quadrilateral::Quadrilateral() {
    a = 10;
    b = 20;
    c = 30;
    d = 40;
    A = 50;
    B = 60;
    C = 70;
    D = 80;
}

void Quadrilateral::print_info() {
    std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
    std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << std::endl;
}