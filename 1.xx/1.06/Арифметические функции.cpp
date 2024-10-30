/*
  Задача 1. Арифметические функции
  Описание
  Дана программа:

  int main(int argc, char** argv)
  {
    int a = 5, b = 10;

    int s = sum(a, b);
    int dif = diff(a, b);
    int mult = multiplication(a, b);
    double div = division(static_cast<double>(a), b);

    std::cout << a << " + " << b << " = " << s << std::endl;
    std::cout << a << " - " << b << " = " << dif << std::endl;
    std::cout << a << " * " << b << " = " << mult << std::endl;
    std::cout << a << " / " << b << " = " << div << std::endl;

    return 0;
  }
  В ней используются функции sum, diff, multiplication, division. Ваша задача —
  написать эти функции, чтобы результат работы программы выглядел следующим
  образом:

  5 + 10 = 15
  5 - 10 = -5
  5 * 10 = 50
  5 / 10 = 0.5
*/

#include <iostream>

using namespace std;

int sum(int a, int b) { return a + b; }
int diff(int a, int b) { return a - b; }
int multiplication(int a, int b) { return a * b; }
double division(double a, double b) { return a / b; }

int main(int argc, char **argv) {
  int a = 5, b = 10;

  int s = sum(a, b);
  int dif = diff(a, b);
  int mult = multiplication(a, b);
  double div = division(a, b);

  std::cout << a << " + " << b << " = " << s << std::endl;
  std::cout << a << " - " << b << " = " << dif << std::endl;
  std::cout << a << " * " << b << " = " << mult << std::endl;
  std::cout << a << " / " << b << " = " << div << std::endl;

  return 0;
}
