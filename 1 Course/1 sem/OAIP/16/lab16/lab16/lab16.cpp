
#include <iostream>
#include <iomanip>
#include <iostream>
using namespace std;

//1. В матрице A[k, n], k <= 12, n <= 8 поменять местами строку, содержащую элемент а со строкой, содержащей элемент b.
void task_1()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));


    int** mas, k, n, a, b, c, d;
    cout << "Введите колличество строк: " << endl;
    cin >> k;
    cout << "Введите колличество столбцов: " << endl;
    cin >> n;
    mas = new int* [k];

    for (int i = 0; i < k; i++)
    {
        mas[i] = new int[n];
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mas[i][j] = rand() % 100 - 1;
        }
    }

    cout << "Исходная матрица " << endl;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++) cout << mas[i][j] << " ";

        cout << endl;
    }
    cout << "Введите элемент: " << endl;
    cin >> a;
    cout << "Введите элемент: " << endl;
    cin >> b;


    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (mas[i][j] == a) {
                c = i;
            }
            if (mas[i][j] == b) {
                d = i;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            swap(mas[c][j], mas[d][j]);
        }
    }

    cout << setw(7);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cout << mas[i][j] << setw(7);
        }
        cout << endl;
    }

}

//2. Дано предложение. Составить программу, которая выводит все слова, оканчивающиеся на -ая.
void task_2()
{
	setlocale(LC_ALL, "Russian");
	char str[] = "Сегодня ты самая красивая !", res[1000];
	int counter = 0, ind = 0;
    cout << "Сегодня ты самая красивая !" << endl;
    cout << "Результат:" << endl;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ' || str[i] == '.')
			if (str[i - 1] == 'я' && str[i - 2] == 'а')
			{
				{
					for (int k = counter; k > 0; k--)
					{
						res[ind] = str[i - k];
						ind++;
					}
					res[ind] = ' ';
					ind++;
				}
			}

		if (str[i] == ' ')
			counter = 0;
		counter++;
	}

	res[ind] = '\0';

	for (int i = 0; i < strlen(res); i++)
	{
		cout << res[i];
	}
    cout << " " << endl;
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












