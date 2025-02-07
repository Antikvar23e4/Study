//�����������.
//������������, �������, ����������� ���������, �������, ������� ����������.
//����� ����������� �� ��������.
#include <iostream>   
#include <windows.h>
# define str_len 50                             
# define size 30  

using namespace std;

void enter_new();
void del();
void out();
void search();

union GOV
{
	char name[str_len];
	char capital[str_len];
	int area;
	int popularity;
	char president[str_len];
}govu;

struct GOVERNMENT
{
	char name[str_len];
	char capital[str_len];
	int area;
	int popularity;
	char president[str_len];
};

struct GOVERNMENT listOfGov[size];
struct GOVERNMENT bad;
struct GOVERNMENT change[1];

int current_size = 0;
int choice;
int check = 0;
int current_check = 0, current_checkName = 0;
int buf = 0;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	cout << "�������:" << endl;
	cout << "1-��� �������� ������" << endl;
	cout << "2-��� ����� ����� ������" << endl;
	cout << "3-��� ������ ������(��)" << endl;
	cout << "4-��� ������ ����������" << endl;
	cout << "0-��� ������" << endl;
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1:  del();	break;
		case 2:  enter_new();  break;
		case 3:  out();	break;
		case 4:  search();	break;
		}
	} while (choice != 0);
}

void enter_new()
{
	int currentForm;
	cout << "���� ����������" << endl;
	if (current_size < size)
	{
		cout << "������ ����� ";
		cout << current_size + 1;
		cout << endl << "������������: ";
		cin.ignore();
		cin.getline(govu.name, 50);
		strcpy_s(listOfGov[current_size].name, govu.name);
		cout << endl << "�������: ";
		cin.getline(govu.capital, 50);
		strcpy_s(listOfGov[current_size].capital, govu.capital);
		cout << endl << "�������(��^2): ";
		cin >> govu.area;
		listOfGov[current_size].area = govu.area;
		cout << endl << "����������� ���������(���. ���.): ";
		cin >> govu.popularity;
		listOfGov[current_size].popularity = govu.popularity;
		cout << endl << "��� ����������: ";
		cin.ignore();
		cin.getline(govu.president, 50);
		strcpy_s(listOfGov[current_size].president, govu.president);
		current_size++;
	}
	else
	{
		cout << "������� ������������ ���-�� �����";
	}


	do
	{
		check = 0;
		for (int i = 0; i < current_size - 1; i++)
		{
			if (strcmp(listOfGov[i].name, listOfGov[i + 1].name) > 0)
			{
				change[1] = listOfGov[i];
				listOfGov[i] = listOfGov[i + 1];
				listOfGov[i + 1] = change[1];
				check++;
			}
		}
	} while (check > 0);
	cout << "��� �� ������ ������� ������?." << endl;
	cin >> choice;
}

void del()
{
	int d;
	cout << "\n����� ������, ������� ���� ������� (��� �������� ���� ����� ������ 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			listOfGov[de1] = listOfGov[de1 + 1];
		current_size = current_size - 1;
		current_check--;
	}
	if (d == 99)
	{
		current_check--;
		for (int i = 0; i < size; i++)
			listOfGov[i] = bad;
	}

	cout << "��� �� ������ ������� ������?." << endl;
	cin >> choice;
}
void out()
{
	int sw, n;
	cout << "1-����� 1 ������" << endl;
	cout << "2-����� ���� �����" << endl;
	cin >> sw;

	if (sw == 1)
	{
		cout << "����� ��������� ������ " << endl;   cin >> n;  cout << endl;
		cout << endl << "\n������������      �������        �������(��^2)        ����������� ���������(���. ���.)         ��� ����������\n";
		cout << listOfGov[n - 1].name << "\t   " << listOfGov[n - 1].capital << "\t       " << listOfGov[n - 1].area << "\t\t            " << listOfGov[n - 1].popularity << "\t\t            " << listOfGov[n - 1].president << endl;
	}
	if (sw == 2)
	{
		cout << endl << "\n������������      �������        �������(��^2)        ����������� ���������(���. ���.)         ��� ����������\n";
		for (int i = 0; i < current_size; i++)
		{

			cout << listOfGov[i].name << "\t   " << listOfGov[i].capital << "\t       " << listOfGov[i].area << "\t\t            " << listOfGov[i].popularity << "\t\t            " << listOfGov[i].president << endl;
		}
	}
	cout << endl << endl;
	cout << "��� �� ������ ������� ������?." << endl;
	cin >> choice;
}
void search()
{
	int choose; int none = 0; struct GOVERNMENT searching[1];
	printf("������� ����� ������������ ���� ������:\n");
	printf("1 - ����� �� ������������\n");
	cin >> choose;
	if (choose == 1)
	{
		printf("������� ������������ �����������: ");
		cin.ignore();
		cin.getline(searching[0].name, 30);
		cout << endl << "\n������������      �������        �������(��^2)        ����������� ���������(���. ���.)         ��� ����������\n";
		for (int i = 0; i < current_size; i++)
		{
			if (strcmp(searching[0].name, listOfGov[i].name) == 0)
			{
				cout << listOfGov[i].name << "\t   " << listOfGov[i].capital << "\t       " << listOfGov[i].area << "\t\t            " << listOfGov[i].popularity << "\t\t            " << listOfGov[i].president << endl;
				none++;
			}
		}
		if (none == 0)
		{
			printf("�� ���� ������� �� ����� ������\n");
		}
	}
	cout << "��� �� ������ ������� ������?." << endl;
	cin >> choice;
}