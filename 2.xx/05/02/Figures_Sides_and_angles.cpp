// Figures_Sides_and_angles.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Задача 2. Фигуры. Стороны и углы
В этом задании вы усложните иерархию классов для усложнённой предметной области.

У вас появляется информация о длине сторон и углах ваших фигур, а также несколько более конкретных фигур. Теперь в треугольнике вы должны хранить информацию о длине всех его трёх сторон (a, b, c) и значениях его трёх углов (A, B, C). В четырёхугольнике вы храните информацию о длине его четырёх сторон (a, b, c, d) и значениях его четырёх углов (A, B, C, D).

Также у вас появляются более конкретные фигуры:

прямоугольный треугольник (угол C всегда равен 90);
равнобедренный треугольник (стороны a и c равны, углы A и C равны);
равносторонний треугольник (все стороны равны, все углы равны 60);
прямоугольник (стороны a,c и b,d попарно равны, все углы равны 90);
квадрат (все стороны равны, все углы равны 90);
параллелограмм (стороны a,c и b,d попарно равны, углы A,C и B,D попарно равны);
ромб (все стороны равны, углы A,C и B,D попарно равны).
Вы должны иметь возможность узнать у каждой фигуры длины её сторон и значения её углов, но извне вы не должны быть способны изменить длины сторон и углы.

Не должно быть возможности создать фигуры, не удовлетворяющие перечисленным условиям. Например, нельзя создать квадрат с разными углами. Геометрические соотношения проверять не нужно. Например, сумма углов в треугольнике может быть не равна 180.

Задача: спроектировать и реализовать классы, описывающие предметную область. Продемонстрируйте их работу: создайте по одному экземпляру каждой фигуры и выведите на экран информацию о длинах её сторон и величине её углов. Значения используйте произвольные.

Инициализацию длин сторон и величин углов нужно выполнить с помощью вызова базовых конструкторов.

Для вывода информации о фигуре создайте функцию print_info, которая будет принимать в качестве аргумента указатель на базовый класс фигуры.

Пример работы программы
Консоль
Треугольник:
Стороны: a=10 b=20 c=30
Углы: A=50 B=60 C=70

Прямоугольный треугольник:
Стороны: a=10 b=20 c=30
Углы: A=50 B=60 C=90

Равнобедренный треугольник:
Стороны: a=10 b=20 c=10
Углы: A=50 B=60 C=50

Равносторонний треугольник:
Стороны: a=30 b=30 c=30
Углы: A=60 B=60 C=60

Четырёхугольник:
Стороны: a=10 b=20 c=30 d=40
Углы: A=50 B=60 C=70 D=80

Прямоугольник:
Стороны: a=10 b=20 c=10 d=20
Углы: A=90 B=90 C=90 D=90

Квадрат:
Стороны: a=20 b=20 c=20 d=20
Углы: A=90 B=90 C=90 D=90

Параллелограмм:
Стороны: a=20 b=30 c=20 d=30
Углы: A=30 B=40 C=30 D=40

Ромб:
Стороны: a=30 b=30 c=30 d=30
Углы: A=30 B=40 C=30 D=40
*/

#include <iostream>

using namespace std;

class Triangle {
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle() {
        a = 10; b = 10; c = 10;
        A = 60; B = 60; C = 60;
    }

    virtual void print_info() {
        cout << "Стороны: a=" << a << " b=" << b << " c=" << c << endl;
        cout << "Углы: A=" << A << " B=" << B << " C=" << C << endl;
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle() {
        a = 10;
        b = 20;
        c = 30;
        A = 50;
        B = 60;
        C = 90;
    }

    void print_info() override {
        cout << "Прямоугольный треугольник:" << endl;
        Triangle::print_info();
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle() {
        a = 10;
        b = 20;
        c = 10;
        A = 50;
        B = 50;
        C = 80;
    }

    void print_info() override {
        cout << "Равнобедренный треугольник:" << endl;
        Triangle::print_info();
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle() {
        a = 30;
        b = 30;
        c = 30;
        A = 60;
        B = 60;
        C = 60;
    }

    void print_info() override {
        cout << "Равносторонний треугольник:" << endl;
        Triangle::print_info();
    }
};

class Quadrilateral {
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrilateral() {
        a = 10;
        b = 20;
        c = 30;
        d = 40;
        A = 50;
        B = 60;
        C = 70;
        D = 80;
    }

    virtual void print_info() {
        cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
        cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << endl;
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle() {
        a = 10;
        b = 20;
        c = a;
        d = b;
        A = 90;
        B = 90;
        C = 90;
        D = 90;
    }

    void print_info() override {
        cout << "Прямоугольник:" << endl;
        Quadrilateral::print_info();
    }
};

class Square : public Rectangle {
public:
    Square() {
        a = 20;
        b = 20;
        c = 20;
        d = 20;
        A = 90;
        B = 90;
        C = 90;
        D = 90;
    }

    void print_info() override {
        cout << "Квадрат:" << endl;
        Rectangle::print_info();
    }
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram() {
        a = 20;
        b = 30;
        c = a;
        d = b;
        A = 30;
        B = 40;
        C = A;
        D = B;
    }

    void print_info() override {
        cout << "Параллелограмм:" << endl;
        Quadrilateral::print_info();
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus() {
        a = 30;
        b = 30;
        c = 30;
        d = 30;
        A = 30;
        B = 40;
        C = 30;
        D = 40;
    }

    void print_info() override {
        cout << "Ромб:" << endl;
        Parallelogram::print_info();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    RightTriangle rt;
    rt.print_info();

    IsoscelesTriangle it;
    it.print_info();

    EquilateralTriangle et;
    et.print_info();

    Quadrilateral q1;
    q1.print_info();

    Rectangle rect;
    rect.print_info();

    Square sq;
    sq.print_info();

    Parallelogram pg;
    pg.print_info();

    Rhombus rh;
    rh.print_info();

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
