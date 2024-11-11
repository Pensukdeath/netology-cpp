// Calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Задача 1. Калькулятор двух чисел
В этом задании вам нужно будет создать класс, выполняющий простые арифметические операции для двух чисел, и продемонстрировать его работу

Создайте класс Calculator. Класс должен содержать два поля num1 и num2 для хранения дробных чисел. Также класс должен содержать следующие методы:

double add() - метод должен возвращать результат сложения num1 и num2
double multiply() - метод должен возвращать результат перемножения num1 и num2
double subtract_1_2() - метод должен возвращать результат вычитания num2 из num1
double subtract_2_1() - метод должен возвращать результат вычитания num1 из num2
double divide_1_2() - метод должен возвращать результат деления num1 на num2
double divide_2_1() - метод должен возвращать результат деления num2 на num1
bool set_num1(double num1) - метод должен установить значение поля num1 равное значению аргумента num1 в случае, если значение аргумента не равно 0. Возвращает true, если установка произошла успешно, в обратном случае false
bool set_num2(double num2) - метод должен установить значение поля num2 равное значению аргумента num2 в случае, если значение аргумента не равно 0. Возвращает true, если установка произошла успешно, в обратном случае false
Напишите код, демонстрирующий работу класса Calculator. Попросите пользователя ввести два числа. После этого выведите пользователю результаты всех операций или попросите его ввести значение ещё раз, если предыдущий ввод был некорректен

Программа спрашивает пользователя бесконечно, пока он сам не закроет консоль

Пример работы программы
Консоль
Введите num1: 3
Введите num2: 6
num1 + num2 = 9
num1 - num2 = -3
num2 - num1 = 3
num1 * num2 = 18
num1 / num2 = 0.5
num2 / num1 = 2
Введите num1: 5
Введите num2: 0
Неверный ввод!
Введите num2: 5
num1 + num2 = 10
num1 - num2 = 0
num2 - num1 = 0
num1 * num2 = 25
num1 / num2 = 1
num2 / num1 = 1
*/
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

class Calculator {
public:
    double num1;
    double num2;
    double add(double num1, double num2) {
        return num1 + num2;
    }
    double multiply(double num1, double num2) {
        return num1 * num2;
    }
    double subtract_1_2(double num1, double num2) {
        return num1 - num2;
    }
    double subtract_2_1(double num1, double num2) {
        return num2 - num1;
    }
    double divide_1_2(double num1, double num2) {
        return num1 / num2;
    }
    double divide_2_1(double num1, double num2) {
        return num2 / num1;
    }
    bool set_num1(double num1) {
        this->num1 = num1;
        if (num1 != 0) {
            return true;
        }
        else {
            return false;
        }
    }
    bool set_num2(double num2) {
        this->num2 = num2;
        if (num2 != 0) {
            return true;
        }
        else {
            return false;
        }
    }
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Calculator play;

    while (true) {
        play.num1 = 0;
        play.num2 = 0;

        cout << "=======================================" << endl;
        cout << "Введите первое число:" << endl;
        cout << "=======================================" << endl;
        while (!play.set_num1(play.num1)) {
            cin >> play.num1;
            if (play.set_num1(play.num1) == true) {
                break;
            }
            else {
                cout << "=======================================" << endl;
                cout << "Ошибка первого значения" << endl;
                cout << "=======================================" << endl;
            }
        }

        cout << "=======================================" << endl;
        cout << "Введите второе число:" << endl;
        cout << "=======================================" << endl;
        while (!play.set_num2(play.num2)) {
            cin >> play.num2;
            if (play.set_num2(play.num2) == true) {
                break;
            }
            else {
                cout << "=======================================" << endl;
                cout << "Ошибка второго значения" << endl;
                cout << "=======================================" << endl;
            }
        }

        cout << "num1 + num2 = " << play.add(play.num1, play.num2) << endl;
        cout << "num1 * num2 = " << play.multiply(play.num1, play.num2) << endl;

        cout << "num1 - num2 = " << play.subtract_1_2(play.num1, play.num2) << endl;
        cout << "num2 - num1 = " << play.subtract_2_1(play.num1, play.num2) << endl;

        cout << "num1 / num2 = " << play.divide_1_2(play.num1, play.num2) << endl;
        cout << "num2 / num1 = " << play.divide_2_1(play.num1, play.num2) << endl;
    }
    
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
