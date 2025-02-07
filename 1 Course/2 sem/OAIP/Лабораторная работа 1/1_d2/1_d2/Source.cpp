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
        cout << "Трамвай номер " << i + 1 << ":" << endl;
        cout << "Название пункта назначения: ";   cin >> users[i].destination;
        cout << "Номер поезда: ";   cin >> users[i].number;
        cout << "Время отправления: ";   cin >> users[i].time;
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
        cout << "\nТрамвай номер " << i + 1 << ":" << endl;
        cout << "\nНазвание пункта назначения: "; cout << users[i].destination;
        cout << "\nНомер поезда: ";   cout << users[i].number;
        cout << "\nВремя отправления: ";   cout << users[i].time;
        cout << endl;
    }
}

void comparison(const Train users[]) {
    bool f = false;
    cout << "\n\nВведите время: ";
    char doptime[6]; cin >> doptime;
    cout << endl;
    for (int i = 0; i < SIZE; i++)
        if (strcmp(users[i].time, doptime) > 0) {
            bool f = true;
            cout << "\nТрамвай номер " << i + 1 << " отправляется позже указанного времени:" << endl;
            cout << "\nНазвание пункта назначения: "; cout << users[i].destination;
            cout << "\nНомер поезда: ";   cout << users[i].number;
            cout << "\nВремя отправления: ";   cout << users[i].time;
            cout << endl;
        }
    if (f == false) {
        cout << "\nТрамваев, отправляющихся позже указанного времени нет";
    }
}