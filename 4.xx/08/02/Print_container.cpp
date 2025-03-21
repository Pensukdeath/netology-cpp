/*
Задача 2. Печать контейнера
Описание
Нужно реализовать шаблонную функцию, которая печатает содержимое контейнера.

Контейнер может быть любым:

std::set
std::vector
std::list
Пример правильной работы программы
std::set<std::string> test_set = { "one", "two", "three", "four" };
print_container(...); // four one three two. помните почему такой порядок? :)

std::list<std::string> test_list = { "one", "two", "three", "four" };
print_container(...); // one, two, three, four

std::vector<std::string> test_vector = { "one", "two", "three", "four" };
print_container(...); // one, two, three, four
*/

#include <iostream>
#include <set>
#include <vector>
#include <list>

template <typename Container>
void print_container(const Container& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (it != container.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
}

int main() {
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set);

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list);

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector);
    
    return 0;
}