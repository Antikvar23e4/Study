// Компоненты файла fileA –  целые числа, значения которых повторяются.
// Получить файл fileB, образованный из fileA числами, которые встречаются в fileA более 2 раз.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include<ctime>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");

	FILE* F1;
	FILE* F2;
	errno_t er, err2;
	const int size = 20;

	int a[size];
	er = fopen_s(&F1, "fileA.txt", "w");
	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % 10;
		fprintf(F1, "%d ", a[i]);
	}
	fclose(F1);
	er = fopen_s(&F1, "fileA.txt", "r");
	for (int i = 0; i < size; i++)
	{
		fscanf(F1, "%d ", &a[i]);
		std::cout << a[i] << " ";
	}

	err2 = fopen_s(&F2, "fileB.txt", "w");

	cout << endl;
	int kol = 0;
	for (int i = 0; i < size; i++)
	{
		kol = 1;
		for (int j = i + 1; j < size; j++)
		{
			if (a[i] == a[j])
			{
				kol++;
				int w = 0;
				for (int k = 0; k < i; k++) {
					if (a[k] == a[i]) {
						w = 1; break;
					}
				}
				if (w == 0 && kol > 2) {
					fprintf(F2, "%d ", a[i]);
					cout << a[i] << " ";
					break;
				}

			}
		}
	}
	fclose(F2);
	return 0;
}