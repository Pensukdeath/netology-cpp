// Comparisons_in_fractions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Задача 1. Сравнения в дробях
В этом задании вы переопределите операторы сравнения для дробей.

Дан код на C++:

#include <iostream>

class Fraction
{
private:
    int numerator_;
    int denominator_;

public:
    Fraction(int numerator, int denominator)
    {
        numerator_ = numerator;
        denominator_ = denominator;
    }
};

int main()
{
    Fraction f1(4, 3);
    Fraction f2(6, 11);

    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
    return 0;
}
Ваша задача — дописать класс Fraction так, чтобы программа компилировалась и работала корректно.

Пример работы программы
Консоль
f1 not == f2
f1 != f2
f1 not < f2
f1 > f2
f1 not <= f2
f1 >= f2
*/

#include <iostream>

class Fraction
{
private:
    int numerator_;
    int denominator_;

public:
    Fraction(int numerator, int denominator)
    {
        numerator_ = numerator;
        denominator_ = denominator;
    }

    bool operator==(const Fraction& other) const
    {
        return numerator_ * other.denominator_ == denominator_ * other.numerator_;
    }

    bool operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const
    {
        return numerator_ * other.denominator_ < denominator_ * other.numerator_;
    }

    bool operator>(const Fraction& other) const
    {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const
    {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const
    {
        return !(*this < other);
    }
};

int main()
{
    Fraction f1(4, 3);
    Fraction f2(6, 11);

    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';

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
