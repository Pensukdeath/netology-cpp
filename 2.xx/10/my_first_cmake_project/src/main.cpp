/*
������ 1. ���������� ������
� ���� ������� ��� ����� ������� ���������� ������ � ������� CMake.

�������� ������ CMake my_first_cmake_project, � ������� ����� ����������� ��������� my_first_cmake_program. ��������� ������ ���������� ��� ������������ � �������������� ���.

������ ������ ���������
�������
������� ���: �������
������������, �������!
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

    cout << "������� ���: ";
    getline(std::cin, name);

    std::cout << "������������, " << name << "!" << std::endl;

    return 0;
}