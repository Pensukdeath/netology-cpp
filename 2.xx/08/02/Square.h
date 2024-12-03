#pragma once
#include "Rectangle.h"

class Square : public Rectangle {
public:
    Square();
    void print_info() override;
};