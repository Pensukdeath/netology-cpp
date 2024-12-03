#include "Rectangle.h"
#include <iostream>

using namespace std;

Rectangle::Rectangle() : Quadrilateral(10, 20, 10, 20, 90, 90, 90, 90) {}

void Rectangle::print_info() {
    cout << "Прямоугольник:" << endl;
    Quadrilateral::print_info();
}