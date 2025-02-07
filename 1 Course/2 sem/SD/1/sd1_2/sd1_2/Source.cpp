//Написать программу, в которой нужно удалить все элементы односвязного списка и добавить n новых, с выводом на экран.


#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    int x,i;
    forward_list<int> newlist = { 3, 2, 8, 4, 1 };
    newlist.clear();//удаляет все элементы
    cout << "Введите сколько чисел хотите добавить: " << endl;
    cin >> x;
    for (int i = 0; i < x; i++) {
        newlist.emplace_front(rand() % 10);//добавляет объекты в начало списка
    }
    for (int n : newlist)//вывод нашего списка
    {
        cout << n << "\t";
    }
}
