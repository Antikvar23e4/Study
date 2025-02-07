// Компоненты файла f – целые числа. Получить файл g, образованный из f включающие  повторных вхождений одного и того же числа.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "");
	int n;
	FILE* A;
	FILE* B;
	A = fopen("f.txt", "r");

	fscanf_s(A, "%d", &n);
	int a[100];
	for (int i = 0; i < n; i++) {
		fscanf_s(A, "%d", &a[i]);
		printf("%d   ", a[i]);
	}
	fclose(A);
	B = fopen("g.txt", "w");
	cout << endl;

	for (int i = 0; i < n; i++)
	{

		for (int k = i + 1; k < n; k++)
		{
			if (a[i] == a[k])
			{

				int w = 0;
				for (int k = 0; k < i; k++) {
					if (a[k] == a[i]) {
						w = 1; break;
					}
				}
				if (w == 0) {
					fprintf(B, "%d ", a[i]);
					cout << a[i] << " ";
				}
				break;
			}
		}
	}
	fclose(B);
	return 0;
}