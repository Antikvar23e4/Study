
#include <iostream>
#include "vybor1.h"
#include "vybor2.h"
#include "vybor3.h"


void main()
{
	using namespace std;
	setlocale(LC_ALL, "ru");
	int n;
	char symbol1, symbol2;
	char symb1, symb_2;
	cout << "�������� ���� �� ���������:\n1 � ����������� ������� �������� ����� � Windows-1251 ����� ���������� �������� � ��������� � �������� ���������; \n2 � ����������� ������� �������� ����� � Windows-1251 ����� �������� �������� � ��������� � �������� ���������; \n3 � ����� � ������� ���� �������, ���������������� ��������� �����; \n4 � ����� �� ���������." << endl;
	cin >> n;
	while (n > 4 && n < 1) {
		cout << "������� ��� ������: ";  cin >> n;
	}
	switch (n) {
	case 1:
		vybor1();
		break;
	case 2:
		vybor2();
		break;
	case 3:
		vybor3();
		break;
	case 4:
		break;
	default:
		break;
	}
}