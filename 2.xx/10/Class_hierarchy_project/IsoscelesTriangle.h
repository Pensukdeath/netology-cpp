#pragma once
#include "Triangle.h"

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double b, double c, double A);
    void print_info() override;
};