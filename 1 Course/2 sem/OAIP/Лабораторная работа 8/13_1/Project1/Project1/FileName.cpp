//������� ������� ��� ������� �����(������������� � �������������) �����.
//������� ��� �����, ������ � �������� ��������� �������.
//��� ����� ����� � ������� �������� ������ ������������� ��������.
//����� ����������� � ������������ ������� �������.
//������� ��� �������� ������� � ��������� �� ����������.

#include "myQueue.h"
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <string>
using namespace std;
int choice;

void Menu() {
	cout << "�������� �����" << endl
		<< "(1) ���� ���������" << endl
		<< "(2) ����� �������" << endl
		<< "(3) ����������� ������� �������" << endl
		<< "(4) �������� ��������" << endl
		<< "(5) ����� ������������� � ������������  ��������" << endl
		<< "(6) ���������� ��������" << endl
		<< "(0) �����" << endl;
	cin >> choice;
}
int main(int argc, char* argv[])
{
	int sizeposik;
	setlocale(LC_CTYPE, "rus");
	setlocale(LC_ALL, "Rus");
	Spisok A; // �������� ������� ������ Spisok � ������ A
	int el; // ���������� ���������� ��� �������� ������������ ��������
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
			cout << "������ ����� " << sizeposik << endl;
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
			cout << "������������ �������� " << max << endl;
			cout << "����������� �������� " << min << endl;
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