#pragma once

#include "GroundTransport.h"

class DLL_EXPORT AllTerrainBoots : public GroundTransport {
public:
    std::string getName() override { return "�������-���������"; }
    double getSpeed() override { return 6.0; }
    double getTime(double distance) override;
};