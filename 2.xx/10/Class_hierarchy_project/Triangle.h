#pragma once
#include "InvalidShapeException.h"

class Triangle {
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle(double a, double b, double c, double A, double B, double C);
    virtual void print_info();
};