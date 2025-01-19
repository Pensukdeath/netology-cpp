#pragma once

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include <string>

class DLL_EXPORT Transport {
public:
    virtual std::string getName() = 0;
    virtual double getSpeed() = 0;
    virtual double getTime(double distance) = 0;
    virtual ~Transport() = default;
};