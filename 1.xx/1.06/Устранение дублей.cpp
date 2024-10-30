// Задача 2. Устранение дублирования

#include <iostream>

using namespace std;

double prints(int value, int power) {
  double result = 1;
  for (int i = 0; i < power; i++) {
    result *= value;
  }
  return result;
}

int main(int argc, char **argv) {
  int value = 5;
  int power = 2;

  double result = prints(value, power);
  cout << value << " в степени " << power << " = " << result << endl;
  value = 3;
  power = 3;

  result = prints(value, power);
  cout << value << " в степени " << power << " = " << result << endl;
  value = 4;
  power = 4;

  result = prints(value, power);
  cout << value << " в степени " << power << " = " << result << endl;
  return 0;
}
