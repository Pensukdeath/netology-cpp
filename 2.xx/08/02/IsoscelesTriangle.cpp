#include "IsoscelesTriangle.h"
#include <iostream>

using namespace std;

IsoscelesTriangle::IsoscelesTriangle(double a, double b, double c, double A)
    : Triangle(a, b, c, A, A, 180 - 2 * A) {

    if (a != c)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: для равнобедренного треугольника стороны a и c должны быть равны");

    if (A + A + (180 - 2 * A) != 180)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: неверная сумма углов");
}

void IsoscelesTriangle::print_info() {
    cout << "Равнобедренный треугольник:" << endl;
    Triangle::print_info();
}