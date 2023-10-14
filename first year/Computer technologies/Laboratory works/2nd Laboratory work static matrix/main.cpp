#include <iostream>
#include <fstream>

const int N_MAX = 15; // Максимальный размер матрицы
const int M_MAX = 15; // Максимальный размер матрицы

// Чтение матрицы из файла
int InputData(const char* FNAME, double Matr[N_MAX][M_MAX], int& rows, int& columns) {
    std::ifstream file(FNAME);
    if (!file) {
        return 1; // Файл не найден
    }
    file >> rows >> columns;
    if (file.fail()) {
        file.close();
        return 3; // Размер не число
    }
    if ((rows > N_MAX) or (columns > M_MAX)) {
        file.close();
        return 5; // Размер больше заданного максимума
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            file >> Matr[i][j];
            if (file.fail()) {
                file.close();
                return 6; // В матрице есть символ, отличный от числа
            }
            if ((file.eof()) and (i < rows - 1 or j < columns - 1))
            {
                file.close();
                return 7;
            }
        }
    }
    if (!(file.eof()))
    {
        file.close();
        return 8; // Элементов больше, чем заданный размер
    }
    file.close();
    return 0;
}

// Печать ошибок
void PrintErrorMessage(int errorCode) {
    switch (errorCode) {
    case 1:
        std::cout << "Файл не найден" << std::endl;
        break;
    case 3:
        std::cout << "Размер не число" << std::endl;
        break;
    case 5:
        std::cout << "Размер больше заданного максимума" << std::endl;
        break;
    case 6:
        std::cout << "В матрице есть символ, отличный от числа" << std::endl;
        break;
    case 7:
        std::cout << "Элементов меньше, чем заданный размер";
        break;
    case 8:
        std::cout << "Элементов больше, чем заданный размер" << std::endl;
        break;
    default:
        std::cout << "Неизвестная ошибка" << std::endl;
        break;
    }
}

// Печать матрицы
void PrintMatrix(double Matr[N_MAX][M_MAX], int rows, int columns) {
    std::cout << rows << " * " << columns << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << " " << Matr[i][j];
        }
        std::cout << std::endl;
    }
}

// Нахождение суммы элементов строки
double GetRowSum(double Matr[N_MAX][M_MAX], int row, int columns) {
    double sum = 0;
    for (int j = 0; j < columns; j++) {
        sum += Matr[row][j];
    }
    return sum;
}

// Нахождение индекса строки с минимальной суммой элементов
int FindMinSumRow(double Matr[N_MAX][M_MAX], int rows, int columns) {
    int minRow = 0;
    double minSum = GetRowSum(Matr, 0, columns);
    for (int i = 1; i < rows; i++) {
        double sum = GetRowSum(Matr, rows, columns);
        if (sum < minSum) {
            minSum = sum;
            minRow = i;
        }
    }
    return minRow;
}

// Нахождение индекса строки с максимальной суммой элементов
int FindMaxSumRow(double Matr[N_MAX][M_MAX], int rows, int columns) {
    int maxRow = 0;
    double maxSum = GetRowSum(Matr, 0, columns);
    for (int i = 1; i < rows; i++) {
        double sum = GetRowSum(Matr, i, columns);
        if (sum > maxSum) {
            maxSum = sum;
            maxRow = i;
        }
    }
    return maxRow;
}

// Обмен строк
void SwapRows(double Matr[N_MAX][M_MAX], int row1, int row2, int columns) {
    for (int j = 0; j < columns; j++) {
        double temp = Matr[row1][j];
        Matr[row1][j] = Matr[row2][j];
        Matr[row2][j] = temp;
    }
}

int main() {
    const char* FNAMEA = "testa.txt"; // Матрица A
    const char* FNAMEB = "testb.txt"; // Матрица B
    setlocale(LC_ALL, "Russian");
    int columnsA = 0;
    int rowsA = 0;// Размер матрицы A
    double MatrA[N_MAX][M_MAX] = { 0 }; // Матрица A

    int columnsB = 0;
    int rowsB = 0; // Размер матрицы B
    double MatrB[N_MAX][M_MAX] = { 0 }; // Матрица B

    int errorCodeA = InputData(FNAMEA, MatrA, rowsA, columnsA);
    if (errorCodeA != 0) {
        PrintErrorMessage(errorCodeA);
        return 0;
    }

    std::cout << "Матрица A:" << std::endl;
    PrintMatrix(MatrA, rowsA, columnsA);

    int minSumRowA = FindMinSumRow(MatrA, rowsA, columnsA);
    int maxSumRowA = FindMaxSumRow(MatrA, rowsA, columnsA);

    SwapRows(MatrA, minSumRowA, maxSumRowA, columnsA);

    std::cout << "Матрица A после обмена строк:" << std::endl;
    PrintMatrix(MatrA, rowsA, columnsA);

    int errorCodeB = InputData(FNAMEB, MatrB, rowsB, columnsB);
    if (errorCodeB != 0) {
        PrintErrorMessage(errorCodeB);
        return 0;
    }

    std::cout << "Матрица B:" << std::endl;
    PrintMatrix(MatrB, rowsB, columnsB);

    int minSumRowB = FindMinSumRow(MatrB, rowsB, columnsB);
    int maxSumRowB = FindMaxSumRow(MatrB, rowsB, columnsB);

    SwapRows(MatrB, minSumRowB, maxSumRowB, columnsB);

    std::cout << "Матрица B после обмена строк:" << std::endl;
    PrintMatrix(MatrB, rowsB, columnsB);

    return 0;
}