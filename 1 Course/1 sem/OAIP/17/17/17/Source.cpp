#include <iostream>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
void task_1()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    cout << "Задание 1" << endl;
    const int n = 20;
    int* a = new int[n];
    int z = 0, k = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите\t" << i + 1 << "-й элемент массива:";
        cin >> a[i];
    }

    for (int i = 1; i < n; i += 2)
        if (a[i] > 0)
        {
            z++;
        }
    cout << "колличество положительных элементов, которые стоят на четных позициях = " << z << "\n";

    int* b = new int[z];
    for (int i = 0; i < 11; i += 2) {
        if (a[i] > 0)
        {
            b[k] = a[i];
            k++;
        }
    }
    cout << endl;
    for (int i = 0; i < z; i++)
    {
        cout << b[i];
    }
    int summa = 0;
    for (int i = 0; i < z; i++)
    {
        summa += (b[i] * b[i]);
        cout << "\nOTVET: " << summa << endl;
    }
}

void task_2()
{
    setlocale(LC_ALL, "rus");
    cout << "Задание 2" << endl;
    const int SIZE = 5;
    int i, j, min, i_min = 0;
    int arr[SIZE][SIZE];

    srand(time(NULL));

    for (i = 0; i < SIZE; ++i)
    {
        for (j = 0; j < SIZE; ++j)
        {
            arr[i][j] = rand() % 20;
        }
    }

    for (i = 0; i < SIZE; ++i)
    {
        for (j = 0; j < SIZE; ++j)
        {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }

    min = arr[0][0];
    for (i = 0; i < SIZE; ++i)
    {
        if (arr[i][i] < min)
        {
            min = arr[i][i];
            i_min = i;
        }
    }

    cout << "Минимальный элемент ["
        << i_min << "][" << i_min << "] = "
        << min << endl;

    cout << "Столбец: ";

    for (i = 0; i < SIZE; ++i)
    {
        cout << arr[i][i_min] << ' ';
    }
}


int main() {
    task_1();
    task_2();
}