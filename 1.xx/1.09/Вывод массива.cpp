/*
  Задача 1. Вывод массива
  Описание
  Напишите функцию print, которая принимает на вход массив произвольного размера
  и выводит его на экран. В программе создайте несколько массивов разного
  размера и используйте для вызова вашей функции.

  Пример работы программы
  1 2 3 4 5 6 7 8 9
  6 5 4 8
  1 4 3 7 5
*/

#include <iostream>

using namespace std;

void print(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    cout << *(arr + i) << " ";
  }
}

int main() {
  int arr_1[5] = {6, 44, 15, 11, 81};
  int arr_2[3] = {6, 75, 8};
  int arr_3[4] = {61, 17, 48, 87};

  int size_1 = sizeof(arr_1) / sizeof(arr_1[0]);
  int size_2 = sizeof(arr_2) / sizeof(arr_2[0]);
  int size_3 = sizeof(arr_3) / sizeof(arr_3[0]);
  cout << "============================" << endl;
  print(arr_1, size_1);
  cout << endl;
  print(arr_2, size_2);
  cout << endl;
  print(arr_3, size_3);
  cout << endl;
  cout << "============================" << endl;

  return 0;
}
