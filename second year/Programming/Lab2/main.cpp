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

int binarySearch(const vector<int>& arr, int key, int& comparisons) {
    
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
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

int linearSearch(const vector<int>& arr, int key, int& comparisons) {
    for (int i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == key) {
            return i;
        }
    }
    
    return -1;
}

int ordinaryArraySearch(const vector<int>& arr, int key, int& comparisons) {
    for (int i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == key) {
            return i;
        } else if (arr[i] > key) {
            break; // Так как массив отсортирован по неубыванию, можно прекратить поиск
        }
    }
    
    return -1;
}

int binarySearchSorted(const vector<int>& arr, int key, int& comparisons) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
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
    unsigned __int64 start,end;
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
            unsigned __int64  startBLS= __rdtsc();
            int resultBLS = binarySearch(subArray, keys[key], comparisonsBLS);
            unsigned __int64 endBLS = __rdtsc();
            double durationBLS = double(endBLS - startBLS) / 10000000;

            int comparisonsSLS = 0;
            unsigned __int64  startSLS= __rdtsc();
            int resultSLS = linearSearch(subArray, keys[key], comparisonsSLS);
            unsigned __int64  endSLS= __rdtsc();
            double durationSLS = double(endSLS - startSLS) / 10000000;

            int comparisonsOAS = 0;
            unsigned __int64  startOAS= __rdtsc();
            int resultOAS = ordinaryArraySearch(subArray, keys[key], comparisonsOAS);
            unsigned __int64  endOAS= __rdtsc();
            double durationOAS = double(endOAS - startOAS) / 10000000;

            int comparisonsBS = 0;
            unsigned __int64  startBS= __rdtsc();
            int resultBS = binarySearchSorted(subArray, keys[key], comparisonsBS);
            unsigned __int64  endBS= __rdtsc();
            double durationBS = double(endBS - startBS) / 10000000;

            cout << "Size: " << size << endl;
            cout << "BLS: Time - " << durationBLS <<fixed<< "s, Comparisons - " << comparisonsBLS << endl;
            cout << "SLS: Time - " << durationSLS <<fixed<< "s, Comparisons - " << comparisonsSLS << endl;
            cout << "OAS: Time - " << durationOAS <<fixed<< "s, Comparisons - " << comparisonsOAS << endl;
            cout << "BS: Time - " << durationBS <<fixed<< "s, Comparisons - " << comparisonsBS << endl;
            cout << "-----------------------------------------" << endl;
        }
    }

    return 0;
}
