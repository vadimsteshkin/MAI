#include "iostream"
#include <cmath>


using namespace std;
 
int main()
{
    int s;
    setlocale(LC_ALL, "rus");
    cout << "�������� ��� ��������� ��������: \n1 - ��� int; 2 - ��� char" << endl;
    cin >> s;
    int a[10], x, k;
    cout << "������� ���-�� ��������� ���� int: " << endl;
    cin >> x;
        cout << "������� ��������: " << endl;
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