#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <intrin.h>
#include <algorithm>

#pragma intrinsic(__rdtsc)

using namespace std;

/**
 * @brief Выводит элементы массива на экран.
 * 
 * @param arr Массив, который нужно вывести.
 */
void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

/**
 * @brief Реализация сортировки Шелла с подсчетом числа сравнений и пересылок.
 * 
 * @param arr Массив, который нужно отсортировать.
 * @param comparisons Счетчик числа сравнений.
 * @param swaps Счетчик числа пересылок.
 * @param n Размер массива.
 * 
 * @details Сортировка Шелла является методом усовершенствованной сортировки вставками.
 * Основная идея заключается в том, чтобы сначала сравнивать и сортировать элементы,
 * находящиеся на некотором фиксированном расстоянии друг от друга (шаге).
 * Процесс повторяется с новыми значениями шага до тех пор, пока шаг не станет равным 1.
 * 
 * @note Сортировка Шелла хорошо справляется с частично упорядоченными массивами.
 */
void shellSort(vector<int>& arr, long long& comparisons, long long& swaps, int n) {
    int gap = n / 2;

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                comparisons++;
                swaps++;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            comparisons++;

            arr[j] = temp;
        }
        gap /= 2;
    }
}

/**
 * @brief Реализация Шейкерной сортировки с подсчетом числа сравнений и пересылок.
 * 
 * @param arr Массив, который нужно отсортировать.
 * @param comparisons Счетчик числа сравнений.
 * @param swaps Счетчик числа пересылок.
 * @param n Размер массива.
 *
 * @details Шейкерная сортировка, также известная как "шейкер-сорт" или "шейкерная сортировка",
 * представляет собой улучшенную версию пузырьковой сортировки.
 * Она движется в обоих направлениях по массиву, "выталкивая" максимальные элементы вправо и минимальные влево.
 *
 * @note Шейкерная сортировка эффективна для небольших массивов, но менее эффективна для больших объемов данных.
 */
void cocktailSort(vector<int>& arr, long long& comparisons, long long& swaps, int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                // swap(arr[i], arr[i + 1]);
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
                swaps++;
            }
        }

        if (!swapped) {
            break;
        }

        swapped = false;
        end--;

        for (int i = end; i > start; i--) {
            comparisons++;
            if (arr[i] < arr[i - 1]) {
                // swap(arr[i], arr[i - 1]);
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = true;
                swaps++;
            }
        }
        start++;
    }
}

int main() {
    // Заданные длины массивов для сортировки
    vector<int> lengths = {1000, 10000, 50000, 100000};

    // Итерация по заданным длинам массивов
    for (int j = 0; j < lengths.size(); j++) {
        int n = lengths[j];

        // Инициализация массивов
        srand(time(0));
        vector<int> Array;
        vector<int> sortedArray;
        vector<int> reverseSortedArray;

        // Заполнение массивов случайными числами
        for (int i = 0; i < n; i++) {
            int num = rand();
            Array.push_back(num);
            sortedArray.push_back(num);
            reverseSortedArray.push_back(num);
        }

        // Сортировка массивов для сравнения с отсортированными и в обратном порядке
        sort(sortedArray.begin(), sortedArray.end());
        sort(reverseSortedArray.begin(), reverseSortedArray.end(), greater<>());

        // Создание копий массивов для каждого алгоритма сортировки
        vector<int> ArrayCopy = Array;
        vector<int> sortedArrayCopy = sortedArray;
        vector<int> reverseSortedArrayCopy = reverseSortedArray;

        // Переменные для подсчета числа сравнений и пересылок в сортировке Шелла
        long long comparisonsCS = 0;
        long long swapsCS = 0;
        long long comparisonsSCS = 0;
        long long swapsSCS = 0;
        long long comparisonsRCS = 0;
        long long swapsRCS = 0;

        // Замер времени выполнения Шейкерной сортировки
        unsigned __int64 startCS = __rdtsc();
        cocktailSort(ArrayCopy, comparisonsCS, swapsCS, n);
        unsigned __int64 endCS = __rdtsc();
        double durationCS = double(endCS - startCS) / 1000000000;

        // Замер времени выполнения Шейкерной сортировки на отсортированном массиве
        unsigned __int64 startSCS = __rdtsc();
        cocktailSort(sortedArrayCopy, comparisonsSCS, swapsSCS, n);
        unsigned __int64 endSCS = __rdtsc();
        double durationSCS = double(endSCS - startSCS) / 1000000000;

        // Замер времени выполнения Шейкерной сортировки на массиве, отсортированном в обратном порядке
        unsigned __int64 startRCS = __rdtsc();
        cocktailSort(reverseSortedArrayCopy, comparisonsRCS, swapsRCS, n);
        unsigned __int64 endRCS = __rdtsc();
        double durationRCS = double(endRCS - startRCS) / 1000000000;

        // Создание копий массивов для каждого алгоритма сортировки
        vector<int> ArrayCopyC = Array;
        vector<int> sortedArrayCopyC = sortedArray;
        vector<int> reverseSortedArrayCopyC = reverseSortedArray;

        // Переменные для подсчета числа сравнений и пересылок в сортировке Шелла
        long long comparisonsSS = 0;
        long long swapsSS = 0;
        long long comparisonsSSS = 0;
        long long swapsSSS = 0;
        long long comparisonsRSS = 0;
        long long swapsRSS = 0;

        // Замер времени выполнения сортировки Шелла
        unsigned __int64 startSS = __rdtsc();
        shellSort(ArrayCopyC, comparisonsSS, swapsSS, n);
        unsigned __int64 endSS = __rdtsc();
        double durationSS = double(endSS - startSS) / 1000000000;

        // Замер времени выполнения сортировки Шелла на отсортированном массиве
        unsigned __int64 startSSS = __rdtsc();
        shellSort(sortedArrayCopyC, comparisonsSSS, swapsSSS, n);
        unsigned __int64 endSSS = __rdtsc();
        double durationSSS = double(endSSS - startSSS) / 1000000000;

        // Замер времени выполнения сортировки Шелла на массиве, отсортированном в обратном порядке
        unsigned __int64 startRSS = __rdtsc();
        shellSort(reverseSortedArrayCopyC, comparisonsRSS, swapsRSS, n);
        unsigned __int64 endRSS = __rdtsc();
        double durationRSS = double(endRSS - startRSS) / 1000000000;

        // Вывод результатов
        cout << "Результаты для массива длины " << n << ":" << endl;
        cout << "Шелла: Время - " << durationSS << " секунд, Сравнения - " << comparisonsSS << ", Пересылки - " << swapsSS << endl;
        cout << "Шелла (отсортированный): Время - " << durationSSS << " секунд, Сравнения - " << comparisonsSSS << ", Пересылки - " << swapsSSS << endl;
        cout << "Шелла (обратно отсортированный): Время - " << durationRSS << " секунд, Сравнения - " << comparisonsRSS << ", Пересылки - " << swapsRSS << endl;
        cout << "Шейкер: Время - " << durationCS << " секунд, Сравнения - " << comparisonsCS << ", Пересылки - " << swapsCS << endl;
        cout << "Шейкер (отсортированный): Время - " << durationSCS << " секунд, Сравнения - " << comparisonsSCS << ", Пересылки - " << swapsSCS << endl;
        cout << "Шейкер (обратно отсортированный): Время - " << durationRCS << " секунд, Сравнения - " << comparisonsRCS << ", Пересылки - " << swapsRCS << endl;
        cout << "--------------------------------------" << endl;
    }

    return 0;
}
