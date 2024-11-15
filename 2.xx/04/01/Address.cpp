// address.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
* Задача 1. Адреса
В этом задании вы будете читать адреса из файла и выводить их в другой файл в другом формате.

Вам дан файл in.txt, в котором находится N адресов. Число N идёт первым в файле. После числа N располагаются N блоков по 4 строки в каждом. Каждый блок состоит из следующих строк: название города, название улицы, номер дома, номер квартиры.

Задача программы заключается в том, чтобы считать адреса из файла in.txt и вывести их в файл out.txt в другом формате и в обратном порядке. Не забудьте вывести количество адресов в начале.

Формат вывода адреса: <название города>, <название улицы>, <номер дома>, <номер квартиры>.

Пример работы программы
in.txt
3
Москва
Строителей
34
12
Омск
Пушкина
2
13
Новосибирск
Мира
85
64
out.txt
3
Новосибирск, Мира, 85, 64
Омск, Пушкина, 2, 13
Москва, Строителей, 34, 12
*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

class Address {
private:
    string City;
    string Street;
    int Home = 0;
    int Apartament = 0;
public:
    void add(string City, string Street, int Home, int Apartament) {
        this->City = City;
        this->Street = Street;
        this->Home = Home;
        this->Apartament = Apartament;
    }
    void move(ofstream &out) {
        cout << City << ", " << Street << ", " << Home << ", " << Apartament << endl;
        out << City << ", " << Street << ", " << Home << ", " << Apartament << endl;
    }
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    fstream in("in.txt");
    int size = 0;
    
    if (in.is_open()) {
        in >> size;
        
        Address* in_arr = new Address[size];
        string address_str1, address_str2; int address_str3 = 0, address_str4 = 0;
        for (int i = 0; i < size; i++) {
            in >> address_str1;
            in >> address_str2;
            in >> address_str3;
            in >> address_str4;
            in_arr[i].add(address_str1, address_str2, address_str3, address_str4);
        }
        in.close();
        ofstream out("out.txt");
        out << size << endl;
        for (int i = 0; i < size; i++) {
            in_arr[i].move(out);
        }
        for (int i = size - 1; i >= 0; i--) {
            in_arr[i].move(out);
        }
        out.close();
        delete[] in_arr;
        
    }
    else {
        cout << "Файл in.txt - Не найден!" << endl;
    }

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
