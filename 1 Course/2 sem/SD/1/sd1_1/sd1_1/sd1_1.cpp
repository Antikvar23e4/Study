
//1.�������� ���������, �������, � ����������� �� ������ ������������,
//� ������� ������ �������� ��������� PC(���, ����, ������ �����),
//� �������������� ������������.

#include <iostream>
using namespace std;

enum StatePC {
   OFF,
   ON,
   SLEEP
};

int main()
{
    setlocale(LC_ALL, "rus");
    int choice;
    cout << "������� ��������� PC (1 - ��������, 2 - �������, 3 - ������ ����� ): " << endl;
    cin >> choice;
    StatePC num = OFF;

    switch (choice) {
    case 1:
        num = OFF;
        cout << "��� PC ���������. "<< endl;
        break;
    case 2:
        num = ON;
        cout << "��� PC �������. " << endl;
        break;
    case 3:
        num = SLEEP;
        cout << "��� PC ����. " << endl;
        break;
    }
}