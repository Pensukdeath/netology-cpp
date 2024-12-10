#pragma once
#include "Triangle.h"

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double a);
    void print_info() override;
};