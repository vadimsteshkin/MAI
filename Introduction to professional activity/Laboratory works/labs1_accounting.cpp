#include <iostream>


using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    cout<<"����� ������ ������ �� ������ ����� ������� 0, ���� ������ ������� ������� ��� ������������� �������, ������� 1 \n";
    int type_book;
    int id=0;
    string author;
    string name;
    string genre;
    int year;

    cin>>type_book;
    if (type_book==0){
        cout<<"������� ��� ������, �������� �����, ����";
        cin>>author>>name>>genre;

        year=2022;
    }else
    {
        cout<<"������� ��� ������, �������� �����, ����, ��� �������";
        cin>>author>>name>>genre>>year;
    }
    cout<<"���� ������������ ���������� ��� ��������� �������: \n";
    cout<<"����� '��������': ���� � ������-30% �����-0 ��� �����-1500 \n";
    cout<<"����� '������ �������':  ���� � ������-50% �����-10000 ��� �����-3000 \n";
    cout<<"����� '�������� ������':  ���� � ������-55% �����- 100000��� �����-20000 \n";
    cout<<"����� '������ ����':  ���� � ������-60% �����-10000000 ��� �����-60000 \n";
}