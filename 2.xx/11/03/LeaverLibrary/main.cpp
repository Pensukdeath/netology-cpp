#include <iostream>
#include <string>
#include "Leaver.h"
#include "Windows.h"

int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
	
    std::string name;
    std::cout << "Введите имя: ";
    std::getline(std::cin, name);

    Leaver leaver;
    std::cout << leaver.leave(name) << std::endl;
	
	system ("pause");
    return 0;
}