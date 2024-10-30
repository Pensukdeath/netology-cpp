/*
  Задача 1. Считающая функция
  Описание
  Нужно написать функцию, которая отслеживает, сколько раз она была вызвана за
  время работы программы.

  Посмотрите на этот код:

  int main(int argc, char** argv)
  {
      for (int i = 0; i < 15; i++)
      {
          counting_function();
      }
  }
  Ваша задача — написать функцию counting_function так, чтобы программа имела
  вывод на консоль, как показано ниже.

  Пример работы программы
  Количество вызовов функции counting_function(): 1
  Количество вызовов функции counting_function(): 2
  Количество вызовов функции counting_function(): 3
  Количество вызовов функции counting_function(): 4
  Количество вызовов функции counting_function(): 5
  Количество вызовов функции counting_function(): 6
  Количество вызовов функции counting_function(): 7
  Количество вызовов функции counting_function(): 8
  Количество вызовов функции counting_function(): 9
  Количество вызовов функции counting_function(): 10
  Количество вызовов функции counting_function(): 11
  Количество вызовов функции counting_function(): 12
  Количество вызовов функции counting_function(): 13
  Количество вызовов функции counting_function(): 14
  Количество вызовов функции counting_function(): 15
*/

#include <iostream>

using namespace std;

void counting_function() {
  static int check = 0;
  check += 1;
  cout << "Количество вызовов функции counting_function(): " << check << endl;
}

int main(int argc, char **argv) {
  for (int i = 0; i < 15; i++) {
    counting_function();
  }
}
