/*
Задание 1
Очередь клиентов
Вам нужно создать приложение, которое имитирует очередь в окошко. Для этого нужно создать два потока, работающие с одной разделяемой переменной.

Первый поток имитирует клиента: раз в секунду он обращается к счётчику клиентов и увеличивает его на 1. Максимальное количество клиентов должно быть параметризировано.

Второй поток имитирует операциониста: раз в 2 секунды он обращается к счётчику клиентов и уменьшает его на 1. «Операционист» работает до последнего клиента.
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> client_count(0);
std::atomic<bool> generator_done(false);

void client_generator(int max_clients) {
    while (client_count < max_clients) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++client_count;
        std::cout << "[Клиент] Пришёл клиент. Всего: " << client_count.load() << std::endl;
    }
    generator_done = true;
}

void operator_worker() {
    while (!generator_done || client_count > 0) {
        if (client_count > 0) {
            --client_count;
            std::cout << "[Оператор] Обслужен клиент. Осталось: " << client_count.load() << std::endl;
        }
        else {
            std::cout << "[Оператор] Нет клиентов, ожидаем..." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "[Оператор] Все клиенты обслужены. Работа завершена." << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int max_clients;
    std::cout << "Введите максимальное количество клиентов: ";
    std::cin >> max_clients;

    std::thread t1(client_generator, max_clients);
    std::thread t2(operator_worker);

    t1.join();
    t2.join();

    std::cout << "Программа завершена." << std::endl;
    return 0;
}