#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

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
    int searchKey = sortedArray[0];

    for (int i = 0; i < 10; i++) {
        int size = sizes[i];
        vector<int> subArray(sortedArray.begin(), sortedArray.begin() + size);

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

        int comparisonsOAS = 0;
        clock_t startOAS = clock();
        int resultOAS = ordinaryArraySearch(subArray, searchKey, comparisonsOAS);
        clock_t endOAS = clock();
        double durationOAS = double(endOAS - startOAS) / CLOCKS_PER_SEC;

        int comparisonsBS = 0;
        clock_t startBS = clock();
        int resultBS = binarySearchSorted(subArray, searchKey, comparisonsBS);
        clock_t endBS = clock();
        double durationBS = double(endBS - startBS) / CLOCKS_PER_SEC;

        cout << "Size: " << size << endl;
        cout << "BLS: Time - " << durationBLS << "s, Comparisons - " << comparisonsBLS << endl;
        cout << "SLS: Time - " << durationSLS << "s, Comparisons - " << comparisonsSLS << endl;
        cout << "OAS: Time - " << durationOAS << "s, Comparisons - " << comparisonsOAS << endl;
        cout << "BS: Time - " << durationBS << "s, Comparisons - " << comparisonsBS << endl;
        cout << "-----------------------------------------" << endl;
    }

    return 0;
}
