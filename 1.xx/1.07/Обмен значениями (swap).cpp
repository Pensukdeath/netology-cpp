/*
  Задача 2. Обмен значениями
  Описание
  В этом задании вам нужно написать функцию swap, которая будет обменивать
  значения между двумя переменными. Посмотрите на эту часть программы:

  int main(int argc, char** argv)
  {
    int a = 5, b = 8;

    std::cout << "a = " << a << ", b = " << b << std::endl;

    swap(a, b);

    std::cout << "a = " << a << ", b = " << b << std::endl;

    return 0;
  }
  В этой программе используется функция swap, которую вам и предстоит создать.
  При этом вы должны написать её так, чтобы программа работала, как показано
  ниже.

  Пример работы программы
  a = 5, b = 8
  a = 8, b = 5
*/

#include <iostream>

using namespace std;

void menu() {
  cout << "===========================" << endl;
  cout << "Программа SWAP_COPY" << endl;
  cout << "---------------------------" << endl;
  cout << "Выберите метод решения:\n1 (Обычное),\n2 (Решение без доп.)" << endl;
  cout << "===========================" << endl;
}
void swap_copy(int &_temp_a, int &_temp_b) {
  int temp_a = _temp_a;
  int temp_b = _temp_b;
  _temp_a = temp_b;
  _temp_b = temp_a;
}
void swap_copy_copy(int &_temp_a, int &_temp_b) {
  _temp_a = _temp_a + _temp_b;
  _temp_b = _temp_a - _temp_b;
  _temp_a = _temp_a - _temp_b;
}

int main(int argc, char **argv) {
  int a = 5, b = 8;
  menu();

  int num = 0;
  cin >> num;

  switch (num) {
  case 1:
    std::cout << "a = " << a << ", b = " << b << std::endl;
    swap_copy(a, b);
    break;
  case 2:
    std::cout << "a = " << a << ", b = " << b << std::endl;
    swap_copy_copy(a, b);
    break;
  default:
    cout << "Неверный выбор!" << endl;
    return 0;
  }

  std::cout << "a = " << a << ", b = " << b << std::endl;
  cout << "===========================" << endl;

  return 0;
}
