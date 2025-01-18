#pragma once

#include "GroundTransport.h"

class DLL_EXPORT Camel : public GroundTransport {
public:
    std::string getName() override { return "Верблюд"; }
    double getSpeed() override { return 10.0; }
    double getTime(double distance) override;
};