#include <iostream>
#include <vector>

void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    int gap = n / 2;

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
        gap /= 2;
    }
}

void cocktailSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;

        swapped = false;
        end--;

        for (int i = end; i > start; i--) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
        start++;
    }

}
}

int main() 
{
    std::vector<int> data = { };
    for (int size :  {
        std::vector<int> data(size);
        int key = data[size / 2]; //  люч ищетс€ в центре

        for (int i = 0; i < size; ++i) {
            data[i] = rand() % size;
        }
    cocktailSort(random_array);
    shellSort(random_array);
    // ¬ыведите массив на каждом промежуточном этапе сортировки и сравните счетчики сравнений и пересылок
    return 0;
    // ¬ыведите массив на каждом промежуточном этапе сортировки и сравните счетчики сравнений и пересылок
    return 0;
}