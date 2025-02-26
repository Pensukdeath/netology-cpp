/*
Задача 1. Возведение в квадрат
Описание
Нужно реализовать шаблонную функцию возведения в квадрат, которая работает не только с простыми числами, но и с векторами. Для этого создайте две реализации шаблонной функции.

Пример правильной работы программы
[IN]: 4
[OUT]: 16
[IN]: -1, 4, 8
[OUT]: 1, 16, 64
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T square(const T& value) {
    return value * value;
}

template <typename T>
vector<T> square(const vector<T>& vec) {
    vector<T> result;
    result.reserve(vec.size());
    for (const auto& elem : vec) {
        result.push_back(square(elem));
    }
    return result;
}

template <typename T>
void print_result(const T& value) {
    cout << value << endl;
}

template <typename T>
void print_result(const vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

int main() {
    int num;
    cout << "[IN]: ";
    cin >> num;
    cout << "[OUT]: ";
    print_result(square(num));
    
    vector<int> vec;
    cout << "[IN]: ";
    int val;
    while (cin >> val) {
        vec.push_back(val);
        if (cin.peek() == '\n') {
            break;
        }
    }
    cout << "[OUT]: ";
    print_result(square(vec));
    
    return 0;
}