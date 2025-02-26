/*
Задача 3. Счётчик чисел
Описание
В этом задании вам нужно реализовать функтор, который подсчитывает сумму и количество чисел, делящихся на 3.

Должны быть реализованы 2 функции:

get_sum()
get_count()
Пример правильной работы программы
[IN]: 4 1 3 6 25 54
[OUT]: get_sum() = 63
[OUT]: get_count() = 3
Подсказки
Не читайте этот раздел сразу. Попытайтесь сначала решить задачу самостоятельно :)

Что использовать для решения.
Можете использовать функцию std::foreach.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DivByThreeCounter {
private:
    int sum;
    int count;

public:
    DivByThreeCounter() : sum(0), count(0) {}

    void operator()(int value) {
        if (value % 3 == 0) {
            sum += value;
            count++;
        }
    }

    int get_sum() const {
        return sum;
    }

    int get_count() const {
        return count;
    }
};

int main() {
    vector<int> numbers;
    int num;
    cout << "[IN]: ";
    while (cin >> num) {
        numbers.push_back(num);
        if (cin.peek() == '\n') {
            break;
        }
    }

    DivByThreeCounter counter = for_each(numbers.begin(), numbers.end(), DivByThreeCounter());

    cout << "[OUT]: get_sum() = " << counter.get_sum() << endl;
    cout << "[OUT]: get_count() = " << counter.get_count() << endl;

    return 0;
}