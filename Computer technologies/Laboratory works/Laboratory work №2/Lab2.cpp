#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>

using namespace std;

int main() {
    double a;//начало отрезка
    double b;//конец отрезка
    int n;//число интервалов
    setlocale(LC_ALL, "RUSSIAN");
    cout << "Введите концы интервала через пробел:\n";
    cin >> a >> b;
    cout << "Начало отрезка: " << a << "\nКонец отрезка: " << b;
    while (a > b)
    {
        cout << "\nНекорректные концы интервала, начало должно быть не больше конца, введите заново: \n";
        cin >> a >> b;
        cout << "Начало отрезка: " << b << "\nКонец отрезка: " << b;
    }
    cout << "\nВведите кол-во интервалов \n";
    cin >> n;
    cout << "Количество интервалов: " << n;
    while (n <= 0)
    {
        cout << "\nКоличество должно быть натуральным числом, введите заново: \n";
        cin >> n;
        cout << "Количество интервалов: " << n;
    }
    setlocale(0, "C");
    cout<<endl << (char) 218 << string(6,(char) 196) << (char) 194 << string(32, (char) 196) << (char) 194 // верхняя граница таблицы
        << string(32, (char) 196) << (char) 194 << string(32, (char) 196) << (char) 191 << endl;


    cout << (char) 179 << setw(6) << (char) 252 << (char) 179 << setw(32) << "X" << (char) 179 << setw(32) << "F(x)"// заголовок таблицы
         << (char) 179 << setw(32) << "G(x)" << (char) 179 << endl;


    long double g;//значение G(x)
    long double f;//значение F(х)
    long double h;//Величина шага
    long double x;
    h = (b - a) / n;
    for (int i = 0; i <= n; i++)
    {
        x = a + i * h;
        f = pow(x+1,3);
        g = (1-x*x);
        cout << (char) 195 << string(6,(char) 196) << (char) 197 << string(32, (char) 196)//string(int,string) - функция, которая возвращает строку, состоящую из int повторений string
             << (char) 197 << string(32, (char) 196) << (char) 197 << string(32, (char) 196) << (char) 180<<endl;// разделитель строк

        cout << (char) 179 << setw(6) << i + 1 << (char) 179 << setw(32) << x << (char) 179 << setw(32) << f
             << (char) 179 << setw(32) << g << (char) 179 << endl;// вывод строки под номером i+1 , которая содержит значения функций f и g в точке x
    }

    cout << (char) 192 << string(6,(char) 196) << (char) 193 << string(32, (char) 196)
         << (char) 193 << string(32, (char) 196) << (char) 193 << string(32, (char) 196) << (char) 217;// нижняя граница таблицы
    return 0;
}