/*
Задача 1. Адреса переменных
Описание
В этом задании вы потренируетесь выводить адреса и размеры переменных. Ваша
задача — создать переменные следующих типов:

int;
short;
long;
long long;
float;
double;
long double;
bool.
Для каждой переменной выведите на консоль её адрес и размер.

Пример работы программы
short: 007DF924 2
int: 007DF918 4
long: 007DF90C 4
long long: 007DF8FC 8
float: 007DF8F0 4
double: 007DF8E0 8
long double: 007DF8D0 8
bool: 007DF8C7 1
*/

#include <iostream>

using namespace std;

int main() {

  int _int = 0;
  short _short = 0;
  long _long = 0;
  long long _long_long = 0;
  float _float = 0;
  double _double = 0;
  long double _long_double = 0;
  bool _bool = 0;

  cout << "================================" << endl;
  cout << "int:         | " << &_int << " " << sizeof(_int) << endl;
  cout << "short:       | " << &_short << " " << sizeof(_short) << endl;
  cout << "long:        | " << &_long << " " << sizeof(_long) << endl;
  cout << "long long:   | " << &_long_long << " " << sizeof(_long_long) << endl;
  cout << "float:       | " << &_float << " " << sizeof(_float) << endl;
  cout << "double:      | " << &_double << " " << sizeof(_double) << endl;
  cout << "long double: | " << &_long_double << " " << sizeof(_long_double)
       << endl;
  cout << "bool:        | " << &_bool << " " << sizeof(_bool) << endl;
  cout << "================================" << endl;

  return 0;
}
