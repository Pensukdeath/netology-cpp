#include "Parallelogram.h"
#include <iostream>

Parallelogram::Parallelogram() {
    a = 20;
    b = 30;
    c = a;
    d = b;
    A = 30;
    B = 40;
    C = A;
    D = B;
}

void Parallelogram::print_info() {
    std::cout << "��������������:" << std::endl;
    Quadrilateral::print_info();
}