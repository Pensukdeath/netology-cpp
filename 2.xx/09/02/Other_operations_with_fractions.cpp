// Other_operations_with_fractions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Задача 2. Остальные операции с дробями
В этом задании вы переопределите остальные операторы для класса дроби.

Необходимо переопределить операторы для класса Fraction из предыдущего задания:

сложение;
вычитание;
умножение;
деление;
унарный минус;
инкремент постфиксный и префиксный;
декремент постфиксный и префиксный.
Продемонстрируйте работу ваших операторов. Попросите пользователя ввести две дроби и покажите результат каждой операции. Операции декремента и инкремента отнимают и прибавляют к дроби 1 соответственно.

Составьте выражения, содержащие постфиксный и префиксный инкремент и декремент, чтобы продемонстрировать разницу между постфиксной и префиксной версиями.

Пример работы программы
Консоль
Введите числитель дроби 1: 3
Введите знаменатель дроби 1: 4
Введите числитель дроби 2: 4
Введите знаменатель дроби 2: 5
3/4 + 4/5 = 31/20
3/4 - 4/5 = -1/20
3/4 * 4/5 = 3/5
3/4 / 4/5 = 15/16
++3/4 * 4/5 = 7/5
Значение дроби 1 = 7/4
7/4-- * 4/5 = 7/5
Значени дроби 1 = 3/4
*/

#include <iostream>
#include <Windows.h>

using namespace std;

int nod(int numerator_, int denominator_);

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

    Fraction operator+(const Fraction& other) const
    {
        return Fraction((numerator_ * other.denominator_) + (other.numerator_ * denominator_), (denominator_ * other.denominator_));
    }

    Fraction operator-(const Fraction& other) const
    {
        return Fraction((numerator_ * other.denominator_) - (other.numerator_ * denominator_), (denominator_ * other.denominator_));
    }

    Fraction operator*(const Fraction& other) const
    {
        int numerator_mult = numerator_ * other.numerator_;
        int denominator_mult = denominator_ * other.denominator_;
        int p = nod(numerator_mult, denominator_mult);
        return Fraction(numerator_mult / p, denominator_mult / p);
    }

    Fraction operator/(const Fraction& other) const
    {
        return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
    }

    Fraction& operator++()
    {
        numerator_ += denominator_;
        return *this;
    }

    Fraction& operator--()
    {
        numerator_ -= denominator_;
        return *this;
    }

    Fraction operator++(int)
    {
        Fraction temp = *this;
        numerator_ += denominator_;
        return temp;
    }

    Fraction operator--(int)
    {
        Fraction temp = *this;
        numerator_ -= denominator_;
        return temp;
    }

    friend ostream& operator<<(ostream& os, const Fraction& f)
    {
        os << f.numerator_ << '/' << f.denominator_;
        return os;
    }
};
//================================================
// Данный код своровал на просторах рунета.
//================================================
int nod(int numerator_, int denominator_)
{
    int num = numerator_, denom = denominator_, rem;
    if (num < denom)
    {
        int temp = num;
        num = denom;
        denom = temp;
    }
    while (rem = num % denom)
    {
        num = denom;
        denom = rem;
    }
    return denom;
}
//================================================
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int a1 = 0, a2 = 0, b1 = 0, b2 = 0;

    cout << "Введите числитель дроби 1: ";
    cin >> a1;
    cout << "Введите знаменатель дроби 1: ";
    cin >> a2;
    cout << "Введите числитель дроби 2: ";
    cin >> b1;
    cout << "Введите знаменатель дроби 2: ";
    cin >> b2;

    Fraction f1(a1, a2);
    Fraction f2(b1, b2);

    cout << f1 << " + " << f2 << " = " << (f1 + f2) << '\n';
    cout << f1 << " - " << f2 << " = " << (f1 - f2) << '\n';
    cout << f1 << " * " << f2 << " = " << (f1 * f2) << '\n';
    cout << f1 << " / " << f2 << " = " << (f1 / f2) << '\n';

    cout << "++" << f1 << " * " << f2 << " = " << (++f1 * f2) << '\n';
    cout << "Значение дроби 1 = " << f1 << '\n';

    cout << f1 << "-- * " << f2 << " = " << (f1-- * f2) << '\n';
    cout << "Значение дроби 1 = " << f1 << '\n';

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
