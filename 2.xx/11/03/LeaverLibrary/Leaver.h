#pragma once
#include <string>

#ifdef LEAVERLIBRARY_EXPORTS
    #define LEAVERLIBRARY_API __declspec(dllexport)
#else
    #define LEAVERLIBRARY_API __declspec(dllimport)
#endif

class LEAVERLIBRARY_API Leaver {
public:
    std::string leave(const std::string& name);
};