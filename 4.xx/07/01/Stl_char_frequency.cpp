/*
Задача 1. Частота символов
Описание
Нужно посчитать, сколько раз каждый символ встречается в заданном тексте, и отсортировать по убыванию частоты.

Пример правильной работы программы
[IN]: Hello world!!
[OUT]: 
l: 3
o: 2
!: 2
 : 1
H: 1
e: 1
d: 1
w: 1
r: 1
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::string input;
    std::getline(std::cin, input);
    
    std::map<char, int> freq;
    
    for (char ch : input) {
        freq[ch]++;
    }
    
    std::vector<std::pair<char, int>> sorted_freq(freq.begin(), freq.end());
    
    std::sort(sorted_freq.begin(), sorted_freq.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });
    
    for (const auto &p : sorted_freq) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
    
    return 0;
}