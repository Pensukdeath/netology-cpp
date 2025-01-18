#pragma once

#include "GameLib.h"

class DLL_EXPORT GroundTransport : public Transport {
public:
    virtual std::string getName() = 0;
    virtual double getSpeed() = 0;
    virtual double getTime(double distance) = 0;
    virtual ~GroundTransport() = default;
};