#pragma once
#include "Quadrilateral.h"

class Rectangle : public Quadrilateral {
public:
    Rectangle();
    void print_info() override;
};