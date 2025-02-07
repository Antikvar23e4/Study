//Написать программу, в которой в начало двусвязного списка добавляется n элементов и вывести на экран.

#include <iostream> 
#include <list>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    int x, i;
    list<int> newlist = { 6, 2, 8, 4, 5 };
    cout << "Первоначальный массив: : " << endl;
    for (int n : newlist)
    {
        cout << n << "\t";
    }
    cout << "" << endl;
    cout << "Введите сколько чисел хотите добавить: " << endl;
    cin >> x;
    for (int i = 0; i < x; i++) {
        newlist.push_front(rand() % 10);//добавляет объекты в начало списка
    }

    cout << "Конечный массив: : " << endl;
    for (int n : newlist)
    {
        cout << n << "\t";
    }
}
