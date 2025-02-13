/*
Задача 2. Быстрая сортировка
Нужно написать функцию с сигнатурой void quick_sort(int* arr, int size), которая принимает на вход массив целых чисел и его размер. Функция должна отсортировать полученный массив методом «быстрая сортировка».

Затем нужно протестировать написанную функцию. Для проверки используйте массивы:

3 43 38 29 18 72 57 61 2 33;
88 91 87 59 53 49 29 16 4 27 28 89 2 25 74;
24 66 20 79 30 16 19 62 94 59 0 7 59 90 84 60 95 62.
Выведите на экран массив до и после сортировки.

Примеры работы программы
Исходный массив: 3 43 38 29 18 72 57 61 2 33
Отсортированный массив: 2 3 18 29 33 38 43 57 61 72
Исходный массив: 88 91 87 59 53 49 29 16 4 27 28 89 2 25 74
Отсортированный массив: 2 4 16 25 27 28 29 49 53 59 74 87 88 89 91
Исходный массив: 24 66 20 79 30 16 19 62 94 59 0 7 59 90 84 60 95 62
Отсортированный массив: 0 7 16 19 20 24 30 59 59 60 62 62 66 79 84 90 94 95
*/

#include <iostream>

using namespace std;

void quick_sort(int* arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[right];
    int i = left, j = right - 1;
    while (i <= j) {
        while (i <= j && arr[i] < pivot) i++;
        while (i <= j && arr[j] > pivot) j--;
        if (i <= j) swap(arr[i++], arr[j--]);
    }
    swap(arr[i], arr[right]);
    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
}

void quick_sort(int* arr, int size) {
    quick_sort(arr, 0, size - 1);
}

void print_array(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int arr1[] = {3, 43, 38, 29, 18, 72, 57, 61, 2, 33};
    int arr2[] = {88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74};
    int arr3[] = {24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62};
    int sizes[] = {10, 15, 18};
    int* arrays[] = {arr1, arr2, arr3};
    
    for (int i = 0; i < 3; i++) {
        cout << "Исходный массив: ";
        print_array(arrays[i], sizes[i]);
        quick_sort(arrays[i], sizes[i]);
        cout << "Отсортированный массив: ";
        print_array(arrays[i], sizes[i]);
        cout << endl;
    }
    
    return 0;
}
