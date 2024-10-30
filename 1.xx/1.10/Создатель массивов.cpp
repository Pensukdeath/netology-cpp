/*
  Задача 2. Создатель массивов
  Описание
  Напишите функцию create_array, которая принимает на вход размер массива,
  создаёт внутри себя динамический массив для значений типа double,
  инициализирует его нулями и возвращает вызывающей функции. Используйте эту
  функцию для создания массива. Запросите у пользователя размер массива и
  выведите на консоль получившийся массив. В конце на забудьте очистить память.

  Пример работы программы
  Введите размер массива: 10
  Массив: 0 0 0 0 0 0 0 0 0 0
*/

#include <iostream>

using namespace std;

double *create_array(int num_mass) {
  double *mass = new double[num_mass]{};
  return mass;
}
void print_mass();

int main() {

  cout << "Введите размер массива: ";
  int num_mass;
  cin >> num_mass;

  double *result = create_array(num_mass);
  cout << "Массив: ";
  for (int i = 0; i < num_mass; i++) {
    cout << *(result + i) << " ";
  }

  delete[] result;
  return 0;
}
