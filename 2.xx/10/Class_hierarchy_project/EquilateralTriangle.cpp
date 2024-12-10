#include "EquilateralTriangle.h"
#include <iostream>

using namespace std;

EquilateralTriangle::EquilateralTriangle(double a)
    : Triangle(a, a, a, 60, 60, 60) {

    if (a <= 0)
        throw InvalidShapeException("������ �������� ������. �������: ����� ������� ������ ���� �������������");
}

void EquilateralTriangle::print_info() {
    cout << "�������������� �����������:" << endl;
    Triangle::print_info();
}