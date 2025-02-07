//����������� ������� ����� � ����������, ������ �� �����, ��������, ������ ���������. ��������� ������������ ����������� � ���� ����.
//�������.�������� �������, ������������ ������, ��������� ���������, �����, �������� ��� �����, ���� �����, ���� ��������.
//����� ������� �� ��������� ����� ��������. ���� ����� ����������� � ������� �������� ����.
#include <iostream>
#include <fstream>
#include <string> 
#include<windows.h>
#define size 30  

using namespace std;

void input();
void output(int, int);
void del();
void find();
void print(int);


enum ConsoleColor
{
	Black = 0,
	Magenta = 5,
	LightMagenta = 13,
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

typedef struct Clients
{
	char fio[16];
	char product[16];
	int cost;
	int summ;
	int days;
} CLIENT;

struct Clients list_of_clients[size];
struct Clients bad;
int choice; int current_size = 0;

struct date
{
	unsigned int day : 5;  // ����� 1..31
	unsigned int month : 4;   // ����� ������ 1..12
	unsigned int year : 12;   // ��� 0..3000
};

date d; //��������� ���������� ����� ���� � �������� ������
int i;

int main()
{
	SetColor(Magenta, Black);
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");
	do
	{
		int n, number;
		cout << "\n1.���� ������ �������\n";
		cout << "2.����� ������\n";
		cout << "3.�������� ������\n";
		cout << "4.����� ���� ��������� �����\n";
		cout << "0.����� �� ���������\n\n";
		cout << "������� ����� ��������: ";
		cin >> choice;
		switch (choice)
		{
		case 1: input(); break;
		case 2: {
			int sw, n;
			cout << "1-����� 1 ������" << endl;
			cout << "2-����� ���� �����" << endl;
			cin >> sw;
			if (sw == 1)
			{
				cout << "����� ��������� ������ " << endl;
				cin >> n;
				cout << endl;
				output(sw, n);
			}
			else
			{
				output(sw, 99);
			}
			break; }
		case 3: del(); break;
		case 4: find(); break;
		}
	} while (choice != 0);
}

void input() {
	if (current_size < size)
	{
		cout << "������ ����� ";
		cout << current_size + 1;
		cout << endl << "�������: " << endl;
		cin >> list_of_clients[current_size].fio;
		cout << "�������� ��������: " << endl;
		cin >> list_of_clients[current_size].product;
		cout << "��������� ���������: " << endl;
		cin >> list_of_clients[current_size].cost;
		cout << "����� ������: " << endl;
		cin >> list_of_clients[current_size].summ;
		cout << "���� ��������: " << endl;
		cin >> list_of_clients[current_size].days;
		cout << "������� ���� �����" << endl;
		cout << "������� ����� (1-31): " << endl; cin >> i; d.day = i;
		cout << "������� ����� (1-12): " << endl; cin >> i; d.month = i;
		cout << "������� ��� (00-99) : " << endl; cin >> i; d.year = i;
		current_size++;
	}
	else
		cout << "������� ������������ ���-�� �����";
}

void output(int sw, int n)
{
	if (sw == 1)
	{
		print(n - 1);
	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			print(i);
		}
	}
}

void del()
{
	int d;
	cout << "\n����� ������, ������� ���� ������� (��� �������� ���� ����� ������ 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			list_of_clients[de1] = list_of_clients[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			list_of_clients[i] = bad;
}

void find()
{
	int key;
	cout << "���� ��������: " << endl;
	cin >> key;

	for (int i = 0; i < current_size; i++)
	{
		if (list_of_clients[i].days == key)
		{
			print(i);
		}
		else {
			cout << "�� �������";
		}
	}
}

void print(int h)
{
	cout << "�������: ";
	cout << list_of_clients[h].fio << endl;
	cout << "�������� ��������: ";
	cout << list_of_clients[h].product << endl;
	cout << "��������� ���������: ";
	cout << list_of_clients[h].cost << endl;
	cout << "����� ������: ";
	cout << list_of_clients[h].summ << endl;
	cout << "���� �������: ";
	cout << list_of_clients[h].days << endl;
	cout << "���� �����: " << d.day << "." << d.month << ".20" << d.year << " ";
}