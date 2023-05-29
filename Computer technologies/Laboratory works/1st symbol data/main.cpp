
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    char surname[20];//искомая фамилия
    char full_name[100];//ФИО
    char Str_All_full_name[1000];//Массив найденных однофамильцев
    int bn = 0;//начало слова
    int en = 0;//конец слова
    int ind = 0;//вспомогательный индекс для работы с однофамильцами
    ifstream input("test3.txt");//открытие файла
    input.getline(surname, 256);//считываем нужную фамилию
    if (!input.is_open())
    {
        cout << "Файла не существует\n"; // если не открылся
    }
    else if (input.peek() == EOF)
    {
        cout << "Файл пуст\n";
    }
    while (input.getline(full_name, 100))
    {
        cout << full_name << endl;//эхо-вывод
    }
    input.clear();//очистка потокаа
    int len = strlen(surname) + 1;
    input.seekg(len, ios_base::beg);
    while (input.getline(full_name, 100))
    {
        // 1. Печать фамилии и инициалов
        bool is_surname = true;
        int i = 0;
        while (full_name[i] != '\0') //проход до конца строки
        {
            while ((full_name[i] == ' ') && (full_name[i] != '\0'))
            {
                i++;
            }
            bn = i;//начало слова
            while ((full_name[i] != ' ') && (full_name[i] != '\0'))
            {
                i++;
            }
            en = i;//конец слова
            int k = bn;
            while (k < en)
            {
                if (bn == 0)//проверка, является ли слово фамилией
                {
                    if (is_surname and (surname[k] != full_name[k]))//проверка на совпадение слов
                    {
                        is_surname = false;//если хотя бы одна буква не совпадает, то флаг в false
                    }
                    cout << full_name[k];
                    k++;
                }
                else
                {
                    cout << full_name[bn] << ".";
                    k = en;
                }
            }
            cout << ' ';
        }
        if (is_surname)// если слова совпали, то записываем слово в массив
        {
            int cnt = 0;
            while (full_name[cnt] != '\0')
            {
                Str_All_full_name[ind] = full_name[cnt];
                cnt++;
                ind++;
            }
            Str_All_full_name[ind] = '\n';
            ind++;
        }
        cout << endl;
    }
    if (ind == 0)
    {
        cout << "Нет такой фамилии";
    }
    else
    {
        Str_All_full_name[ind] = '\0';
        cout << Str_All_full_name;// вывод массива совпавших слов
    }
    system("pause");
    input.close();//закрытие файла
    return 0;
}
