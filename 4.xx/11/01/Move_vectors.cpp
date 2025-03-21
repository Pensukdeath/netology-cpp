/*
Задача 1. Перемещение объектов
Описание
Вам нужно реализовать шаблонную функцию, которая перемещает содержимое одного std::vector в другой.

std::vector <std::string> one = { "test_string1", "test_string2" };
std::vector <std::string> two;
move_vectors(...)
*/

#include <iostream>
#include <vector>
#include <utility>

template <typename T>
void move_vectors(std::vector<T>& source, std::vector<T>& destination) {
    destination = std::move(source);
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    
    std::vector<std::string> one = { "test_string1", "test_string2" };
    std::vector<std::string> two;
    
    move_vectors(one, two);
    
    std::cout << "Содержимое 'two':" << std::endl;
    for (const auto& str : two) {
        std::cout << str << std::endl;
    }
    
    std::cout << "Содержимое 'one':" << std::endl;
    std::cout << "Размер: " << one.size() << std::endl;
    
    return 0;
}