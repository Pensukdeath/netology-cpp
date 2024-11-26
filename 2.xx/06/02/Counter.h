#pragma once
class Counter {
private:
    int point = 0;
public:
    Counter();
    void add();
    void subtract();
    void info();
    void startPoint(int point);
};