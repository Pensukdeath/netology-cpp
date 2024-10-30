/*
  Задача 1. Приветствие
  Описание
  Напишите программу, которая спрашивает у пользователя отдельно его имя и
  фамилию, а затем приветствует его. Работу необходимо выполнить, используя
  операции над строками.

  Пример работы программы
  Введите имя: Егор
  Введите фамилию: Летов
  Здравствуйте, Егор Летов!
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");
  cout << "Введите ваше имя: ";
  string name;
  getline(cin, name);
  cout << "Введите вашу фамилию: ";
  string family;
  getline(cin, family);
  cout << "Введите ваше отчество: ";
  string patronymic;
  getline(cin, patronymic);
  cout << "Здравствуйте, " << name << " " << family << " " << patronymic << "!"
       << endl;
  return 0;
}
