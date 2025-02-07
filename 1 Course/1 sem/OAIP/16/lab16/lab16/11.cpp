#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

int Max(int** mas, int n, int m) {

    int ind_1, ind_2;
    int max = mas[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mas[i][j] > max) {
                max = mas[i][j];
                ind_1 = i;
                ind_2 = j;
            }
        }
    }
    cout << "Максимальный элемент: " << max << " с индексом " << ind_1 << "," << ind_2 << endl;

    return 0;
}

int Sum(int** mas, int n) {
    int S1 = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            S1 += mas[i][j];
    cout << "Сумма элементов ниже главной диагонали: " << S1;
    cout << endl;

    return 0;
}

int task_2()
{
    setlocale(LC_ALL, "Russian");
    const int MAX = 80;
    char  str1[MAX] = "Cool cap", str2[MAX];
    unsigned int   i, k = 0, m = 0, x = 0;
    cout << "Исходная строка: " << str1 << endl;

    for (i = 0; str1[i]; i++)
    {
        if (str1[i] == 'c' || str1[i] == 'C') {
            str2[k] = str1[i];
            k++;
            str2[k] = '*';
            k++;
        }
        else   str2[k++] = str1[i];
    }
    str2[k] = '\0';
    cout << "Результат: " << str2 << endl;

    return 0;
}

int task_1()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int** mas, n, m;
    cout << "Введите количество строк: ";
    cin >> n;
    cout << "Введите количество столбцов: ";
    cin >> m;
    mas = new int* [n];

    for (int i = 0; i < n; i++)
    {
        mas[i] = new int[m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mas[i][j] = rand() % 20;
        }
    }

    cout << "Исходный массив: " << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) cout << setw(2) << mas[i][j] << " ";
        cout << endl;
    }

    Max(mas, n, m);
    Sum(mas, n);

    delete[] mas;
    return 0;
}

int main(void)
{
    setlocale(LC_CTYPE, "Russian");
    int choice;
    do
    {
        cout << "Выберите вариант работы" << endl;
        cout << "1 задание " << endl;
        cout << "2 задание" << endl;
        cout << "3 - выход" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1: task_1();
            break;
        case 2: task_2();
            break;
        case 3:  break;
        }
    } while (choice != 3);
}


