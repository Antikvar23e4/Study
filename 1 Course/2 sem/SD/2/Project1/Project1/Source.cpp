
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
	cout << "Выберите действие:" << endl
		<< "(1) Клиентские данные" << endl
		<< "(2) Составление документа" << endl
		<< "(3) Вывод  документов" << endl
		<< "(4) Удаление докуменов" << endl
		<< "Ваш выбор: ";
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
			cout << "Данные клиента 2 - удалить, 1 - ввести, 0 - просмотреть?" << endl;
			cin >> choice;
			switch (choice) {
			case 2:
				system("cls");
				cout << "Удалить данные о клиенте (1) или удалить клиента из базы данных (2)?" << endl;
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
				cout << "Ввод данных" << endl;
				input();
				system("pause");
				system("cls");
				Menu();
				break;
			case 0:
				system("cls");
				cout << "Вывод данных" << endl;
				output();
				system("pause");
				system("cls");
				Menu();
				break;
			default:
				system("cls");
				cout << "Неверно введен номер действия!" << endl;
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
			cout << "Выберите клиента для составления документа: " << endl;
			cin >> client;
			cout << "Документ составлен!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 3:
			system("cls");
			cout << "Введите номер документа для вывода: " << endl;
			cin >> number;
			cout << "Документы выведены!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");
			cout << "Введите номер документа для удаления: " << endl;
			cin >> number;
			cout << "Документы удалены!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		default:
			system("cls");
			cout << "Неверно введен номер действия!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
	}
}

void input()
{
	cout << "Введите название файла для ввода данных клиента: ";
	cin >> fileName;
	base b[1];
	for (int i = 0; i < 1; ++i)
	{
		cout << "Введите ФИО : " << endl;
		cin >> b[i].name;
		cout << "Введите адрес: " << endl;
		cin >> b[i].adress;
		cout << "Введите номер телефона: " << endl;
		cin >> b[i].number;
	}
	ofstream fout(fileName); // Запись в файл
	if (!fout.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		for (int i = 0; i < 1; ++i)
		{
			fout << "Название: " << b[i].name << endl  << "Адрес: " << b[i].adress << endl << "Номер телефона: " << b[i].number << endl;
		}

	}
	fout.close();
}

void output()
{
	string s; // считанные строки
	ifstream fin(fileName); // файл из которого читаем 

	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n"; // сообщить об этом
	else
	{
		while (getline(fin, s)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
			cout << s << endl; // выводим на экран
		}
	}
	fin.close(); //закрываем файл 
}

void delData()
{
	ofstream fon(fileName, ios_base::out | ios_base::trunc);
	cout << "Данные о клиенте удалены" << endl;
}

void delFile()
{
	remove(fileName);
	cout << "Клиент удалён из базы данных" << endl;
}

