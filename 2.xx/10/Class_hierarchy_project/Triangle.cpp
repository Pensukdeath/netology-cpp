#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(double a, double b, double c, double A, double B, double C) {
    if (a <= 0 || b <= 0 || c <= 0)
        throw InvalidShapeException("������ �������� ������. �������: ����� ������ ������ ���� ��������������");

    if (A + B + C != 180)
        throw InvalidShapeException("������ �������� ������. �������: ����� ����� �� ����� 180");

    this->a = a;
    this->b = b;
    this->c = c;
    this->A = A;
    this->B = B;
    this->C = C;
}

void Triangle::print_info() {
    cout << "�������: a=" << a << " b=" << b << " c=" << c << endl;
    cout << "����: A=" << A << " B=" << B << " C=" << C << endl;
}