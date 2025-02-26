/*
Задача 2. Таблица
Описание
Нужно написать шаблонный класс для двумерного массива (таблицы). Все ячейки таблицы имеют один и тот же тип данных T.

Требования к классу:

Должен быть конструктор, получающий на входе два целых числа — количество строк и столбцов соответственно.
Должны быть константная и неконстантная версии оператора [], возвращающего массив, к которому снова можно применить оператор [].
Нужно, чтобы работали конструкции вида:
* cout << table[i][j]; * table[i][j] = value;.

Должна быть константная функция Size, возвращающая размер таблицы.
Пример правильной работы программы
auto test = table<int>(2, 3);
test[0][0] = 4;
std::cout << test[0][0]; // выводит 4
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Table {
private:
    vector<vector<T>> data;
    size_t rows, cols;

public:
    Table(size_t r, size_t c) : rows(r), cols(c), data(r, vector<T>(c)) {}

    vector<T>& operator[](size_t index) {
        return data[index];
    }

    const vector<T>& operator[](size_t index) const {
        return data[index];
    }

    pair<size_t, size_t> Size() const {
        return {rows, cols};
    }
};

int main() {
    Table<int> test(2, 3);
    test[0][0] = 4;
    cout << test[0][0] << endl;
    return 0;
}