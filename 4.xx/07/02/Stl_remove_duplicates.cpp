/*
Задача 2. Удаление дубликатов
Описание
Вам поступают числа из стандартного потока ввода. Первым числом вводится количество элементов, далее сами значения.

Нужно вывести все эти числа без дубликатов в порядке убывания.

Пример правильной работы программы
[IN]:
6
1
5
1
3
4
4
[OUT]: 
5
4
3
1
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    
    std::set<int> unique_numbers;
    
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        unique_numbers.insert(num);
    }
    
    std::vector<int> sorted_numbers(unique_numbers.begin(), unique_numbers.end());
    std::sort(sorted_numbers.rbegin(), sorted_numbers.rend());
    
    for (int num : sorted_numbers) {
        std::cout << num << std::endl;
    }
    
    return 0;
}
