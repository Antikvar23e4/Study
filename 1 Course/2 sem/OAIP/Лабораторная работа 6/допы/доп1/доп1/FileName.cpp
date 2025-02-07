#include "list.h"
#include <iostream>
#include <tchar.h>
using namespace std;

struct Person {
	int nomer;
	char punkt[25];
	int days;
	char  vremya[25];
	char  vremya2[25];
	Person* next;
};

void print(void* b) {
	Person* a = (Person*)b;
	cout << a->nomer << "  " << a->punkt << "  " << a->days << "  " << a->vremya << "  " << a->vremya2 << endl;
}

void print2(void* b) {
	Person* a = (Person*)b;
}

void Searcing() {

}

int state_menu;
void Menu();

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	//������. ����� ������, ����� ����������, ��� ����������, ����� ��������, ����� �����������. 
	Person a1 = { 34145, "�����", 2, "11.00", "15.00" };
	Person a2 = { 56578, "�����", 5, "12.00", "16.30" };
	Person a3 = { 68757, "������", 2, "16.00", "10.30" };

	bool rc; int number;
	Object L1 = Create();   // �������� ������ � ������ L1
	L1.Insert(&a1);
	L1.Insert(&a2);
	L1.Insert(&a3);

	Menu();
	while (state_menu != 0) {
		switch (state_menu) {
		case 1: {
			system("cls");
			cout << "������� ����� ������ " << endl;
			cin >> number;
			if (number == a1.nomer) {
				Element* e = L1.Search(&a1);
				Person* aa = (Person*)e->Data;
				cout << "������ ������� " << aa->nomer << "  " << aa->punkt << "  " << aa->days << "  " << aa->vremya << "  " << aa->vremya2 << endl;
			}
			if (number == a2.nomer) {
				Element* e = L1.Search(&a2);
				Person* aa = (Person*)e->Data;
				cout << "������ ������� " << aa->nomer << "  " << aa->punkt << "  " << aa->days << "  " << aa->vremya << "  " << aa->vremya2 << endl;
			}
			if (number == a3.nomer) {
				Element* e = L1.Search(&a3);
				Person* aa = (Person*)e->Data;
				cout << "������ ������� " << aa->nomer << "  " << aa->punkt << "  " << aa->days << "  " << aa->vremya << "  " << aa->vremya2 << endl;
			}
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 2: {
			system("cls");
			cout << "������� ����� ������" << endl;
			cin >> number;
			if (number == a1.nomer) {
				rc = L1.Delete(&a1);
				if (rc == true) cout << "������ �������" << endl;
			}
			if (number == a2.nomer) {
				rc = L1.Delete(&a2);
				if (rc == true) cout << "������ �������" << endl;
			}
			if (number == a3.nomer) {
				rc = L1.Delete(&a3);
				if (rc == true) cout << "������ �������" << endl;
			}
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 3: {
			system("cls");
			L1.PrintList(print);
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 4: {
			system("cls");
			L1.CountList(print2);
			system("pause");
			system("cls");
			Menu();
			break;
		}
		case 5: {
			system("cls");
			L1.DeleteList();
			system("pause");
			system("cls");
			Menu();
			break;
		}
		}
	}
	return 0;
}

void Menu() {
	cout << "�������� ��������" << endl
		<< "(1) ����� ��������" << endl
		<< "(2) �������� ��������" << endl
		<< "(3) ����� ������" << endl
		<< "(4) ������� ����� ��������� ������" << endl
		<< "(5) �������� ������" << endl
		<< "(0) �����" << endl;
	cin >> state_menu;
}