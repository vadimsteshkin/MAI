#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>

using namespace std;

int main() {
    double a;//������ �������
    double b;//����� �������
    int n;//����� ����������
    setlocale(LC_ALL, "RUSSIAN");
    cout << "������� ����� ��������� ����� ������:\n";
    cin >> a >> b;
    cout << "������ �������: " << a << "\n����� �������: " << b;
    while (a > b)
    {
        cout << "\n������������ ����� ���������, ������ ������ ���� �� ������ �����, ������� ������: \n";
        cin >> a >> b;
        cout << "������ �������: " << b << "\n����� �������: " << b;
    }
    cout << "\n������� ���-�� ���������� \n";
    cin >> n;
    cout << "���������� ����������: " << n;
    while (n <= 0)
    {
        cout << "\n���������� ������ ���� ����������� ������, ������� ������: \n";
        cin >> n;
        cout << "���������� ����������: " << n;
    }
    setlocale(0, "C");
    cout<<endl << (char) 218 << string(6,(char) 196) << (char) 194 << string(32, (char) 196) << (char) 194 // ������� ������� �������
        << string(32, (char) 196) << (char) 194 << string(32, (char) 196) << (char) 191 << endl;


    cout << (char) 179 << setw(6) << (char) 252 << (char) 179 << setw(32) << "X" << (char) 179 << setw(32) << "F(x)"// ��������� �������
         << (char) 179 << setw(32) << "G(x)" << (char) 179 << endl;


    long double g;//�������� G(x)
    long double f;//�������� F(�)
    long double h;//�������� ����
    long double x;
    h = (b - a) / n;
    for (int i = 0; i <= n; i++)
    {
        x = a + i * h;
        f = pow(x+1,3);
        g = (1-x*x);
        cout << (char) 195 << string(6,(char) 196) << (char) 197 << string(32, (char) 196)//string(int,string) - �������, ������� ���������� ������, ��������� �� int ���������� string
             << (char) 197 << string(32, (char) 196) << (char) 197 << string(32, (char) 196) << (char) 180<<endl;// ����������� �����

        cout << (char) 179 << setw(6) << i + 1 << (char) 179 << setw(32) << x << (char) 179 << setw(32) << f
             << (char) 179 << setw(32) << g << (char) 179 << endl;// ����� ������ ��� ������� i+1 , ������� �������� �������� ������� f � g � ����� x
    }

    cout << (char) 192 << string(6,(char) 196) << (char) 193 << string(32, (char) 196)
         << (char) 193 << string(32, (char) 196) << (char) 193 << string(32, (char) 196) << (char) 217;// ������ ������� �������
    return 0;
}