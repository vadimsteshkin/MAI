#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;

typedef int (*DataGeneratorIntFull)(const char*, int, int, int, int*);
typedef int (*DataGeneratorIntPartly)(const char*, int, int, int, int, int*);
typedef float (*DataGeneratorFloatFull)(const char*, int, int, int, float*);
typedef float (*DataGeneratorFloatPartly)(const char*, int, int, int, int, float*);


const char* FNAME1[] = { "files\\sluch.txt", "files\\grow.txt", "files\\decr.txt" };
const char* FNAME2[] = { "files\\pila.txt", "files\\sin.txt", "files\\stup.txt" };
const char* FNAME3[] = { "files\\sluchfloat.txt", "files\\growfloat.txt", "files\\decrfloat.txt" };
const char* FNAME4[] = { "files\\pilafloat.txt", "files\\sinfloat.txt", "files\\stupfloat.txt" };



/*Генерирует случайную последовательность целых чисел в диапазоне от min до max. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
int Rand_Num(const char* FNAME, int n, int min, int max, int* data1);

/*Генерирует случайную последовательность чисел с плавающей точкой в диапазоне от min до max. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
float Rand_Numfloat(const char* FNAME, int n, int min, int max, float* data3);

/*Генерирует упорядоченную по возрастанию последовательность целых чисел в диапазоне от min до max. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
int Grow_Num(const char* FNAME, int n, int min, int max, int* data1);

/*Генерирует упорядоченную по возрастанию последовательность чисел с плавающей точкой в диапазоне от min до max. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
float Grow_Numfloat(const char* FNAME, int n, int min, int max, float* data3);

/*Генерирует упорядоченную по убыванию последовательность целых чисел в диапазоне от min до max.
 Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
int Decr_Num(const char* FNAME, int n, int min, int max, int* data1);

/*Генерирует упорядоченную по убыванию последовательность чисел с плавающей точкой в диапазоне от min до max.
 Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
float Decr_Numfloat(const char* FNAME, int n, int min, int max, float* data3);

/*Генерирует "пилообразную" последовательность целых чисел, 
в которой значения повторяются в интервалах заданной длины (interval) в диапазоне от min до max. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
int Saw_Num(const char* FNAME, int n, int min, int max, int interval, int* data2);

/*Генерирует "пилообразную" последовательность чисел с плавающей точкой, 
в которой значения повторяются в интервалах заданной длины (interval) в диапазоне от min до max. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
float Saw_Numfloat(const char* FNAME, int n, int min, int max, int interval, float* data4);

/*Генерирует "синусоидальную" последовательность целых чисел, 
в которой значения изменяются по синусоидальному закону в интервале от min до max с заданным интервалом interval. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
int Sin_Num(const char* FNAME, int n, int min, int max, int interval, int* data2);

/*Генерирует "синусоидальную" последовательность чисел с плавающей точкой, 
в которой значения изменяются по синусоидальному закону в интервале от min до max с заданным интервалом interval. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
float Sin_Numfloat(const char* FNAME, int n, int min, int max, int interval, float* data4);

/*Генерирует "ступенчатую" последовательность целых чисел, 
в которой значения изменяются по синусоидальному закону в интервале от min до max с заданным интервалом interval. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
int Stair_Num(const char* FNAME, int n, int min, int max, int interval, int* data2);

/*Генерирует "ступенчатую" последовательность чисел c плавающей точкой, 
в которой значения изменяются по синусоидальному закону в интервале от min до max с заданным интервалом interval. 
Записывает эту последовательность в файл с именем, переданным в качестве аргумента FNAME.*/
float Stair_Numfloat(const char* FNAME, int n, int min, int max, int interval, float* data4);


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n = 200;
	int min = 10;
	int max = 1000;
	int interval = 20;
	DataGeneratorIntFull dataGeneratorsIntFull[] = { Rand_Num, Grow_Num, Decr_Num };
	DataGeneratorIntPartly dataGeneratorsIntPartly[] = { Saw_Num, Sin_Num, Stair_Num };
	DataGeneratorFloatFull dataGeneratorsFloatFull[] = { Rand_Numfloat, Grow_Numfloat, Decr_Numfloat };
	DataGeneratorFloatPartly dataGeneratorsFloatPartly[] = { Saw_Numfloat, Sin_Numfloat, Stair_Numfloat };
	cout << "Целые числа" << endl;
	for (int i = 0; i < 3; i++)
	{
		int data1[1000];
		dataGeneratorsIntFull[i](FNAME1[i], n, min, max, data1);
	}
	for (int i = 0; i < 3; i++)
	{
		int data2[1000];
		dataGeneratorsIntPartly[i](FNAME2[i], n, min, max, interval, data2);
	}
	cout << "Числа с плавающей запятой" << endl;
	for (int i = 0; i < 3; i++)
	{
		float data3[1000];
		dataGeneratorsFloatFull[i](FNAME3[i], n, min, max, data3);
	}
	for (int i = 0; i < 3; i++)
	{
		float data4[1000];
		dataGeneratorsFloatPartly[i](FNAME4[i], n, min, max, interval, data4);
	}
	return 0;
}

int Rand_Num(const char* FNAME, int n, int min, int max, int* data1)
{
	ofstream fout(FNAME);
	srand(time(NULL));
	cout << "Случайная последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data1[i] = min + rand() % (max - min + 1);
		fout << data1[i] << endl;
		cout << data1[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
int Grow_Num(const char* FNAME, int n, int min, int max, int* data1)
{
	ofstream fout(FNAME);
	cout << "Возрастающая последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data1[i] = ((double(max - min)) / n) * i + min;
		fout << data1[i] << endl;
		cout << data1[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
int Decr_Num(const char* FNAME, int n, int min, int max, int* data1)
{
	ofstream fout(FNAME);
	cout << "Убывающая последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data1[i] = max - ((double(max - min)) / n) * i;
		fout << data1[i] << endl;
		cout << data1[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
int Saw_Num(const char* FNAME, int n, int min, int max, int interval, int* data2)
{
	ofstream fout(FNAME);
	cout << "Пилообразная последовательность" << endl;
	int i = 0;
	int j = 0;
	while (i < n)
	{
		data2[i] = (double(max - min)) / interval * j + min;
		fout << data2[i] << endl;
		cout << data2[i] << " ";
		if (j < interval)
		{
			j++;
		}
		else
		{
			j = 0;
		}
		i++;
	}
	cout << endl;
	fout.close();
	return 0;
}
int Sin_Num(const char* FNAME, int n, int min, int max, int interval, int* data2)
{
	ofstream fout(FNAME);
	cout << "Синусоидная последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data2[i] = min + ((max - min) / 2) * (1 + sin(i * 2 * M_PI / interval));
		fout << data2[i] << endl;
		cout << data2[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
int Stair_Num(const char* FNAME, int n, int min, int max, int interval, int* data2)
{
	ofstream fout(FNAME);
	cout << "Ступенчатая последовательность" << endl;
	int i = 0;
	int j = 0;
	int k = min;
	while (i < n)
	{
		data2[i] = k;
		fout << data2[i] << endl;
		cout << data2[i] << " ";
		if (j < interval)
		{
			j++;
		}
		else
		{
			j = 0;
			k = k + ((max - min)) / (n / ((interval)));
		}
		i++;
	}
	cout << endl;
	fout.close();
	return 0;
}
float Rand_Numfloat(const char* FNAME, int n, int min, int max, float* data3)
{
	ofstream fout(FNAME);
	cout << "Случайная последовательность" << endl;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		data3[i] = min + rand() / float(RAND_MAX)*(max-min+1);
		fout << data3[i] << endl;
		cout << data3[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
float Grow_Numfloat(const char* FNAME, int n, int min, int max, float* data3)
{
	ofstream fout(FNAME);
	cout << "Возрастающая последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data3[i] = (double(max - min)) / n * i + min;
		fout << data3[i] << endl;
		cout << data3[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
float Decr_Numfloat(const char* FNAME, int n, int min, int max, float* data3)
{
	ofstream fout(FNAME);
	cout << "Убывающая последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data3[i] = max-(double(max - min)) / n * i ;
		fout << data3[i] << endl;
		cout << data3[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
float Saw_Numfloat(const char* FNAME, int n, int min, int max, int interval, float* data4)
{
	ofstream fout(FNAME);
	cout << "Пилообразная последовательность" << endl;
	int i = 0;
	int j = 0;
	while (i < n)
	{
		data4[i] = (double(max - min)) / interval * j + min;
		fout << data4[i] << endl;
		cout << data4[i] << " ";
		if (j < interval)
		{
			j++;
		}
		else
		{
			j = 0;
		}
		i++;
	}
	cout << endl;
	fout.close();
	return 0;
}
float Sin_Numfloat(const char* FNAME, int n, int min, int max, int interval, float* data4)
{
	ofstream fout(FNAME);
	cout << "Синусоидная последовательность" << endl;
	for (int i = 0; i < n; i++)
	{
		data4[i] =min + ((max-min)/2) * (1 + sin(i * 2 * M_PI / interval));
		fout << data4[i] << endl;
		cout << data4[i] << " ";
	}
	cout << endl;
	fout.close();
	return 0;
}
float Stair_Numfloat(const char* FNAME, int n, int min, int max, int interval, float* data4)
{
	ofstream fout(FNAME);
	cout << "Ступечатая последовательность" << endl;
	int i = 0;
	int j = 0;
	float k = min;
	while (i < n)
	{
		data4[i] = k;
		fout << data4[i] << endl;
		cout << data4[i] << " ";
		if (j < interval)
		{
			j++;
		}
		else
		{
			j = 0;
			k = k + ((max - min)) / (n / (float(interval)));
		}
		i++;
	}
	cout << endl;
	fout.close();
	return 0;
}