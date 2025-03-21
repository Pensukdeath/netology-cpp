/*
Задача 1. Уникальный вектор
Описание
Нужно реализовать функцию, которая удаляет все дубликаты, а не только подряд идущие, из std::vector.

Пример правильной работы программы
[IN]: 1 1 2 5 6 1 2 4
[OUT]: 1 2 4 5 6
Подсказки
Не читайте этот раздел сразу. Попытайтесь сначала решить задачу самостоятельно :)

Что использовать для решения.
Для корректной работы std::unique нужно отсортировать исходный вектор.
*/

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> removeDuplicates(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
    auto it = std::unique(vec.begin(), vec.end());
    vec.erase(it, vec.end());
    return vec;
}

int main() {
    std::vector<int> vec = {1, 1, 2, 5, 6, 1, 2, 4};
    
    std::vector<int> uniqueVec = removeDuplicates(vec);
    
    for (int num : uniqueVec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}