#pragma once
class Quadrilateral {
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrilateral();
    virtual void print_info();
};