#include "IsoscelesTriangle.h"
#include <iostream>

using namespace std;

IsoscelesTriangle::IsoscelesTriangle(double a, double b, double c, double A)
    : Triangle(a, b, c, A, A, 180 - 2 * A) {

    if (a != c)
        throw InvalidShapeException("������ �������� ������. �������: ��� ��������������� ������������ ������� a � c ������ ���� �����");

    if (A + A + (180 - 2 * A) != 180)
        throw InvalidShapeException("������ �������� ������. �������: �������� ����� �����");
}

void IsoscelesTriangle::print_info() {
    cout << "�������������� �����������:" << endl;
    Triangle::print_info();
}