#include "iostream"
#include <cmath>


using namespace std;
 
int main()
{
    int s;
    setlocale(LC_ALL, "rus");
    cout << "Выбирете тип вводимого элемента: \n1 - тип int; 2 - тип char" << endl;
    cin >> s;
    int a[10], x, k;
    cout << "Введите кол-во элементов типа int: " << endl;
    cin >> x;
        cout << "Введите элементы: " << endl;
        for (int i=0; i<x; i++)
        cin >> a[i];
        cout << endl;
        k=powf(2,x);
        for (int i=0; i<k; i++) 
            {
                cout << "{";
                for (int j=0; j<x; j++) 
                    if (i & (1<<j))
                     cout << a[j] << " "; 
                     cout << "}" << endl;
            }
    return 0;
}