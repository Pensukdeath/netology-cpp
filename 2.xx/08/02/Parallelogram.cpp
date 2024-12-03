#include "Parallelogram.h"
#include <iostream>

using namespace std;

Parallelogram::Parallelogram() : Quadrilateral(20, 30, 20, 30, 30, 40, 30, 40) {}

void Parallelogram::print_info() {
    cout << "Параллелограмм:" << endl;
    Quadrilateral::print_info();
}