#include <iostream>
#include <algorithm>
using namespace std;

void task1() {
    int n = 10;
    int a[10] = { 5, 2, 3, 1, 9, 8, 7, 6, 10, 4 };

    sort(a, a + 4);
    sort(a + 4, a + n, greater<int>());

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}

void task2() {
    int n = 15;
    int a[15] = { 5, 2, 1, 1, 9, 8, 7, 6, 10, 10, -5, -4, -3, -2, -1 };

    sort(a, a + n);
    n = unique(a, a + n) - a;

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}

void task3() {
    setlocale(LC_CTYPE, "rus");
    int n = 7;
    // cout << "Введите количество элементов массива: ";
     //cin >> n;
    const int w = n;
    int a[7];
    for (int i = 0; i < n; i++)
    {
        bool unique;
        do {
            unique = true;
            cout << "Введите элемент " << i + 1 << ": ";
            cin >> a[i];
            for (int j = 0; j < i; j++) {
                if (a[i] == a[j]) {
                    cout << "Элемент уже введен, введите другой элемент." << endl;
                    unique = false;
                    break;
                }
            }
        } while (!unique);
    }

    int max = a[0], min = a[0], max_index = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
            max_index = i;
        }
        if (a[i] < min)
            min = a[i];
    }

    cout << "Максимальный элемент массива: " << max << ", его индекс: " << max_index << endl;
    cout << "Минимальный элемент массива: " << min << endl;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    cout << endl << "1 задание" << endl;
    task1();
    cout << endl << "2 задание" << endl;
    task2(); 
    cout << endl << "3 задание" << endl;
    task3();
}

