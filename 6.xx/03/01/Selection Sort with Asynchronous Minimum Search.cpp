/*
Задание 1
Сортировка выбором
Реализуйте алгоритм сортировки выбором.
Сортировка выбором состоит в том, что в неупорядоченном списке находится наименьший элемент. Выбранный в исходном списке минимальный элемент записывается на i-е место исходного списка (i=1,2,…,п), а элемент с i-го места — на место выбранного. При этом очевидно, что уже упорядоченные элементы, а они будут расположены, начиная с первого места, исключаются из дальнейшей сортировки, поэтому длина списка, участвующего в каждом последующем просмотре, должна быть на один элемент меньше предыдущего.
Поиск минимального элемента реализуйте в виде асинхронной задачи.
Результат должен возвращаться в основной поток через связку std::promise-std::future.
*/
#include <iostream>
#include <vector>
#include <future>
#include <algorithm>

// Асинхронный поиск индекса минимального элемента
std::future<size_t> find_min_index_async(const std::vector<int>& vec, size_t start) {
    std::promise<size_t> prom;
    auto fut = prom.get_future();

    std::thread([&vec, start, p = std::move(prom)]() mutable {
        size_t min_index = start;
        for (size_t i = start + 1; i < vec.size(); ++i) {
            if (vec[i] < vec[min_index]) {
                min_index = i;
            }
        }
        p.set_value(min_index);
    }).detach();

    return fut;
}

void selection_sort_async(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        auto fut = find_min_index_async(vec, i);
        size_t min_index = fut.get();

        if (min_index != i) {
            std::swap(vec[i], vec[min_index]);
        }
    }
}

int main() {
    std::vector<int> data = {64, 25, 12, 22, 11};

    selection_sort_async(data);

    std::cout << "Sorted array: ";
    for (const auto& val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}