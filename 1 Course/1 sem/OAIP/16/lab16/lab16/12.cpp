#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

int FindMin(int** arr, int n, int i, int min)
{
	int index;
	for (int j = 0; j < n; j++)
	{
		if (arr[i][j] < min)
		{
			min = arr[i][j];
			index = j;
		}
	}
	return index;
}
int* Copy(int** arr, int n, int k)
{
	int* buff = new int[n];
	for (int i = 0; i < n; i++)
	{
		buff[i] = arr[i][k];
	}
	return buff;
}

void task_1()
{
	setlocale(LC_ALL, "Russian");
	int n, min = INT_MAX, index;
	cout << "Введите порядок матрицы:";
	cin >> n;

	int** matr = new int* [n];
	for (int i = 0; i < n; i++)matr[i] = new int[n];

	cout << "Введите элементы:" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matr[i][j];
	for (int i = 0; i < n; i++)
	{
		index = FindMin(matr, n, i, min);
		int t = matr[i][i];
		matr[i][i] = matr[i][index];
		matr[i][index] = t;
		min = INT_MAX;
	}
	cout << "Результат:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matr[i][j] << "" << endl;
	}
	for (int i = 0; i < n; i++)
		delete[] matr[i];
	delete[] matr;
}


void task_2()
{
	setlocale(LC_ALL, "Russian");
	int n, min = INT_MAX, index;
	cout << "Введите порядок матрицы:";
	cin >> n;
	int** matr = new int* [n];
	for (int i = 0; i < n; i++)matr[i] = new int[n];

	cout << "Введите элементы:" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matr[i][j];
	int* buff_1 = new int[n];
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		count = 0;
		buff_1 = Copy(matr, n, i);
		for (int j = 0; j < n; j++)
		{
			if (matr[i][j] == buff_1[j])count++;
		}
		if (count == n) cout << "\nk = " << i << endl;
	}
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

