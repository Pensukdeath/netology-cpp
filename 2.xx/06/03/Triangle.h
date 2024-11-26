#pragma once
class Triangle {
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle();
    virtual void print_info();
};