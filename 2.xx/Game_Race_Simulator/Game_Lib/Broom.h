#pragma once

#include "FlyingTransport.h"

class DLL_EXPORT Broom : public FlyingTransport {
public:
    std::string getName() override { return "Метла"; }
    double getSpeed() override { return 20.0; }
    double getTime(double distance) override;
};