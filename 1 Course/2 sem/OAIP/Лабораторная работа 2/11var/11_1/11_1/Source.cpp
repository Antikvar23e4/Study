//Реализовать функции ввода с клавиатуры, вывода на экран, удаления, поиска элементов. Интерфейс пользователя осуществить в виде меню.
//Ломбард. Фамилия клиента, наименование товара, оценочная стоимость, сумма, выданная под залог, дата сдачи, срок хранения.
//Выбор товаров по истечении срока хранения. Дату сдачи реализовать с помощью битового поля.
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
	unsigned int day : 5;  // число 1..31
	unsigned int month : 4;   // номер месяца 1..12
	unsigned int year : 12;   // год 0..3000
};

date d; //объявляем переменную этого типа с битовыми полями
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
		cout << "\n1.Ввод данных клиента\n";
		cout << "2.Вывод данных\n";
		cout << "3.Удаление данных\n";
		cout << "4.Поиск даты истечения срока\n";
		cout << "0.Выход из программы\n\n";
		cout << "Введите номер операции: ";
		cin >> choice;
		switch (choice)
		{
		case 1: input(); break;
		case 2: {
			int sw, n;
			cout << "1-вывод 1 строки" << endl;
			cout << "2-вывод всех строк" << endl;
			cin >> sw;
			if (sw == 1)
			{
				cout << "Номер выводимой строки " << endl;
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
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "Фамилия: " << endl;
		cin >> list_of_clients[current_size].fio;
		cout << "Название продукта: " << endl;
		cin >> list_of_clients[current_size].product;
		cout << "Оценочная стоимость: " << endl;
		cin >> list_of_clients[current_size].cost;
		cout << "Сумма залога: " << endl;
		cin >> list_of_clients[current_size].summ;
		cout << "Срок хранения: " << endl;
		cin >> list_of_clients[current_size].days;
		cout << "Введите дату сдачи" << endl;
		cout << "Введите число (1-31): " << endl; cin >> i; d.day = i;
		cout << "Введите месяц (1-12): " << endl; cin >> i; d.month = i;
		cout << "Введите год (00-99) : " << endl; cin >> i; d.year = i;
		current_size++;
	}
	else
		cout << "Введено максимальное кол-во строк";
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
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;  cin >> d;
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
	cout << "Срок хранения: " << endl;
	cin >> key;

	for (int i = 0; i < current_size; i++)
	{
		if (list_of_clients[i].days == key)
		{
			print(i);
		}
		else {
			cout << "Не найдено";
		}
	}
}

void print(int h)
{
	cout << "Фамилия: ";
	cout << list_of_clients[h].fio << endl;
	cout << "Название продукта: ";
	cout << list_of_clients[h].product << endl;
	cout << "Оценочная стоимость: ";
	cout << list_of_clients[h].cost << endl;
	cout << "Сумма залога: ";
	cout << list_of_clients[h].summ << endl;
	cout << "Срок хранеия: ";
	cout << list_of_clients[h].days << endl;
	cout << "Дата сдачи: " << d.day << "." << d.month << ".20" << d.year << " ";
}