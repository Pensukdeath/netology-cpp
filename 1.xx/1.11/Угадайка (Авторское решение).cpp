/*
  Задача 2. Угадайка (Авторское решение)
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");

  string ask_1 = "Неправильно\n";
  string ask_2 = "Правильно!";
  int point = 0;
  cout << "=======================" << endl;
  cout << "Программа загадки!\t" << endl;
  cout << "-----------------------" << endl;
  cout << "Правила: Все ответы\nписать с маленькой буквы\t" << endl;
  cout << "=======================" << endl;
  cout << "Загадка №1:" << endl;
  cout << "=======================" << endl;
  cout << "Если сядешь на него,\n"
          "Быстро ты вспотеешь,\n"
          "Но с усердием своим\n"
          "Далеко доедешь."
       << endl;
  cout << "=======================" << endl;
  cout << "Введите ответ: ";
  string riddle_1 = "велосипед";
  string answer_1;
  getline(cin, answer_1);
  if (answer_1 == riddle_1) {
    cout << ask_2 << endl;
    point += 1;
  } else {
    cout << ask_1 << endl;
  }
  cout << "=======================" << endl;
  cout << "Загадка №2:" << endl;
  cout << "=======================" << endl;
  cout << "Он стоит и всем мешает,\n"
          "А особенно с утра.\n"
          "Это каждый взрослый знает —\n"
          "От него не жди добра."
       << endl;
  cout << "=======================" << endl;
  cout << "Введите ответ: ";
  string riddle_2 = "будильник";
  string answer_2;
  getline(cin, answer_2);
  if (answer_2 == riddle_2) {
    cout << ask_2 << endl;
    point += 1;
  } else {
    cout << ask_1 << endl;
  }
  string ask;
  if (point == 1) {
    ask = " вопрос!";
  } else if (point == 2) {
    ask = " вопроса!";
  } else {
    ask = " вопросов!";
  }
  cout << "===================================" << endl;
  cout << "Вы угадали правильно на " << point << ask << endl;
  cout << "===================================" << endl;
  return 0;
}
