/*
Задача 3*. Аналог std::vector
Описание
Для лучшего понимания работы std::vector в этом задании вам нужно написать собственную шаблонную упрощённую реализацию std::vector.

У вашего контейнера должны работать функции:

at(int index) — доступ к элементу контейнера по индексу;
push_back(T value) — размер контейнера неизвестен заранее, вам нужно правильно увеличивать выделенную память;
size () — количество элементов в контейнере;
capacity() — количество элементов, которое может вместить контейнер до нового выделения памяти.
*/

#include <iostream>
#include <stdexcept>
#include <locale>

template <typename T>
class MyVector {
private:
    T* data;
    size_t vec_size;
    size_t vec_capacity;

    void resize() {
        vec_capacity = (vec_capacity == 0) ? 1 : vec_capacity * 2;
        T* new_data = new T[vec_capacity];
        for (size_t i = 0; i < vec_size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

public:
    MyVector() : data(nullptr), vec_size(0), vec_capacity(0) {}
    
    ~MyVector() {
        delete[] data;
    }
    
    void push_back(T value) {
        if (vec_size == vec_capacity) {
            resize();
        }
        data[vec_size++] = value;
    }
    
    T at(int index) const {
        if (index < 0 || index >= static_cast<int>(vec_size)) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }
    
    size_t size() const {
        return vec_size;
    }
    
    size_t capacity() const {
        return vec_capacity;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    
    std::cout << "Размер: " << vec.size() << "\n";
    std::cout << "Вместимость: " << vec.capacity() << "\n";
    std::cout << "Элемент с индексом 1: " << vec.at(1) << "\n";
    
    return 0;
}