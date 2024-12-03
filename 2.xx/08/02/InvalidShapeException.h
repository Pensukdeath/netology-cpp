#pragma once
#include <exception>
#include <string>

class InvalidShapeException : public std::exception {
private:
    std::string message;

public:
    explicit InvalidShapeException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};