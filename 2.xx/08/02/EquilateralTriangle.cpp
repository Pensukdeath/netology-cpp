#include "EquilateralTriangle.h"
#include <iostream>

using namespace std;

EquilateralTriangle::EquilateralTriangle(double a)
    : Triangle(a, a, a, 60, 60, 60) {

    if (a <= 0)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: длина стороны должна быть положительной");
}

void EquilateralTriangle::print_info() {
    cout << "Равносторонний треугольник:" << endl;
    Triangle::print_info();
}