/*
Задание 2
Параллельные вычисления
Напишите программу для расчёта суммы двух векторов.
Распараллельте эту программу на 2, 4, 8 и 16 потоков.
Определите, какое количество потоков даёт самый быстрый результат.
Сравните результаты выполнения для массивов из 1 000, 10 000, 100 000 и 1 000 000 элементов.
Время выполнения для каждого варианта сведите в таблицу и выведите её в консоль.
Первый запущенный поток должен вывести на экран доступное количество аппаратных ядер.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;
using namespace std::chrono;

void vector_add_part(const vector<int>& a, const vector<int>& b, vector<int>& result, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        result[i] = a[i] + b[i];
    }
}

double parallel_vector_add(size_t size, int thread_count) {
    vector<int> a(size, 1);
    vector<int> b(size, 2);
    vector<int> result(size);

    vector<thread> threads;
    size_t chunk_size = (size + thread_count - 1) / thread_count;

    auto start_time = high_resolution_clock::now();

    for (int t = 0; t < thread_count; ++t) {
        size_t start_idx = t * chunk_size;
        size_t end_idx = min(start_idx + chunk_size, size);
        if (start_idx < end_idx) {
            threads.emplace_back(vector_add_part, cref(a), cref(b), ref(result), start_idx, end_idx);
        }
    }

    for (auto& th : threads) {
        th.join();
    }

    auto end_time = high_resolution_clock::now();
    duration<double> diff = end_time - start_time;
    return diff.count();
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<size_t> sizes = { 1000, 10000, 100000, 1000000 };
    vector<int> thread_counts = { 1, 2, 4, 8, 16 };

    cout << "Количество аппаратных ядер - " << thread::hardware_concurrency() << "\n\n";

    cout << setw(12) << " ";
    for (size_t size : sizes)
        cout << setw(13) << size;
    cout << endl;

    for (int threads : thread_counts) {
        cout << setw(12) << (to_string(threads) + " потоков");
        for (size_t size : sizes) {
            double time_s = parallel_vector_add(size, threads);
            cout << setw(12) << fixed << setprecision(6) << time_s << "s";
        }
        cout << endl;
    }

    return 0;
}