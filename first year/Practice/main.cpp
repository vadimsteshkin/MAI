//c++. В процессе функционирование АСУ ВД в файле фиксируются данные о самолетах, совершивших посадку.
// Каждая запись имеет:время посадки, марка летательного аппарата, бортовой номер, пункт отправления.
// Написать программу сортирующую записи методом индексной сортировки пузырьком в порядке возрастания времени посадки
// . Результаты написать в виде таблицы. Обеспечить входной контроль данных. Чтение происходит из текстового файла. Алгоритм должен быть параметризован.
/********************************************************************
*               Информатика и вычислительная техника                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : Practice                                           *
* File Name : Source.cpp                                            *
* Language : C++                                                    *
* Programmer(s) : М3О-109Б-22                                       *
*                 Стешкин В.А                                       *
* Modifyed By :                                                     *
* Created : 10.05.2023                                              *
* Comment(s) : Практика                                             *
*********************************************************************/
//Подключение библиотек
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
/********************************************************************
*             ГЛОБАЛЬНЫЕ КОНСТАНТЫ                                  *
*********************************************************************/
using namespace std;

//const string FILENAME = "Test.txt";//Correct test
const string FILENAME = "Test2.txt";//Correct test

//const string FILENAME = "Mist1.txt"; //"Error opening file.";
//const string FILENAME = "Mist21.txt"; //"Invalid time format.";
//const string FILENAME = "Mist22.txt"; //"Hours are not a number.";
//const string FILENAME = "Mist23.txt"; //"Invalid time (number of hours).";
//const string FILENAME = "Mist24.txt"; //"Minutes are not a number.";
//const string FILENAME = "Mist25.txt";  //"Invalid time (number of minutes).";
//const string FILENAME = "Mist3.txt"; //"File does not contain data.";
//const string FILENAME = "Mist4.txt"; //"Invalid tail number (does not start with 'B').";
//const string FILENAME = "Mist5.txt";  //"Invalid tail number (digits after 'B' should be numbers).";
//const string FILENAME = "Mist6.txt";  //"Invalid departure point (should contain only letters).";
//const string FILENAME = "Mist8.txt";  //"Less than 4 columns in the record.";
//const string FILENAME = "Mist9.txt"; //"More than 4 columns in the record."

/********************************************************************
*             ПРОТОТИПЫ ФУНКЦИЙ                                     *
*********************************************************************/
//Печать ошибок
string getErrorMessage(int errorCode);

//Проверка на корректность времени
int isValidTime(const string &time, vector<int> &errorCodes);

//Проверка на кооректность бортового номера
void check_tail_number(const char *tail, int len, vector<int> &errorCodes);

//Проверка на корректность пункта отправления
void check_departure_point(const char *point, int len, vector<int> &errorCodes);

//сравнение записей времени
bool compareFlightRecords(const vector<string> &record1, const vector<string> &record2);

//пузырьковая сортировка
void bubbleSort(vector<vector<string>> &records);

//печать ошибок
void printErrors(const vector<int> &errorCodes);

//открытие файла
bool openInputFile(ifstream &inputFile);

//закрытие файла
void closeInputFile(ifstream &inputFile);

//добавление записей в вектор
void processValidRecord(const vector<string> &record, vector<vector<string>> &flightRecords);

//проверка на количество столбцов
void processInvalidRecord(const vector<string> &record, vector<int> &errorCodes);

//чтение данных из файла
void readFlightRecords(vector<vector<string>> &flightRecords, vector<int> &errorCodes);

//Печать разделителя таблиц
void printSeparator();

// Функция печати шапки таблицы
void printHeader();

// Функция печати конца таблицы
void printFooter();

// Функция печати строки таблицы
void printRow(const vector<string> &record);

// Функция печати всех записей о посадках самолетов
void printFlightRecords(const vector<vector<string>> &flightRecords);

//главная функция
int main();

/******************************************************************
*             ОСНОВНАЯ ПРОГРАММА                                  *
*******************************************************************/



string getErrorMessage(int errorCode)
{
    switch (errorCode)
    {
        case 1:
            return "Error opening file.";
        case 21:
            return "Invalid time format.";
        case 22:
            return "Hours are not a number.";
        case 23:
            return "Invalid time (number of hours).";
        case 24:
            return "Minutes are not a number.";
        case 25:
            return "Invalid time (number of minutes).";
        case 3:
            return "File does not contain data.";
        case 4:
            return "Invalid tail number (does not start with 'B').";
        case 5:
            return "Invalid tail number (digits after 'B' should be numbers).";
        case 6:
            return "Invalid departure point (should contain only letters).";
        case 7:
            return "Incorrect number of columns in the record.";
        case 8:
            return "Less than 4 columns in the record.";
        case 9:
            return "More than 4 columns in the record.";
        default:
            return "Unknown error.";
    }
}

int isValidTime(const string &time, vector<int> &errorCodes)
{
    if (time.length() != 5)// Изменили проверку на time[1] != ':'
    {
        errorCodes.push_back(21);
    }

    if (!isdigit(time[0]))
    {
        errorCodes.push_back(22);
    }
    int hours = atoi(time.substr(0, 2).c_str());
    int minutes = atoi(time.substr(3, 2).c_str());
    if (hours < 0 || hours > 23)
    {
        errorCodes.push_back(23);
    }

    if (!isdigit(time[3]) || !isdigit(time[4]))
    {
        errorCodes.push_back(24);
    }
    if (minutes < 0 || minutes > 59)
    {
        errorCodes.push_back(25);
    }
    return errorCodes.size();
}

void check_tail_number(const char *tail, int len, vector<int> &errorCodes)
{
    if (tail[0] != 'B')
    {
        errorCodes.push_back(4);
    }
    if (!(isdigit(tail[2]) && isdigit(tail[3]) && isdigit(tail[4]) && isdigit(tail[5])))
    {
        errorCodes.push_back(5);
    }
}

void check_departure_point(const char *point, int len, vector<int> &errorCodes)
{
    int k = 0;
    while (point[k] != '\0')
    {
        if (isdigit(point[k]))
        {
            errorCodes.push_back(6);
            return;
        }
        k++;
    }
}

bool compareFlightRecords(const vector<string> &record1, const vector<string> &record2)
{
    return record1[0] < record2[0];
}

void bubbleSort(vector<vector<string>> &records)
{
    for (size_t i = 0; i < records.size() - 1; ++i)
    {
        for (size_t j = 0; j < records.size() - i - 1; ++j)
        {
            if (compareFlightRecords(records[j + 1], records[j]))
            {
                swap(records[j], records[j + 1]);
            }
        }
    }
}

void printErrors(const vector<int> &errorCodes)
{
    for (const auto &errorCode: errorCodes)
    {
        cout << getErrorMessage(errorCode) << endl;
    }
}

bool openInputFile(ifstream &inputFile)
{
    inputFile.open(FILENAME);
    return inputFile.is_open();
}

void closeInputFile(ifstream &inputFile)
{
    inputFile.close();
}


void processValidRecord(const vector<string> &record, vector<vector<string>> &flightRecords) {
    flightRecords.push_back(record);
}

void processInvalidRecord(const vector<string> &record, vector<int> &errorCodes)
{
    if (record.size() < 4)
    {
        errorCodes.push_back(8); // Ошибка: меньше 4 столбцов в записи
    } else if (record.size() > 4)
    {
        errorCodes.push_back(9); // Ошибка: больше 4 столбцов в записи
    }
}

void readFlightRecords(vector<vector<string>> &flightRecords, vector<int> &errorCodes)
{
    ifstream inputFile;
    if (!openInputFile(inputFile))
    {
        errorCodes.push_back(1); // Ошибка: не удалось открыть файл
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        stringstream iss(line);
        vector<string> record;
        string field;

        while (iss >> field)
        {
            record.push_back(field);
        }

        if (record.size() == 4)
        {
            vector<int> timeErrorCodes;
            int timeErrors = isValidTime(record[0], timeErrorCodes);
            if (timeErrors > 0)
            {
                errorCodes.insert(errorCodes.end(), timeErrorCodes.begin(), timeErrorCodes.end());
            } else
            {
                check_tail_number(record[2].data(), record[2].size(), errorCodes);
                check_departure_point(record[3].data(), record[3].size(), errorCodes);
                processValidRecord(record, flightRecords);
            }
        }
        else
        {
            processInvalidRecord(record, errorCodes);
        }
    }

    closeInputFile(inputFile);

    if (flightRecords.empty())
    {
        errorCodes.push_back(3); // Ошибка: файл не содержит корректных записей
    }
}


void printSeparator()
{
    cout << char(195);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++) cout << char(196);
        if (i != 3) cout << char(197);
    }
    cout << char(180) << endl;
}

// Функция печати шапки таблицы
void printHeader()
{
    cout << char(218);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++) cout << char(196);
        if (i != 3) cout << char(194);
    }
    cout << char(191) << endl;

    cout << char(179) << setw(13) << "Landing Time"
         << char(179) << setw(13) << "Mark LA"
         << char(179) << setw(13) << "Board Number"
         << char(179) << setw(13) << "Point of Dep."
         << char(179) << endl;

    printSeparator();
}

// Функция печати конца таблицы
void printFooter()
{
    cout << char(192);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++) cout << char(196);
        if (i != 3) cout << char(193);
    }
    cout << char(217) << endl;
}

// Функция печати строки таблицы
void printRow(const vector<string> &record)
{

    cout << char(179);
    for (const auto &field: record) {
        cout << setw(13) << left << field << char(179);
    }
    cout << endl;
    printSeparator();
}

// Функция печати всех записей о посадках самолетов
void printFlightRecords(const vector<vector<string>> &flightRecords)
{
    printHeader();
    for (const auto &record: flightRecords)
    {
        printRow(record);

    }
    printFooter();
}

int main()
{
    vector<vector<string>> flightRecords;
    vector<int> errorCodes;
    readFlightRecords(flightRecords, errorCodes);

    if (!errorCodes.empty())
    {
        printErrors(errorCodes);
    }
    else
    {
        cout << "=== Flight Records before Sorting ===" << endl;
        printFlightRecords(flightRecords);

        bubbleSort(flightRecords);

        cout << "\n=== Flight Records after Sorting ===" << endl;
        printFlightRecords(flightRecords);
    }

    return 0;
}