
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int _stateMenu;
void input();
void output();
void delData();
void delFile();

char fileName[20];

struct base
{
	string name;
	string adress;
	string number;
};

void Menu() {
	cout << "�������� ��������:" << endl
		<< "(1) ���������� ������" << endl
		<< "(2) ����������� ���������" << endl
		<< "(3) �����  ����������" << endl
		<< "(4) �������� ���������" << endl
		<< "��� �����: ";
	cin >> _stateMenu;
}

int main()
{
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	char client, number;
	Menu();
	while (_stateMenu != 0) {

		switch (_stateMenu)
		{
		case 1:
			system("cls");
			int choice, clientData;
			system("cls");
			cout << "������ ������� 2 - �������, 1 - ������, 0 - �����������?" << endl;
			cin >> choice;
			switch (choice) {
			case 2:
				system("cls");
				cout << "������� ������ � ������� (1) ��� ������� ������� �� ���� ������ (2)?" << endl;
				cin >> clientData;
				if (clientData == 1)
				{
					delData();
				}
				else
				{
					delFile();
				}
				system("pause");
				system("cls");
				Menu();
				break;
			case 1:
				system("cls");
				cout << "���� ������" << endl;
				input();
				system("pause");
				system("cls");
				Menu();
				break;
			case 0:
				system("cls");
				cout << "����� ������" << endl;
				output();
				system("pause");
				system("cls");
				Menu();
				break;
			default:
				system("cls");
				cout << "������� ������ ����� ��������!" << endl;
				system("pause");
				system("cls");
				Menu();
			}
			break;
			system("pause");
			system("cls");
			Menu();
			break;
		case 2:
			system("cls");
			cout << "�������� ������� ��� ����������� ���������: " << endl;
			cin >> client;
			cout << "�������� ���������!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 3:
			system("cls");
			cout << "������� ����� ��������� ��� ������: " << endl;
			cin >> number;
			cout << "��������� ��������!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");
			cout << "������� ����� ��������� ��� ��������: " << endl;
			cin >> number;
			cout << "��������� �������!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		default:
			system("cls");
			cout << "������� ������ ����� ��������!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
	}
}

void input()
{
	cout << "������� �������� ����� ��� ����� ������ �������: ";
	cin >> fileName;
	base b[1];
	for (int i = 0; i < 1; ++i)
	{
		cout << "������� ��� : " << endl;
		cin >> b[i].name;
		cout << "������� �����: " << endl;
		cin >> b[i].adress;
		cout << "������� ����� ��������: " << endl;
		cin >> b[i].number;
	}
	ofstream fout(fileName); // ������ � ����
	if (!fout.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else
	{
		for (int i = 0; i < 1; ++i)
		{
			fout << "��������: " << b[i].name << endl  << "�����: " << b[i].adress << endl << "����� ��������: " << b[i].number << endl;
		}

	}
	fout.close();
}

void output()
{
	string s; // ��������� ������
	ifstream fin(fileName); // ���� �� �������� ������ 

	if (!fin.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else
	{
		while (getline(fin, s)) { // ���� �� ��������� ����� ����� ������ ��������� ������ � ���������� (s)
			cout << s << endl; // ������� �� �����
		}
	}
	fin.close(); //��������� ���� 
}

void delData()
{
	ofstream fon(fileName, ios_base::out | ios_base::trunc);
	cout << "������ � ������� �������" << endl;
}

void delFile()
{
	remove(fileName);
	cout << "������ ����� �� ���� ������" << endl;
}

