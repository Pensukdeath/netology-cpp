/*
  Задача 1. Умный массив
Описание
Вам нужно реализовать умный массив для данных типа int в духе идиомы RAII, который сам управляет своей памятью: самостоятельно выделяет её при создании и очищает, когда объект данного класса не используется.

Должны быть реализованы следующие функции:

Конструктор, принмающий количество элементов, которое будет хранить массив.
Функция добавления нового элемента в массив. Не забудьте обработать случай, когда количество элементов больше количества элементов, на которую выделена память.
Функция получения элемента по индексу. Не забудьте проверку на корректность индекса.
Деструктор.
Пример правильной работы программы
Работа с вашим классом должна происходить так:

try {
	smart_array arr(5);
	arr.add_element(1);
	arr.add_element(4);
	arr.add_element(155);
	arr.add_element(14);
	arr.add_element(15);
	std::cout << arr.get_element(1) << std::endl;
}
catch (const std::exception& ex) {
	std::cout << ex.what() << std::endl;
}
*/

#include <iostream>
#include <stdexcept>

class smart_array {
private:
    int* data;
    size_t capacity;
    size_t size;

public:
    smart_array(size_t capacity) : capacity(capacity), size(0) {
        if (capacity == 0) {
            throw std::invalid_argument("Размер должен быть больше 0.");
        }
        data = new int[capacity];
    }

    ~smart_array() {
        delete[] data;
    }

    void add_element(int value) {
        if (size >= capacity) {
            throw std::out_of_range("Массив заполнен");
        }
        data[size++] = value;
    }

    int get_element(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за пределы диапазона");
        }
        return data[index];
    }

    size_t get_size() const {
        return size;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);

        std::cout << "Элемент с индексом 1: " << arr.get_element(1) << std::endl;

        arr.add_element(99);
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}
