#include <iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
using namespace std;
#define SIZE 3

struct Train {
    char destination[5];
    unsigned int number;
    char time[6];
};

void Copy(Train& pest, Train bust);
void output(const Train users[]);
void comparison(const Train users[]);

int main()
{
    setlocale(LC_CTYPE, "rus");
    Train users[SIZE];
    for (int i = 0; i < SIZE; i++) {
        cout << "������� ����� " << i + 1 << ":" << endl;
        cout << "�������� ������ ����������: ";   cin >> users[i].destination;
        cout << "����� ������: ";   cin >> users[i].number;
        cout << "����� �����������: ";   cin >> users[i].time;
    }

    Train buf;
    for (int i = 0; i < SIZE - 1; i++)
        for (int k = 0; k < SIZE - 1; k++)
            if (strcmp(users[k].destination, users[k + 1].destination) > 0) {
                Copy(buf, users[k]);
                Copy(users[k], users[k + 1]);
                Copy(users[k + 1], buf);
            }
    output(users);
    comparison(users);
}

void Copy(Train& pest, Train bust) {
    strcpy_s(pest.destination, bust.destination);
    strcpy_s(pest.time, bust.time);
    pest.number = bust.number;
}

void output(const Train users[]) {
    for (int i = 0; i < SIZE; i++) {
        cout << "\n������� ����� " << i + 1 << ":" << endl;
        cout << "\n�������� ������ ����������: "; cout << users[i].destination;
        cout << "\n����� ������: ";   cout << users[i].number;
        cout << "\n����� �����������: ";   cout << users[i].time;
        cout << endl;
    }
}

void comparison(const Train users[]) {
    bool f = false;
    cout << "\n\n������� �����: ";
    char doptime[6]; cin >> doptime;
    cout << endl;
    for (int i = 0; i < SIZE; i++)
        if (strcmp(users[i].time, doptime) > 0) {
            bool f = true;
            cout << "\n������� ����� " << i + 1 << " ������������ ����� ���������� �������:" << endl;
            cout << "\n�������� ������ ����������: "; cout << users[i].destination;
            cout << "\n����� ������: ";   cout << users[i].number;
            cout << "\n����� �����������: ";   cout << users[i].time;
            cout << endl;
        }
    if (f == false) {
        cout << "\n��������, �������������� ����� ���������� ������� ���";
    }
}