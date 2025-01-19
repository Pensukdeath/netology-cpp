#pragma once

#include "FlyingTransport.h"

class DLL_EXPORT Eagle : public FlyingTransport {
public:
    std::string getName() override { return "Орёл"; }
    double getSpeed() override { return 8.0; }
    double getTime(double distance) override;
};