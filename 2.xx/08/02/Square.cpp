#include "Square.h"
#include <iostream>

using namespace std;

Square::Square() : Rectangle() {
    a = 20;
    b = 20;
    c = 20;
    d = 20;
}

void Square::print_info() {
    cout << "Квадрат:" << endl;
    Rectangle::print_info();
}