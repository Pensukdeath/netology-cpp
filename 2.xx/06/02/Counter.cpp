#include <iostream>
#include "Counter.h"

using namespace std;

Counter::Counter() {}

void Counter::add() {
    point++;
}

void Counter::subtract() {
    point--;
}

void Counter::info() {
    cout << "===================================" << endl;
    cout << "Ваш счёт: " << endl;
    cout << "===================================" << endl;
    cout << point << endl;
}

void Counter::startPoint(int point) {
    this->point = point;
}