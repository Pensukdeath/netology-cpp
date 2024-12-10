#pragma once
#include "Triangle.h"

class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b, double c);
    void print_info() override;
};