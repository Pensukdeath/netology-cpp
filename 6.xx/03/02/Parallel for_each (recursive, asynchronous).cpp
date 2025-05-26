/*
Задание 2
For_each
Реализуйте параллельный вариант оператора for_each.
Функция должна принимать итераторы на начало и конец контейнера и ссылку, обрабатывающую функцию.
При реализации нужно рекурсивно разделить контейнер на несколько блоков и для каждого запустить отдельную задачу, применяющую обрабатывающую функцию к части контейнера.

*/

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <iterator>

template<typename Iterator, typename Func>
void parallel_for_each(Iterator begin, Iterator end, Func func, size_t min_block_size = 1000) {
    const size_t length = std::distance(begin, end);

    if (length <= min_block_size) {
        std::for_each(begin, end, func);
        return;
    }

    Iterator mid = begin;
    std::advance(mid, length / 2);

    auto fut = std::async(std::launch::async, parallel_for_each<Iterator, Func>, begin, mid, func, min_block_size);
    parallel_for_each(mid, end, func, min_block_size);

    fut.get(); // дождаться завершения первой половины
}

int main() {
    std::vector<int> data(10000, 1); // большой вектор из 10000 единиц

    parallel_for_each(data.begin(), data.end(), [](int& x) { x += 1; });

    std::cout << "First 10 values after parallel for_each: ";
    for (size_t i = 0; i < 10; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}