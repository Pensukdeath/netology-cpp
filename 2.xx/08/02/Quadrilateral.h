#pragma once
#include "InvalidShapeException.h"

class Quadrilateral {
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrilateral();
    Quadrilateral(double a, double b, double c, double d, double A, double B, double C, double D);
    virtual void print_info();
};