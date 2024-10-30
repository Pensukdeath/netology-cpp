/*
  Задача 2. Одинаковые, но разные функции
  Описание
  Ваша задача — создать несколько функций с одинаковой сигнатурой, то есть с
  одинаковым именем, одинаковыми параметрами и одинаковым типом возвращаемого
  значения, но с разной реализацией.

  Создайте четыре функции int calc(int x, int y), каждая из которых будет
  реализовывать одно из четырёх простых арифметических действий: сложение,
  вычитание, умножение, деление.

  В функции main напишите код, который использует каждую из четырёх функций и
  выводит результат на экран. В функции передавайте два числа, которые перед
  этим тоже выведите на экран, чтобы можно было убедиться в корректности
  операции.

  Пример работы программы
  x = 6, y = 9
  Сложение: 15
  Вычитание: -3
  Умножение: 54
  Деление: 0
*/

#include <iostream>
using namespace std;

namespace Addition {
int calc(int x, int y) { return x + y; }
} // namespace Addition
namespace Subtraction {
int calc(int x, int y) { return x - y; }
} // namespace Subtraction
namespace Multiplication {
int calc(int x, int y) { return x * y; }
} // namespace Multiplication
namespace Division {
int calc(int x, int y) { return x / y; }
} // namespace Division

int main() {
  int num_1 = 0;
  int num_2 = 0;
  cout << "==============================" << endl;
  cout << "Введите первое число: " << endl;
  cout << "==============================" << endl;
  cin >> num_1;
  cout << "\033c";
  cout << "==============================" << endl;
  cout << "Введите второе число: " << endl;
  cout << "==============================" << endl;
  cin >> num_2;
  cout << "\033c";
  cout << "==============================" << endl;
  cout << "Сложение: " << Addition::calc(num_1, num_2) << endl;
  cout << "------------------------------" << endl;
  cout << "Вычитание: " << Subtraction::calc(num_1, num_2) << endl;
  cout << "------------------------------" << endl;
  cout << "Умножение: " << Multiplication::calc(num_1, num_2) << endl;
  cout << "------------------------------" << endl;
  cout << "Деление: " << Division::calc(num_1, num_2) << endl;
  cout << "==============================" << endl;
  return 0;
}
