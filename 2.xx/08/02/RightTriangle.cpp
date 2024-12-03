#include "RightTriangle.h"
#include <iostream>

using namespace std;

RightTriangle::RightTriangle(double a, double b, double c)
    : Triangle(a, b, c, 90, 45, 45) {

    if (c * c != a * a + b * b)
        throw InvalidShapeException("������ �������� ������. �������: ����������� �� �������� �������������");
}

void RightTriangle::print_info() {
    cout << "������������� �����������:" << endl;
    Triangle::print_info();
}