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
    cout << "������������ �������: " << max << " � �������� " << ind_1 << "," << ind_2 << endl;

    return 0;
}

int Sum(int** mas, int n) {
    int S1 = 0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            S1 += mas[i][j];
    cout << "����� ��������� ���� ������� ���������: " << S1;
    cout << endl;

    return 0;
}

int task_2()
{
    setlocale(LC_ALL, "Russian");
    const int MAX = 80;
    char  str1[MAX] = "Cool cap", str2[MAX];
    unsigned int   i, k = 0, m = 0, x = 0;
    cout << "�������� ������: " << str1 << endl;

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
    cout << "���������: " << str2 << endl;

    return 0;
}

int task_1()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    int** mas, n, m;
    cout << "������� ���������� �����: ";
    cin >> n;
    cout << "������� ���������� ��������: ";
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

    cout << "�������� ������: " << endl;

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
        cout << "�������� ������� ������" << endl;
        cout << "1 ������� " << endl;
        cout << "2 �������" << endl;
        cout << "3 - �����" << endl;
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


