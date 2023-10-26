#include <iostream>
#include <ctime>
#include <cstdlib> // Для функции rand()
#include <vector>
#include <algorithm> // Для сортировки массива
using namespace std;

// Функция для алгоритма BLS (Бинарный поиск)
int binarySearch(const vector<int>& arr, int key, int& comparisons) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++; // Увеличиваем счетчик сравнений
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Элемент не найден
}

// Функция для алгоритма SLS (Линейный поиск)
int linearSearch(const vector<int>& arr, int key, int& comparisons) {
    for (int i = 0; i < arr.size(); i++) {
        comparisons++; // Увеличиваем счетчик сравнений
        if (arr[i] == key) {
            return i;
        }
    }
    
    return -1; // Элемент не найден
}

int main() 
{
    // Генерация данных
    srand(time(0)); // Инициализация генератора случайных чисел
    vector<int> sortedArray;
    vector<int> unsortedArray;

    // Заполнение массивов случайными числами
    for (int i = 0; i < 200000; i++) 
    {
        int num = rand();
        sortedArray.push_back(num);
        unsortedArray.push_back(num);
    }

    // Сортировка sortedArray
    sort(sortedArray.begin(), sortedArray.end());

    // Определите размерности массивов и ключ поиска
    int sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int searchKey = sortedArray[0]; // Используйте ключ, который находится в начале массива

    // Проведение измерений
    for (int i = 0; i < 10; i++) {
        int size = sizes[i];
        vector<int> subArray(sortedArray.begin(), sortedArray.begin() + size); // Выбираем подмассив

        int comparisonsBLS = 0;
        clock_t startBLS = clock();
        int resultBLS = binarySearch(subArray, searchKey, comparisonsBLS);
        clock_t endBLS = clock();
        double durationBLS = double(endBLS - startBLS) / CLOCKS_PER_SEC;

        int comparisonsSLS = 0;
        clock_t startSLS = clock();
        int resultSLS = linearSearch(subArray, searchKey, comparisonsSLS);
        clock_t endSLS = clock();
        double durationSLS = double(endSLS - startSLS) / CLOCKS_PER_SEC;

        cout << "Size: " << size << endl;
        cout << "BLS: Time - " << durationBLS << "s, Comparisons - " << comparisonsBLS << endl;
        cout << "SLS: Time - " << durationSLS << "s, Comparisons - " << comparisonsSLS << endl;
        cout << "-----------------------------------------" << endl;
    }

    return 0;
}
