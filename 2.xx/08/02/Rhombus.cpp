#include "Rhombus.h"
#include <iostream>

using namespace std;

Rhombus::Rhombus() : Parallelogram() {
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
    cout << "Ромб:" << endl;
    Parallelogram::print_info();
}