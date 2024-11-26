#include "Rhombus.h"
#include <iostream>

Rhombus::Rhombus() {
    a = 30;
    b = 30;
    c = 30;
    d = 30;
    A = 30;
    B = 40;
    C = 30;
    D = 40;
}

void Rhombus::print_info() {
    std::cout << "Ромб:" << std::endl;
    Parallelogram::print_info();
}