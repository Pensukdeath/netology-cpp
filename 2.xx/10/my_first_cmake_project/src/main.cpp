/*
Задача 1. Простейший проект
В этом задании вам нужно создать простейший проект с помощью CMake.

Создайте проект CMake my_first_cmake_project, в котором будет исполняемая программа my_first_cmake_program. Программа должна спрашивать имя пользователя и приветствовать его.

Пример работы программы
Консоль
Введите имя: Виталий
Здравствуйте, Виталий!
*/

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string name;

    cout << "Введите имя: ";
    getline(std::cin, name);

    std::cout << "Здравствуйте, " << name << "!" << std::endl;

    return 0;
}