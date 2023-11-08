#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <intrin.h>

#pragma intrinsic(__rdtsc)


using namespace std;

int betterlinerSearch(const vector<int>& arr, int key, int& comparisons, int& comparisons_i) {
    int size=arr.size();
	for (int i = 0; i < size; i++) //Цикл алгоритма поиска
	{
		comparisons_i++;
		if (arr[i] == key) //Сравнение с ключом
		{
			comparisons++;
			return i;
		}
		else
		{
			comparisons++;
		}
    
    }
    return 0;
}

int linearSearch(const vector<int>& arr, int key, int& comparisons) {
    vector<int> arrCopy = arr; 
    int size = arrCopy.size();
    int last = arrCopy[size - 1]; // Последнее значение
    arrCopy[size - 1] = key; // Значение последнего члена массива
    int i = 0; // Индекс
    while (arrCopy[i] != key) // Сравнение элемента массива с ключом
    {
        i++;
        comparisons++;
    }
    arrCopy[size - 1] = last;
    if ((i < size - 1) or ((arrCopy[size - 1]) == key)) // Вывод индекса
    {
        return i;
    }
    return -1;
}

int ordinaryArraySearch(const vector<int>& arr, int key) 
{
    vector<int> arrCopy = arr;
    int size=arr.size();
    int last = arrCopy[size - 1];//Последнее значение
	arrCopy[size - 1] = LLONG_MAX;
	int i = 0;//Индекс
	while (key > arr[i])//Сравнение элемента массива с ключом 
	{
		i++;
	}
	arrCopy[size - 1] = last;//Концу массива присваиваем обратно последний элемент
	if (key == arr[i])//Вывод индекса
	{
		return i;
	}
	if (key== arrCopy[size - 1])
	{
		return size - 1;
	}
    return -1;
}

int binarySearchSorted(const vector<int>& arr, int key) 
{
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }


    return -1;
}

int main() {
    srand(time(0));
    vector<int> sortedArray;
    vector<int> unsortedArray;

    for (int i = 0; i < 200000; i++) {
        int num = rand();
        sortedArray.push_back(num);
        unsortedArray.push_back(num);
    }

    sort(sortedArray.begin(), sortedArray.end());

    int sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int keys[]={16,9000,18990};

    for (int key=0; key<3; key++)
    {
        cout<<"Для ключа в индексе: "<<keys[key]<<endl;
        for (int i = 0; i < 10; i++) 
        {
            int size = sizes[i];
            vector<int> subArray(sortedArray.begin(), sortedArray.begin() + size);


            int comparisonsBLS = 0;
            int comparisonsBLS_i = 0;
            unsigned __int64  startBLS= __rdtsc();
            int resultBLS = betterlinerSearch(unsortedArray, keys[key], comparisonsBLS, comparisonsBLS_i);
            cout << "Индекс равен: " << resultBLS << endl;
			cout << "Кол-во сравнений с ключом: " << comparisonsBLS<< endl;
			cout << "Кол-во сравнений в цикле: " <<  comparisonsBLS_i<< endl;
            unsigned __int64 endBLS = __rdtsc();
            double durationBLS = double(endBLS - startBLS) / 10000000;


            int comparisonsSLS = 0;
            int comparisonsSLS_i = 0;
            unsigned __int64  startSLS= __rdtsc();
            int resultSLS = linearSearch(unsortedArray, keys[key], comparisonsSLS);
            cout << "Индекс равен: " << resultSLS << endl;
            unsigned __int64  endSLS= __rdtsc();
            double durationSLS = double(endSLS - startSLS) / 10000000;


            unsigned __int64  startOAS= __rdtsc();
            int resultOAS = ordinaryArraySearch(subArray, keys[key]);
            cout << "Индекс равен: " << resultOAS << endl;
            unsigned __int64  endOAS= __rdtsc();
            double durationOAS = double(endOAS - startOAS) / 10000000;

            
            unsigned __int64  startBS= __rdtsc();
            int resultBS = binarySearchSorted(subArray, keys[key]);
            unsigned __int64  endBS= __rdtsc();
            double durationBS = double(endBS - startBS) / 10000000;

            cout << "Size: " << size << endl;
            cout << "BLS: Time - " << durationBLS <<fixed<< "s, Comparisons - " << comparisonsBLS <<", "<<comparisonsBLS_i<< endl;
            cout << "SLS: Time - " << durationSLS <<fixed<< "s, Comparisons - " << comparisonsSLS << endl;
            cout << "OAS: Time - " << durationOAS <<fixed<< "s" << endl;
            cout << "BS: Time - " << durationBS <<fixed<< "s" << endl;
            cout << "-----------------------------------------" << endl;
        }
    }

    return 0;
}
