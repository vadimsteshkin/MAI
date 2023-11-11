#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <intrin.h>
#include <algorithm>
#include <chrono>

#pragma intrinsic(__rdtsc)

using namespace std;
void printArray(vector<int>& arr)
{
    for (int i=0; i<arr.size();i++)
    {
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}
void shellSort(vector<int>& arr, int& comparisons,int n)
{
    //cout<<"Сортировка Шелла"<<endl;
    int gap = n / 2;

    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                comparisons++;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            comparisons++;

            arr[j] = temp;
            //printArray(arr);
        }
        gap /= 2;
    }
    //printArray(arr);
}

void cocktailSort(vector<int>& arr, long long& comparisons, int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; i++)
        {
            comparisons++;
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                swapped = true;
                //printArray(arr);
            }
        }
        if (!swapped)
        {
            break;
        }
        swapped = false;
        end--;

        for (int i = end; i > start; i--)
        {
            comparisons++;
            if (arr[i] < arr[i - 1])
            {
                swap(arr[i], arr[i - 1]);
                swapped = true;
                //printArray(arr);
            }
        }
        start++;
    }

}

int main()
{
    //vector<int> lengths={20};
    vector<int> lengths={1000, 10000, 50000, 100000 };
    for (int j=0;j<lengths.size();j++)
    {
        int n=lengths[j];
        srand(time(0));
        vector<int> Array;
        vector<int> sortedArray;
        vector<int> reverseSortedArray;

        for (int i = 0; i < n; i++)
        {
            int num = rand();
            Array.push_back(num);
            sortedArray.push_back(num);
            reverseSortedArray.push_back(num);
        }
        sort(sortedArray.begin(), sortedArray.end());
        sort(reverseSortedArray.begin(), reverseSortedArray.end(),greater<>());

        //cout<<"Массив"<<endl;
        //printArray(reverseSortedArray);

        vector<int> ArrayCopy = Array;
        vector<int> sortedArrayCopy = sortedArray;
        vector<int> reverseSortedArrayCopy = reverseSortedArray;

        long long comparisonsCS = 0;
        unsigned __int64  startCS= __rdtsc();
        cocktailSort(ArrayCopy, comparisonsCS,n);
        unsigned __int64  endCS= __rdtsc();
        double durationCS = double(endCS - startCS) / 10000000000;

        long long comparisonsSCS = 0;
        unsigned __int64  startSCS= __rdtsc();
        cocktailSort(sortedArrayCopy,comparisonsSCS,n);
        unsigned __int64  endSCS= __rdtsc();
        double durationSCS = double(endSCS - startSCS) / 10000000000;

        long long comparisonsRCS = 0;
        unsigned __int64  startRCS= __rdtsc();
        cocktailSort(reverseSortedArrayCopy,comparisonsRCS,n);
        unsigned __int64  endRCS= __rdtsc();
        double durationRCS = double(endRCS - startRCS) / 10000000000;


        vector<int> ArrayCopyC = Array;
        vector<int> sortedArrayCopyC = sortedArray;
        vector<int> reverseSortedArrayCopyC = reverseSortedArray;

        int comparisonsSS = 0;
        unsigned __int64  startSS= __rdtsc();
        shellSort(ArrayCopyC,comparisonsSS,n);
        unsigned __int64  endSS= __rdtsc();
        double durationSS = double(endSS - startSS) / 10000000000;

        int comparisonsSSS = 0;
        unsigned __int64  startSSS= __rdtsc();
        shellSort(sortedArrayCopyC,comparisonsSSS,n);
        unsigned __int64  endSSS= __rdtsc();
        double durationSSS = double(endSSS - startSSS) / 10000000000;

        int comparisonsRSS = 0;
        unsigned __int64  startRSS= __rdtsc();
        shellSort(reverseSortedArrayCopyC,comparisonsRSS,n);
        unsigned __int64  endRSS= __rdtsc();
        double durationRSS = double(endRSS - startRSS) / 10000000000;

        cout<<"Время сортировки Шелла при длине "<<n<<" равно "<<durationSS<<fixed<<" Сравнения: "<<comparisonsSS<<endl;
        cout<<"Время сортировки Шелла на отсортированном массиве при длине "<<n<<" равно "<<durationSSS<<fixed<<" Сравнения: "<<comparisonsSSS<<endl;
        cout<<"Время сортировки Шелла отсортированном по убыванию массиве при длине "<<n<<" равно "<<durationRSS<<fixed<<" Сравнения: "<<comparisonsRSS<<endl;
        cout<<"Время Шейкерной сортировки при "<<n<<" равно "<<durationCS<<fixed<<" Сравнения: "<<comparisonsCS<<endl;
        cout<<"Время Шейкерной сортировки на отсортированном массиве при длине  "<<n<<" равно "<<durationSCS<<fixed<<" Сравнения: "<<comparisonsSCS<<endl;
        cout<<"Время Шейкерной сортировки отсортированном по убыванию массиве при длине "<<n<<" равно "<<durationRCS<<fixed<<" Сравнения: "<<comparisonsRCS<<endl;
    }
    return 0;
}