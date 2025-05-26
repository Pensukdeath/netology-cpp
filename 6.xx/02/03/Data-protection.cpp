/*
Задание 3
Защищённый обмен данными
Создайте класс Data, содержащий в качестве полей скалярные данные и мьютекс.
Создайте функцию swap, которая принимает ссылки на два объекта класса Data и обменивает их местами.
В функциях нужно сначала захватить мьютексы обоих объектов, а затем выполнить обмен данными.
Реализуйте три варианта этой функции: при помощи lock, scoped_lock и unique_lock.
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <locale>

class Data {
public:
    int value;
    std::mutex mtx;

    Data(int v) : value(v) {}
};

void swap_lock(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx);
    std::lock_guard<std::mutex> lock1(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(b.mtx, std::adopt_lock);
    std::swap(a.value, b.value);
}

void swap_scoped_lock(Data& a, Data& b) {
    std::scoped_lock lock(a.mtx, b.mtx);
    std::swap(a.value, b.value);
}

void swap_unique_lock(Data& a, Data& b) {
    std::unique_lock<std::mutex> lock1(a.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock2(b.mtx, std::defer_lock);
    std::lock(lock1, lock2);
    std::swap(a.value, b.value);
}

int main() {
    setlocale(LC_ALL, "Russian");

    Data d1(100), d2(200);

    std::cout << "До обмена: d1 = " << d1.value << ", d2 = " << d2.value << "\n";

    swap_lock(d1, d2);
    std::cout << "После swap_lock:         d1 = " << d1.value << ", d2 = " << d2.value << "\n";

    swap_scoped_lock(d1, d2);
    std::cout << "После swap_scoped_lock:  d1 = " << d1.value << ", d2 = " << d2.value << "\n";

    swap_unique_lock(d1, d2);
    std::cout << "После swap_unique_lock:  d1 = " << d1.value << ", d2 = " << d2.value << "\n";

    return 0;
}
