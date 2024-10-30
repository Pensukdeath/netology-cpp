/*
  Задача 3. Переворот массива
  Описание
  Напишите функцию reverse, которая принимает на вход массив произвольного
  размера и «разворачивает» его в обратную сторону — то есть первый элемент
  становится последним и наоборот. Выведите на консоль массив до вызова функции
  и после вызова функции.

  Обратите внимание, что функция reverse должна изменять передаваемый ей массив.
  Элементы в нём должны изменить свой порядок.

  Пример работы программы
  До функции reverse: 1 2 3 4 5 6 7 8 9
  После функции reverse: 9 8 7 6 5 4 3 2 1
*/

#include <iostream>
using std::cout;
using std::endl;


void swap(int *_a, int *_b) {
  int temp = *_a;
  *_a = *_b;
  *_b = temp;
}
void reverse(int * arr, int size_all) {
  int count = size_all / 2;
  for (int i = 0; i < count; i++, --size_all) {
    swap((arr + i), arr + (size_all-1));
  }
}

int main() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size_all = sizeof arr / sizeof arr[0];
  cout << "До функции reverse: ";
  for (int i = 0; i < size_all; i++) {
    cout << arr[i] << " ";
  }

  cout << endl;
  cout << "После функции reverse: ";
  reverse(arr, size_all);
  for (int i = 0; i < size_all; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  
  cout << endl;
  return 0;
}
