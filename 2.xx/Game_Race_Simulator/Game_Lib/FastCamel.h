#pragma once

#include "GroundTransport.h"

class DLL_EXPORT FastCamel : public GroundTransport {
public:
    std::string getName() override { return "�������-���������"; }
    double getSpeed() override { return 40.0; }
    double getTime(double distance) override;
};