/*
  Задание 1. Таблица истинности
  Напишите программу, которая выводит таблицу истинности для логических
  операторов ||, &&, с применением логических выражений.

  Результат работы программы
  Оператор: ||
  true    true    true
  false   true    true
  true    false   true
  false   false   false

  Оператор: &&
  true    true    true
  false   true    false
  true    false   false
  false   false   false
*/
#include <iostream>

using namespace std;

int main() {
  bool a, b, c;
  string _a, _b, _c;
  a = true;
  b = true;
  c = a || b;
  cout << "===========================================" << endl;
  cout << "Программа выводит значения a || b" << endl;
  cout << "===========================================" << endl;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;

  a = false;
  b = true;
  c = a || b;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;

  a = true;
  b = false;
  c = a || b;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;

  a = false;
  b = false;
  c = a || b;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;
  cout << "===========================================" << endl;

  cout << "\n" << endl;

  a = true;
  b = true;
  c = a && b;
  cout << "===========================================" << endl;
  cout << "Программа выводит значения a && b" << endl;
  cout << "===========================================" << endl;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;

  a = false;
  b = true;
  c = a && b;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;

  a = true;
  b = false;
  c = a && b;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;

  a = false;
  b = false;
  c = a && b;
  _a = a ? "| true |" : "| false|";
  _b = b ? "| true |" : "| false|";
  _c = c ? "| true |" : "| false|";
  cout << _a << _b << _c << endl;
  cout << "===========================================" << endl;

  return 0;
}
