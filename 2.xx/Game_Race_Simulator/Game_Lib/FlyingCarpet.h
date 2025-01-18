#pragma once

#include "FlyingTransport.h"

class DLL_EXPORT FlyingCarpet : public FlyingTransport {
public:
    std::string getName() override { return "����-������"; }
    double getSpeed() override { return 10.0; }
    double getTime(double distance) override;
};