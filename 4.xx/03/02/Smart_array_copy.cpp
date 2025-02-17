/*
  Задача 2. Копирование умных массивов
Описание
В этом задании вам нужно поработать с классом умных массивов, который вы реализовали в предыдущем задании. Сначала попробуйте создать два экземпляра вашего класса с различными элементами и присвоить один другому.

smart_array arr(5);
arr.add_element(1);
arr.add_element(4);
arr.add_element(155);

smart_array new_array(2);
new_array.add_element(44); 
new_array.add_element(34);

arr = new_array
Попытайтесь самостоятельно разобраться, что произошло, и правильно реализовать копирование умных массивов.

Подсказки
Не читайте этот раздел сразу. Попытайтесь сначала решить задачу самостоятельно :)

Что использовать для решения.
В программе возникает исключение, потому что компилятор самостоятельно сгенерировал оператор присваивания, который просто копирует все поля одного объекта другому. В частности, проблема возникает из-за копирования указателя: оба объекта класса имеют одинаковый указатель на область памяти и в своих деструкторах пытаются освободить его. Происходит двойное освобождение памяти.
  */

#include <iostream>

class smart_array {
private:
    int* data;
    int capacity;
    int size;

public:
    smart_array(int cap) : capacity(cap), size(0) {
        data = new int[capacity];
    }

    ~smart_array() {
        delete[] data;
    }

    smart_array(const smart_array& other) : capacity(other.capacity), size(other.size) {
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    smart_array& operator=(const smart_array& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        capacity = other.capacity;
        size = other.size;
        data = new int[capacity];

        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    void add_element(int value) {
        if (size < capacity) {
            data[size++] = value;
        } else {
            std::cerr << "Массив заполнен!" << std::endl;
        }
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    std::cout << "Исходные массивы:" << std::endl;
    arr.print();
    new_array.print();

    arr = new_array;

    std::cout << "После присваивания:" << std::endl;
    arr.print();
    new_array.print();

    return 0;
}