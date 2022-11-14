
#include <iostream>
#include <cmath>

using namespace std;


int main() {
    setlocale(LC_ALL, "Rus");?
    int n; //количество просуммированных элементов
    double e, sum, Tsum, Diff, Znak; //Точность, сумма, точная сумма, модуль разницы между точной суммой и суммой, изменение знака
    cout << "Введите эпсилон \n";
    cin >> e;
    while (e <= 0) {
        cout << "Эпсилон должен быть больше 0 \n";
        cin >> e;
    }
    n = 0;
    Znak = -1;
    sum = 0;
    Tsum = 3.14159 / 4;
    Diff = abs(Tsum - sum);
    while (Diff > e) {
        n++;
        Znak *= -1;
        sum += Znak * 1 / (2 * n - 1);
        Diff = abs(Tsum - sum);
    }
    cout << "Разность: " << Diff << "\nСчетчик: " << n << "\nСумма: " << sum;
    return 0;
}