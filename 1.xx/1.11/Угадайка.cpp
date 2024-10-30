/*
  Задача 2. Угадайка
  Описание
  Напишите программу, которая просит пользователя угадать слово, записанное в
  коде — то есть вводить слова до тех пор, пока одно из них не совпадёт с
  загаданным словом.

  Пример работы программы
  Угадайте слово: арбуз
  Неправильно
  Угадайте слово: клубника
  Неправильно
  Угадайте слово: малина
  Правильно! Вы победили! Загаданное слово — малина
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");

  string ask_1 = "Неправильно\n";
  string ask_2 = "Правильно! Вы победили! Загаданное слово — ";
  cout << "Угадайте слово: " << endl;
  string answer_1 = "малина";
  string answer_2 = "арбуз";
  string answer_3 = "клубника";

  for (int i = 0; i <= 1;) {
    string answer;
    getline(cin, answer);
    if (answer == answer_1 || answer == answer_2 || answer == answer_3) {
      cout << ask_2 << answer;
      i++;
    } else {
      cout << ask_1;
    }
  }
}
