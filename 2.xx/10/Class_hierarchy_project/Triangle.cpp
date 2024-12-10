#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(double a, double b, double c, double A, double B, double C) {
    if (a <= 0 || b <= 0 || c <= 0)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: длины сторон должны быть положительными");

    if (A + B + C != 180)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: сумма углов не равна 180");

    this->a = a;
    this->b = b;
    this->c = c;
    this->A = A;
    this->B = B;
    this->C = C;
}

void Triangle::print_info() {
    cout << "Стороны: a=" << a << " b=" << b << " c=" << c << endl;
    cout << "Углы: A=" << A << " B=" << B << " C=" << C << endl;
}