
#include <iostream>
#include <iomanip>
#include <iostream>
using namespace std;

//1. � ������� A[k, n], k <= 12, n <= 8 �������� ������� ������, ���������� ������� � �� �������, ���������� ������� b.
void task_1()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));


    int** mas, k, n, a, b, c, d;
    cout << "������� ����������� �����: " << endl;
    cin >> k;
    cout << "������� ����������� ��������: " << endl;
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

    cout << "�������� ������� " << endl;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++) cout << mas[i][j] << " ";

        cout << endl;
    }
    cout << "������� �������: " << endl;
    cin >> a;
    cout << "������� �������: " << endl;
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

//2. ���� �����������. ��������� ���������, ������� ������� ��� �����, �������������� �� -��.
void task_2()
{
	setlocale(LC_ALL, "Russian");
	char str[] = "������� �� ����� �������� !", res[1000];
	int counter = 0, ind = 0;
    cout << "������� �� ����� �������� !" << endl;
    cout << "���������:" << endl;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ' || str[i] == '.')
			if (str[i - 1] == '�' && str[i - 2] == '�')
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












