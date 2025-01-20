#pragma once

#include "GroundTransport.h"

class DLL_EXPORT Centaur : public GroundTransport {
public:
    std::string getName() override { return " ентавр"; }
    double getSpeed() override { return 15.0; }
    double getTime(double distance) override;
};