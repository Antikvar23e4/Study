
//1.Написать программу, которая, в зависимости от выбора пользователя,
//в консоли должна выводить состояния PC(вкл, выкл, спящий режим),
//с использованием перечислений.

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
    cout << "Введите состояние PC (1 - выключен, 2 - включен, 3 - спящий режим ): " << endl;
    cin >> choice;
    StatePC num = OFF;

    switch (choice) {
    case 1:
        num = OFF;
        cout << "Ваш PC неактивен. "<< endl;
        break;
    case 2:
        num = ON;
        cout << "Ваш PC активен. " << endl;
        break;
    case 3:
        num = SLEEP;
        cout << "Ваш PC спит. " << endl;
        break;
    }
}