// Sort_Address.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Задача 2. Сортируем адреса
В этом задании вы будете читать из файла адреса и выводить их в другой файл в другом формате, отсортированными по названию города.

Вам дан файл in.txt, в котором находится N адресов. Число N идёт первым в файле. После числа N располагаются N блоков по 4 строки в каждом. Каждый блок состоит из следующих строк: название города, название улицы, номер дома, номер квартиры.

Задача программы заключается в том, чтобы считать адреса из файла in.txt, отсортировать их по названию города и вывести отсортированный список адресов в файл out.txt в другом формате. Не забудьте вывести количество адресов в начале.

Города должны быть отсортированы в алфавитном порядке.

Формат вывода адреса: <название города>, <название улицы>, <номер дома>, <номер квартиры>.

Пример работы программы
in.txt
5
Москва
Строителей
34
12
Новокузнецк
Науки
5
16
Омск
Пушкина
2
13
Москва
Арбат
4
1
Новосибирск
Мира
85
64
out.txt
5
Москва, Строителей, 34, 12
Москва, Арбат, 4, 1
Новокузнецк, Науки, 5, 16
Новосибирск, Мира, 85, 64
Омск, Пушкина, 2, 13
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
    Address(){
        City;
        Street;
        Home;
        Apartament;
    }
    void add(string City, string Street, int Home, int Apartament) {
        this->City = City;
        this->Street = Street;
        this->Home = Home;
        this->Apartament = Apartament;
    }
    void move(ofstream& out) {
        cout << City << ", " << Street << ", " << Home << ", " << Apartament << endl;
        
        out << City << ", " << Street << ", " << Home << ", " << Apartament << endl;
    }
    string getCity() {
        return City;
    }
};
void sort(Address* in_arr, int size) {
    for (int i = 0; i < size; i++) {
        bool flag = true;
        for (int j = 0; j < size - (i + 1); j++) {
            if (in_arr[j].getCity() > in_arr[j + 1].getCity()) {
                flag = false;
                swap(in_arr[j], in_arr[j + 1]);
            }
        }
        if (flag) {
            break;
        }
    }
}
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
        sort(in_arr, size);
        for (int i = 0; i < size; i++) {
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


/*
        string get_city()
    {
        return City;
    }

    void swap_strings(Address& in_arr1, Address& in_arr2)  // сравнение городов и замена функций.
    {
        string str1, str2;
        int tmp1, tmp2;

        str1 = in_arr2.City;
        str2 = in_arr2.Street;
        tmp1 = in_arr2.Home;
        tmp2 = in_arr2.Apartament;

        in_arr2.City = in_arr1.City;
        in_arr2.Street = in_arr1.Street;
        in_arr2.Home = in_arr1.Home;
        in_arr2.Apartament = in_arr1.Apartament;

        in_arr1.City = str1;
        in_arr1.Street = str2;
        in_arr1.Home = tmp1;
        in_arr1.Apartament = tmp2;
    }

    string str1, str2;
    for (int i = 0; i < size - 1; i++) // сортировка пузырьком
    {
        for (int j = 1; j < size; j++)
        {
            str1 = arr[i].get_sity_name();
            str2 = arr[j].get_sity_name();
            if (str1 > str2)
            {
                arr[i].swap_strings(arr[i], arr[j]);
            }
        }
    }
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
