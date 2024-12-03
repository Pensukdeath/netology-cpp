#include "Quadrilateral.h"
#include <iostream>

using namespace std;

Quadrilateral::Quadrilateral() {
    a = 10;
    b = 20;
    c = 30;
    d = 40;
    A = 50;
    B = 60;
    C = 70;
    D = 80;
}

Quadrilateral::Quadrilateral(double a, double b, double c, double d, double A, double B, double C, double D) {
    if (a <= 0 || b <= 0 || c <= 0 || d <= 0)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: длины сторон должны быть положительными");

    if (A + B + C + D != 360)
        throw InvalidShapeException("Ошибка создания фигуры. Причина: сумма углов не равна 360");

    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
}

void Quadrilateral::print_info() {
    cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
    cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << endl;
}