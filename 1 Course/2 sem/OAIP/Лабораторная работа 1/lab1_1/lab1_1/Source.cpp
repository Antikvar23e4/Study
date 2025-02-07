
//Вокзал. Номер поезда, пункт назначения, дни следования, время прибытия, время отправления. Выбор по пункту назначения.
//	1.ввод элементов структуры с клавиатуры;
//	2.вывод элементов структуры в консольное окно;
//	3.удаление заданной структурированной переменной;
//	4.поиск информации;
//	5.запись информации в файл;
//	6.чтение данных из файла.


#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;
#define size 2

struct Terminus
{
	int trainNumber;
	char destination[30];
	int travelDays;
	int arrivalTime;
	int departureTime;
};

Terminus arr[size];
int i = 0;
int oper;

void input();
void remove();
void output();
void search();
void infile();
void outfile();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	do {
		cout << "Что вы хотите сделать?\n";
		cout << "1 - Ввод данных в структуру\n";
		cout << "2 - Удаление данных из структуры\n";
		cout << "3 - Вывод данных на экран\n";
		cout << "4 - Поиск по пункту назначения\n";
		cout << "5 - Запись в файл\n";
		cout << "6 - Чтение из файла\n";
		cout << "7 - Для завершения работы\n";
		cin >> oper;
		switch (oper)
		{
		case 1:  input(); break;
		case 2:  remove(); break;
		case 3:  output(); break;
		case 4:  search(); break;
		case 5:  infile(); break;
		case 6:  outfile(); break;
		case 7: break;
		}
	} while (oper != 7);
	system("pause");
}

void input()
{
	while (i < size)
	{

		cout << "Введите информацию с  " << i + 1 << "-ого билета " << endl;
		cout << endl << "Номер поезда: ";
		cin >> arr[i].trainNumber;
		cout << endl << "Пункт назначения: ";
		cin >> arr[i].destination;
		cout << endl << "Дни следования : ";
		cin >> arr[i].travelDays;
		cout << endl << "Вряемя прибытия : ";
		cin >> arr[i].arrivalTime;
		cout << endl << "Время отправления : ";
		cin >> arr[i].departureTime;
		i++;
		cout << "-------------------------------------------" << endl;
	}

}

void output()
{
	if (i > 0)
	{
		int n;
		cout << "Введите номер элемента, который хотите вывести: "; cin >> n;
		n--;
		cout << "Номер поезда: " << arr[n].trainNumber << endl;
		cout << "Пункт назначения: " << arr[n].destination << endl;
		cout << "Дни следования : " << arr[n].travelDays << endl;
		cout << "Время прибытия : " << arr[n].arrivalTime << endl;
		cout << "Время отправления : " << arr[n].departureTime << endl;

	}
	cout << "-------------------------------------------" << endl;
}

void remove()
{
	if (i > 0)
	{
		int d;
		cout << "Номер записи, которую нужно удалить: "; cin >> d;
		for (int de1 = (d - 1); de1 < i; de1++)
			arr[de1] = arr[de1 + 1];
		i--;
		cout << "Запись удалена" << endl;
	}
	cout << "-------------------------------------------" << endl;
}

void search()
{
	string t, destination;
	if (i > 0)
	{
		cout << "Введите пункт назначения: "; cin >> t;
		for (int k = 0; k < i; k++)
		{
			destination = arr[k].destination;
			if (destination == t)
			{
				cout << "Номер поезда: " << arr[k].trainNumber << endl;
				cout << "Дни следования : " << arr[k].travelDays << endl;
				cout << "Время прибытия : " << arr[k].arrivalTime << endl;
				cout << "Время отправления : " << arr[k].departureTime << endl;

			}
		}
	}
	cout << "-------------------------------------------" << endl;
}

void infile() {
	ofstream fout("t.txt");
	for (int k = 0; k < i; k++) {
		fout << "\n" << arr[k].trainNumber;
		fout << "\n" << arr[k].destination;
		fout << "\n" << arr[k].travelDays;
		fout << "\n" << arr[k].arrivalTime;
		fout << "\n" << arr[k].departureTime;
		fout << "\n" << "-------------------------------------------" << endl;
	}
	fout.close();
}
void outfile() {
	char buff[50];
	ifstream fin("t.txt");
	do {
		fin.getline(buff, 50);
		cout << buff << endl;
		buff[0] = 0;
	} while (!fin.eof());

}
