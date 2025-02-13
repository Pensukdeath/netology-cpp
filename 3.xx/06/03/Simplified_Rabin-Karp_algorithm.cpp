/*
Задача 3. Упрощённый алгоритм Рабина-Карпа
В этом задании вам нужно реализовать функцию, которая находит в предоставленной строке заданную подстроку с помощью упрощённого алгоритма Рабина-Карпа. Назовём её find_substring_light_rabin_karp.

Функция должна принимать на вход две строки: в одной вы будете искать подстроку, а вторая будет этой подстрокой. Функция должна возвращать индекс найденной подстроки в строке. Если подстрока не была найдена, то возвращается -1.

После написания функции её необходимо протестировать. Для этого организуйте работу с пользователем. Попросите его ввести строку. В этой строке вы будете искать подстроки. Дальше попросите пользователя ввести подстроку, которую надо найти в введённой ранее строке. Программа должна вывести на консоль индекс найденной подстроки, а если подстрока не была найдена, то программа должна сообщить об этом пользователю. Продолжайте спрашивать у пользователя подстроку до тех пор, пока он не введёт exit. После того, как он ввёл exit, попытайтесь найти подстроку exit, сообщите пользователю о результате и завершите работу программы.

Пример работы программы
Введите строку, в которой будет осуществляться поиск: hellohellomydearfriend
Введите подстроку, которую нужно найти: hello
Подстрока hello найдена по индексу 0
Введите подстроку, которую нужно найти: lomy
Подстрока lomy найдена по индексу 8
Введите подстроку, которую нужно найти: year
Подстрока year не найдена
Введите подстроку, которую нужно найти: exit
Подстрока exit не найдена
Подсказки
Не читайте этот раздел сразу. Попытайтесь сначала решить задачу самостоятельно :)

Что использовать для решения.
Сигнатура функции будет выглядеть так: int find_substring_light_rabin_karp(std::string source, std::string substring).

Упрощённый алгоритм Рабина-Карпа подробно расписан в лекции.
*/

#include <iostream>
#include <string>

using namespace std;

int find_substring_light_rabin_karp(string source, string substring) {
    int n = source.length();
    int m = substring.length();
    
    if (m > n) return -1;

    const int p = 31;
    const int mod = 1e9 + 7;

    long long hash_substring = 0;
    for (int i = 0; i < m; i++) {
        hash_substring = (hash_substring * p + (substring[i] - 'a' + 1)) % mod;
    }

    long long hash_window = 0;
    for (int i = 0; i < m; i++) {
        hash_window = (hash_window * p + (source[i] - 'a' + 1)) % mod;
    }

    if (hash_substring == hash_window) {
        if (source.substr(0, m) == substring) {
            return 0;
        }
    }

    long long p_pow = 1;
    for (int i = 0; i < m - 1; i++) {
        p_pow = (p_pow * p) % mod;
    }

    for (int i = 1; i <= n - m; i++) {
        hash_window = (hash_window - (source[i - 1] - 'a' + 1) * p_pow % mod + mod) % mod;
        hash_window = (hash_window * p + (source[i + m - 1] - 'a' + 1)) % mod;

        if (hash_substring == hash_window) {
            if (source.substr(i, m) == substring) {
                return i;
            }
        }
    }

    return -1;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string source;
    cout << "Введите строку, в которой будет осуществляться поиск: ";
    cin >> source;

    string substring;
    while (true) {
        cout << "Введите подстроку, которую нужно найти: ";
        cin >> substring;

        if (substring == "exit") {
            if (find_substring_light_rabin_karp(source, "exit") == -1) {
                cout << "Подстрока exit не найдена\n";
            } else {
                cout << "Подстрока exit найдена\n";
            }
            break;
        }

        int result = find_substring_light_rabin_karp(source, substring);
        if (result != -1) {
            cout << "Подстрока " << substring << " найдена по индексу " << result << '\n';
        } else {
            cout << "Подстрока " << substring << " не найдена\n";
        }
    }

    return 0;
}