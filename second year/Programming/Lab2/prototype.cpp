#include<iostream>
#include<climits>
#include <chrono>
using namespace std;
/********************************************************************
*             ПРОТОТИПЫ ФУНКЦИЙ                                                                          *
*********************************************************************/
//Алгоритм поиска BLS
int Better_Linear_Search(int* data, int size, int x);
//Алгоритм поиска SLS
int Sentinel_Linear_Search(int* data, int size, int x);
//Алгоритм поиска OLS
int Ordered_Linear_Search(int* data, int size, int x);
//Алгоритм поиска BS
int Binary_Search(int* data, int size, int x);
/******************************************************************
*             ОСНОВНАЯ ПРОГРАММА                                                                    *
*******************************************************************/
//Начало main
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int size = 20000;//Размер последовательности
	int x_rand = 8669;//Ключ для поиска в случайной последовательности
	int x_fix = 19998;//Ключ для поиска в возрастающей последовательности
	int data1[20000] = {};//Массив последовательности
	for (int i = 0; i < size; i++)//Создание последовательности
	{
		data1[i] = rand();
		if (i == 7) cout << "Эл-т в начале массива: " << data1[i] << endl;
		if (i == size / 2) cout << "Эл-т в середине массива: " << data1[i] << endl;
		if (i == size -3) cout << "Эл-т в конце массива: " << data1[i] << endl;
		//cout << data1[i] << " ";
	}
	cout << "Выполнение BLS" << endl;
	auto begin1 = std::chrono::steady_clock::now();//Начало отсчёта времени для BLS
	Better_Linear_Search(data1, size, x_rand);//Запуск BLS
	auto end1 = std::chrono::steady_clock::now();//Конец отсчёта времени для BLS
	auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);//Подсчёт времени для BLS
	std::cout << "Время работы алгоритма поиска BLS: " << elapsed_ms1.count() << " (мкС)" << std::endl;//Вывод времени для BLS
	cout << "Выполнение SLS" << endl;
	auto begin2 = std::chrono::steady_clock::now();//Начало отсчёта времени для SLS
	Sentinel_Linear_Search(data1, size, x_rand);//Запуск SLS
	auto end2 = std::chrono::steady_clock::now();//Конец отсчёта времени для SLS
	auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);//Подсчёт времени для SLS
	std::cout << "Время работы алгоритма поиска SLS: " << elapsed_ms2.count() << " (мкС)" << std::endl;//Вывод времени для SLS
	for (int i = 0; i < size; i++)
	{
		data1[i] = i;
		//cout << data1[i] << " ";
	}
	cout << "Выполнение OLS" << endl;
	auto begin3 = std::chrono::steady_clock::now();//Начало отсчёта времени для OLS
	Ordered_Linear_Search(data1, size, x_fix);//Запуск OLS
	auto end3 = std::chrono::steady_clock::now();//Конец отсчёта времени для OLS
	auto elapsed_ms3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3);//Подсчёт времени для OLS
	std::cout << "Время работы алгоритма поиска OLS: " << elapsed_ms3.count() << " (мкС)" << std::endl;//Вывод времени для OLS
	cout << "Выполнение BS" << endl;
	auto begin4 = std::chrono::steady_clock::now();//Начало отсчёта времени для BS
	Binary_Search(data1, size, x_fix);//Запуск BS
	auto end4 = std::chrono::steady_clock::now();//Конец отсчёта времени для BS
	auto elapsed_ms4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4);//Подсчёт времени для BS
	std::cout << "Время работы алгоритма поиска BS: " << elapsed_ms4.count() << " (мкС)" << std::endl;//Вывод времени для BS
	return 0;
}//Конец main
//Алгоритм поиска BLS
int Better_Linear_Search(int* data, int size, int x)
{
	int cnt_i = 0;//Кол-во сравнений в цикле
	int cnt = 0;//Кол-во сравнений с ключом
	for (int i = 0; i < size; i++) //Цикл алгоритма поиска
	{
		cnt_i++;
		if (data[i] == x) //Сравнение с ключом
		{
			cout << "Индекс равен: " << i << endl;
			cnt++;
			cout << "Кол-во сравнений с ключом: " << cnt << endl;
			cout << "Кол-во сравнений в цикле: " << cnt_i << endl;
			return i;
		}
		else
		{
			cnt++;
		}
	}//Конец данного цикла
	cout << "Not_Found" << endl;
	cout << "Кол-во сравнений с ключом: " << cnt << endl;
	cout << "Кол-во сравнений в цикле: " << cnt_i << endl;
	return 1;
}//Конец алгоритма поиска BLS
//Алгоритм поиска SLS
int Sentinel_Linear_Search(int* data, int size, int x)
{
	int last = data[size - 1];//Последнее значение
	data[size - 1] = x;//Значение последнего члена массива
	int i = 0;//Индекс
	int cnt = 0;//Кол-во сравнений
	while (data[i] != x)//Сравнение элемента массива с ключом
	{
		i++;
		cnt++;
	}
	if (data[size - 1] == x)
	{
		cnt++;
	}
	data[size - 1] = last;
	if ((i < size - 1) or (data[size - 1] == x))//Вывод индекса
	{
		cout << "Индекс равен: " << i << endl;
	}
	else
	{
		cout << "Not_Found" << endl;
	}
	cout << "Кол-во сравнений: " << cnt << endl;
	return 0;
}//Конец алгоритма поиска SLS
//Алгоритм поиска OLS
int Ordered_Linear_Search(int* data, int size, int x)
{
	int last = data[size - 1];//Последнее значение
	data[size - 1] = LLONG_MAX;
	int i = 0;//Индекс
	while (x > data[i])//Сравнение элемента массива с ключом 
	{
		i++;
	}
	data[size - 1] = last;//Концу массива присваиваем обратно последний элемент
	if (x == data[i])//Вывод индекса
	{
		cout << "Индекс равен: " << i << endl;
		return i;
	}
	if (x == data[size - 1])
	{
		cout << "Индекс равен: " << size - 1 << endl;
		return size - 1;
	}
	cout << "Not_Found" << endl;
	return 2;
}//Конец алгоритма поиска OLS
//Алгоритм поиска BS
int Binary_Search(int* data, int size, int x)
{
	int p = 1;//Установка переменных p и r
	int r = size;
	while (p <= r)//Поиск элемента
	{
		int q = (p + r) / 2;
		if (data[q] == x)//Вывод индекса
		{
			cout << "Индекс равен: " << q << endl;
			return q;
		}
		else if (data[q] > x)
		{
			r = q - 1;
		}
		else
		{
			p = q + 1;

		}
	}
	cout << "Not_Found" << endl;
	return 3;
}//Конец алгоритма поиска BS
