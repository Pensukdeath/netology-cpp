/*
  Задача 2. Чтение массива из файла
  Описание
  Напишите программу, которая открывает файл in.txt, содержащий массив целых
  чисел, и выводит на консоль этот массив в обратном порядке. Первое «слово»
  входящего файла — это число элементов массива. Дальше следует сам массив.

  Пример работы программы
  Содержимое файла in.txt:

  5
  1 2 3 4 5
  Вывод на консоль

  5 4 3 2 1
  Ещё один пример работы программы
  Содержимое файла in.txt:

  7
  6 5 3 8 2 5 8
  Вывод на консоль

  8 5 2 8 3 5 6
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream use("in.txt");
  string str;
  int size = 0;
  use >> size;
  if (use.is_open()) {
    int *arr = new int[size];
    for (int i = 0; i < size; i++) {
      use >> arr[i];
    }
    for (int i = size - 1; i >= 0; i--) {
      cout << arr[i] << " ";
    }
    delete[] arr;
  } else {
    cout << "Файл не найден!";
  }
  return 0;
}
