#include <iostream>
# define str_len 30                               
# define size 30  
using namespace std;

//. ����������� ������� ����� � ����������, ������ �� �����, ��������, ������ ���������. 
// ��������� ������������ �����-������ � ���� ����.
// ������ ����������. 
// ����� �����, ��������, ������������, ������ ���������� 
// (����������� ����������, �����, �������� ���������, ������������� � �. �.), 
// ������������� (�������, �����, �������) � ������� ����� � ������ ������. 
// ����� ���� �� ����. ������������� ����� ����������� � ������� ������������.
//                  

void enter_new();
void del();
void find();
void out(int, int);
void print(int);

struct byte
{
	unsigned a : 1;
	unsigned b : 1;
};

enum Origin
{
	bought = 1, stolen, gifted
};

struct Lib
{
	char author[str_len];
	char name[str_len];
	char publisher[str_len];
	int year;
	char section[str_len];
	byte availability;
	Origin origin;
};
struct Lib list_of_books[size];
struct Lib bad;
int book_origin;
int book_status;
int current_size = 0; int choice;
void Menu()
{
	cout << "�������:" << endl;
	cout << "1-��� �������� ������" << endl;
	cout << "2-��� ����� ����� ������" << endl;
	cout << "3-��� ����� �� ����" << endl;
	cout << "4-��� ������ ������(��)" << endl;
	cout << "5-��� ������" << endl;
}
int main()
{
	setlocale(LC_CTYPE, "Russian");
	Menu();
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1:  del();	 break;
		case 2:  enter_new(); break;
		case 3:  find(); break;
		case 4:
		{
			int sw, n;
			cout << "1-����� 1 ������" << endl;
			cout << "2-����� ���� �����" << endl;
			cin >> sw;
			if (sw == 1)
			{
				cout << "����� ��������� ������ " << endl;
				cin >> n;
				cout << endl;
				out(sw, n);
			}
			else
			{
				out(sw, 99);
			}
			break;
		}

		}
	} while (choice != 5);
}
void enter_new()
{
	cout << "���� ����������" << endl;
	if (current_size < size)
	{
		cout << "����� ������ ";
		cout << current_size + 1;
		cout << endl << "������� ������ " << endl;
		cin >> list_of_books[current_size].author;
		cout << endl << "�������� ����� " << endl;
		cin >> list_of_books[current_size].name;
		cout << endl << "��� ������� " << endl;
		cin >> list_of_books[current_size].year;
		cout << endl << "������ ���������� " << endl;
		cin >> list_of_books[current_size].section;
		cout << endl << "������������ ����� " << endl
			<< "(1) - �������" << endl
			<< "(2) - ��������" << endl
			<< "(3) - ��������" << endl;
		cin >> book_origin;
		switch (book_origin)
		{
		case 1: list_of_books[current_size].origin = bought;
			break;
		case 2: list_of_books[current_size].origin = stolen;
			break;
		case 3: list_of_books[current_size].origin = gifted;
			break;
		default:
			cout << "write 1 - 3";
			break;
		}
		cout << endl << "�������" << endl
			<< "(1) - ����" << endl
			<< "(0) - ���" << endl;
		cin >> book_status;
		if (book_status)
		{
			list_of_books[current_size].availability.a = true;
			list_of_books[current_size].availability.b = false;
		}
		else
		{
			list_of_books[current_size].availability.b = true;
			list_of_books[current_size].availability.a = false;
		}

		current_size++;
	}
	else
		cout << "������� ������������ ���-�� �����";
	cout << "��� ������?" << endl;
	Menu();
	cin >> choice;
}
void del()
{
	int d;
	cout << "\n����� ������, ������� ���� ������� (��� �������� ���� ����� ������ 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			list_of_books[de1] = list_of_books[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			list_of_books[i] = bad;
	cout << "��� ������?" << endl;
	Menu();
	cin >> choice;
}
void find()
{
	int year;
	cout << "�������: " << endl;
	cout << "��� �������" << endl;
	cin >> year;

	for (int i = 0; i < current_size; i++)
	{
		if (list_of_books[i].year == year)
		{
			print(i);
		}
	}

	cout << "��� ������?" << endl;
	Menu();
	cin >> choice;
}

void out(int sw, int n)
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
	cout << "��� ������?" << endl;
	Menu();
	cin >> choice;
}
void print(int n)
{
	cout << "\n\n����� ";
	cout << n;
	cout << endl << "������� ������ " << endl;
	cout << list_of_books[n].author;
	cout << endl << "�������� ����� " << endl;
	cout << list_of_books[n].name;
	cout << endl << "��� ������� " << endl;
	cout << list_of_books[n].year;
	cout << endl << "������ ����������" << endl;
	cout << list_of_books[n].section;
	cout << endl << "������������� ����� " << endl;
	switch (list_of_books[n].origin)
	{
	case 1: cout << "�������"; break;
		break;
	case 2: cout << "��������"; break;
		break;
	case 3: cout << "��������"; break;
		break;
	default:
		cout << "write 1 - 3";
		break;
	}
	cout << endl << "������� " << endl;
	if (list_of_books[n].availability.a)
	{
		cout << "���� � �������" << endl;
	}
	else
	{
		cout << "��� � �������" << endl;
	}
}
