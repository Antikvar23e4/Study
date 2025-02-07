#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

void Fill(int** matrix, int sz, int max_value)
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			matrix[i][j] = rand() % (max_value + 1);
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
 }

void getstring(char** string_array, int x)
{
	string_array[x] = new char[200];
	cin.getline(string_array[x], 200);

}

void define_amount(char** string_array, int x)
{
	int amount = 0;
	for (int i = 0; string_array[x][i] != '\0'; i++)
	{
		if (string_array[x][i] == 'm')amount++;

	}
	cout << "Символ входит в строку " << x + 1 << ": " << amount << endl;
}

void task_1()
{
	setlocale(LC_ALL, "Russian");
	int sz, sum = 0;
	cout << "Введите размер матрицы:";
	cin >> sz;
	cout << "\n\n";
	int** matrix = new int* [sz];
	for (int i = 0; i < sz; i++) matrix[i] = new int[sz];
	Fill(matrix, sz, 100);
	for (int i = 0; i < sz; i++)
	{
     for(int j = 0;j<sz;j++)
	 { 
		 if (j != i)
		 {
			 sum += matrix[i][j];
		 }
		 else break;
	 }
	}
	cout << "\n\nСуммма элементов под главной диагональю:" << sum << "\n\n";
	for (int i = 0; i < sz; i++)delete[] matrix[i];
	delete[] matrix;
}


void task_2()
{
	setlocale(LC_ALL, "Russian");
	int strings_amount;
	cout << "";
	cin >> strings_amount;
	char** string_array = new char* [strings_amount];
	cout << endl;
	for (int i = 0; i < strings_amount; i++)
	{
		cout << "\n" << i + 1 << "\n";
		if (i == 0)cin.ignore();
		getstring(string_array, i);
	}
	cout << "\n\n";
	for (int i = 0; i < strings_amount; i++)
	{
		define_amount(string_array, i);
	}
	for (int i = 0; i < strings_amount; i++) delete[] string_array[i];
	delete[] string_array;
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

