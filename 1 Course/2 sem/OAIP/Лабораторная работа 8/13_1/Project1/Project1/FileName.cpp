//Создать очередь для массива целых(положительных и отрицательных) чисел.
//функции для ввода, вывода и удаления элементов очереди.
//При вводе чисел в очередь помещать только отрицательные элементы.
//Найти минимальный и максимальный элемент очереди.
//Вывести все элементы очереди и посчитать их количество.

#include "myQueue.h"
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <string>
using namespace std;
int choice;

void Menu() {
	cout << "Выберите пункт" << endl
		<< "(1) Ввод элементов" << endl
		<< "(2) Вывод очереди" << endl
		<< "(3) Определение размера очереди" << endl
		<< "(4) Удаление элемента" << endl
		<< "(5) Поиск максимального и минимального  элемента" << endl
		<< "(6) Добавление элемента" << endl
		<< "(0) Выход" << endl;
	cin >> choice;
}
int main(int argc, char* argv[])
{
	int sizeposik;
	setlocale(LC_CTYPE, "rus");
	setlocale(LC_ALL, "Rus");
	Spisok A; // создание объекта класса Spisok с именем A
	int el; // объявление переменной для хранения добавляемого элемента
	int size, max, min;
	Menu();
	while (choice != 0) {
		switch (choice) {
		case 1: {
			system("cls");
			A.POSTROENIE();
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 2: {
			system("cls");
			A.VYVOD();
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 3: {
			system("cls");
			sizeposik = A.Size();
			cout << "Размер равен " << sizeposik << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 4: {
			system("cls");
			A.YDALENIE();
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 5: {
			system("cls");
			max = A.findMax();
			min = A.findMin();
			cout << "Максимальный элемнент " << max << endl;
			cout << "Минимальный элемнент " << min << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 6: {
			system("cls");
			A.DOBAVLENIE();
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 0:
			A.OCHISTKA();
			return 0;
			break;
		}
	}
	return 0;
}