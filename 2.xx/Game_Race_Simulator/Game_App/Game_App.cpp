// Game_App.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "Camel.h"
#include "FastCamel.h"
#include "Centaur.h"
#include "AllTerrainBoots.h"
#include "FlyingCarpet.h"
#include "Eagle.h"
#include "Broom.h"
#include "GameLib.h"

using namespace std;

void registerVehicles(vector<Transport*>& registeredVehicles, bool isGroundRace, bool isFlyingRace) {
    int choice;
    char continueRegistration;
    vector<Transport*> selectedVehicles;

    do {
        cout << "=========================================\n";
        cout << "Выберите транспорт для регистрации:\n";
        cout << "=========================================\n";

        if (isGroundRace) {
            cout << "1 - Верблюд (Наземное)\n";
            cout << "2 - Верблюд-быстроход (Наземное)\n";
            cout << "3 - Кентавр (Наземное)\n";
            cout << "4 - Ботинки-вездеходы (Наземное)\n";
        }

        if (isFlyingRace) {
            cout << "5 - Ковёр-самолёт (Воздушное)\n";
            cout << "6 - Орёл (Воздушное)\n";
            cout << "7 - Метла (Воздушное)\n";
        }
        cout << "=========================================\n";
        cout << "Введите номер транспорта для регистрации: ";

        while (!(cin >> choice) ||
            (isGroundRace && choice < 1 || choice > 4) &&
            (isFlyingRace && choice < 5 || choice > 7)) {
            cout << "Некорректный ввод! Выберите правильный номер транспорта.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Transport* newVehicle = nullptr;

        switch (choice) {
        case 1:
            if (isGroundRace) {
                newVehicle = new Camel();
            }
            break;
        case 2:
            if (isGroundRace) {
                newVehicle = new FastCamel();
            }
            break;
        case 3:
            if (isGroundRace) {
                newVehicle = new Centaur();
            }
            break;
        case 4:
            if (isGroundRace) {
                newVehicle = new AllTerrainBoots();
            }
            break;
        case 5:
            if (isFlyingRace) {
                newVehicle = new FlyingCarpet();
            }
            break;
        case 6:
            if (isFlyingRace) {
                newVehicle = new Eagle();
            }
            break;
        case 7:
            if (isFlyingRace) {
                newVehicle = new Broom();
            }
            break;
        default:
            break;
        }

        bool isAlreadySelected = false;
        for (auto& vehicle : selectedVehicles) {
            if (vehicle->getName() == newVehicle->getName()) {
                isAlreadySelected = true;
                break;
            }
        }

        if (!isAlreadySelected) {
            registeredVehicles.push_back(newVehicle);
            selectedVehicles.push_back(newVehicle);
        }
        else {
            cout << "Этот транспорт уже выбран! Выберите другой транспорт.\n";
            delete newVehicle;
        }

        cout << "Хотите зарегистрировать еще транспорт? (1 - да, 0 - нет): ";
        while (!(cin >> continueRegistration) || (continueRegistration != '0' && continueRegistration != '1')) {
            cout << "Некорректный ввод! Введите 1 для продолжения или 0 для завершения.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (continueRegistration == '1');
}




void startRace(vector<Transport*>& registeredVehicles, double distance) {
    if (registeredVehicles.size() < 2) {
        cout << "Для начала гонки необходимо зарегистрировать хотя бы два разных ТС.\n";
        return;
    }

    vector<pair<string, double>> results;

    for (auto& vehicle : registeredVehicles) {
        results.push_back({ vehicle->getName(), vehicle->getTime(distance) });
    }

    sort(results.begin(), results.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second < b.second;
        });

    cout << "Результаты гонки:\n";
    for (const auto& result : results) {
        cout << result.first << ": " << result.second << " часов\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Transport*> registeredVehicles;
    int raceType;
    double distance;
    int repeatRace;

    do {
        cout << "=========================================\n";
        cout << "Добро пожаловать в симулятор гонок!\n";
        cout << "=========================================\n";
        cout << "Выберите тип гонки:\n";
        cout << "1 - Наземная гонка\n";
        cout << "2 - Воздушная гонка\n";
        cout << "3 - Гонка Наземного и Воздушного ТС\n";
        cout << "=========================================\n";
        cout << "Введите номер типа гонки: ";
        while (!(cin >> raceType) || (raceType < 1 || raceType > 3)) {
            cout << "Некорректный ввод! Пожалуйста, выберите правильный номер гонки.\n";
            cin.clear();
        }

        cout << "Введите расстояние для гонки (в километрах): ";
        while (!(cin >> distance) || (distance <= 0)) {
            cout << "Некорректный ввод! Пожалуйста, введите положительное значение.\n";
            cin.clear();
        }

        switch (raceType) {
        case 1:
            registerVehicles(registeredVehicles, true, false);
            break;
        case 2:
            registerVehicles(registeredVehicles, false, true);
            break;
        case 3:
            registerVehicles(registeredVehicles, true, true);
            break;
        default:
            break;
        }

        startRace(registeredVehicles, distance);

        cout << "Хотите повторить гонку? (1 - да, 0 - нет): ";
        while (!(cin >> repeatRace) || (repeatRace != 0 && repeatRace != 1)) {
            cout << "Некорректный ввод! Введите 1 для повторения или 0 для выхода.\n";
            cin.clear();
        }

        for (auto& vehicle : registeredVehicles) {
            delete vehicle;
        }
        registeredVehicles.clear();
    } while (repeatRace == 1);

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
