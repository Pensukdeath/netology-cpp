#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace std::chrono;

mutex cout_mutex;

const int BAR_WIDTH = 20;

void move_cursor_to_line(int line) {
    cout << "\033[" << (line + 1) << ";0H";
}

void progress_bar(int index, int duration_ms) {
    auto id = this_thread::get_id();
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i <= BAR_WIDTH; ++i) {
        {
            lock_guard<mutex> lock(cout_mutex);
            move_cursor_to_line(index);
            cout << setw(2) << index << "  ";
            cout << setw(6) << hash<thread::id>{}(id) % 100000 << "  ";
            cout << "[";
            for (int j = 0; j < i; ++j) cout << "#";
            for (int j = i; j < BAR_WIDTH; ++j) cout << " ";
            cout << "]       \r" << flush;
        }
        this_thread::sleep_for(chrono::milliseconds(duration_ms / BAR_WIDTH));
    }

    auto end_time = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end_time - start_time).count();

    {
        lock_guard<mutex> lock(cout_mutex);
        move_cursor_to_line(index);
        cout << setw(2) << index << "  ";
        cout << setw(6) << hash<thread::id>{}(id) % 100000 << "  ";
        cout << "[";
        for (int j = 0; j < BAR_WIDTH; ++j) cout << "#";
        cout << "]  " << elapsed << " ms" << endl;
    }
}

int main() {
    int thread_count = 5;
    int total_duration_ms = 2000;

    cout << "\033[2J\033[H";

    vector<thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(progress_bar, i, total_duration_ms);
    }

    for (auto& t : threads)
        t.join();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
