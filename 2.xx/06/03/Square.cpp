#include "Square.h"
#include <iostream>

Square::Square() {
    a = 20;
    b = 20;
    c = 20;
    d = 20;
    A = 90;
    B = 90;
    C = 90;
    D = 90;
}

void Square::print_info() {
    std::cout << "�������:" << std::endl;
    Rectangle::print_info();
}