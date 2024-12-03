#include "RightTriangle.h"
#include <iostream>

using namespace std;

RightTriangle::RightTriangle(double a, double b, double c)
    : Triangle(a, b, c, 90, 45, 45) {

    if (c * c != a * a + b * b)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: треугольник не является прямоугольным");
}

void RightTriangle::print_info() {
    cout << "Прямоугольный треугольник:" << endl;
    Triangle::print_info();
}