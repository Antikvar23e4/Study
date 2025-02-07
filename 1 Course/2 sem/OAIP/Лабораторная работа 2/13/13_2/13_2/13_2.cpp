//Государство.
//Наименование, столица, численность населения, площадь, фамилия президента.
//Выбор государства по названию.
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
	cout << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для вывода записи(ей)" << endl;
	cout << "4-для поиска информации" << endl;
	cout << "0-для выхода" << endl;
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
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "Наименование: ";
		cin.ignore();
		cin.getline(govu.name, 50);
		strcpy_s(listOfGov[current_size].name, govu.name);
		cout << endl << "Столица: ";
		cin.getline(govu.capital, 50);
		strcpy_s(listOfGov[current_size].capital, govu.capital);
		cout << endl << "Площадь(км^2): ";
		cin >> govu.area;
		listOfGov[current_size].area = govu.area;
		cout << endl << "Численность населения(млн. чел.): ";
		cin >> govu.popularity;
		listOfGov[current_size].popularity = govu.popularity;
		cout << endl << "Имя президента: ";
		cin.ignore();
		cin.getline(govu.president, 50);
		strcpy_s(listOfGov[current_size].president, govu.president);
		current_size++;
	}
	else
	{
		cout << "Введено максимальное кол-во строк";
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
	cout << "Что вы хотите сделать дальше?." << endl;
	cin >> choice;
}

void del()
{
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;  cin >> d;
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

	cout << "Что вы хотите сделать дальше?." << endl;
	cin >> choice;
}
void out()
{
	int sw, n;
	cout << "1-вывод 1 строки" << endl;
	cout << "2-вывод всех строк" << endl;
	cin >> sw;

	if (sw == 1)
	{
		cout << "Номер выводимой строки " << endl;   cin >> n;  cout << endl;
		cout << endl << "\nНаименование      Столица        Площадь(км^2)        Численность населения(млн. чел.)         Имя президента\n";
		cout << listOfGov[n - 1].name << "\t   " << listOfGov[n - 1].capital << "\t       " << listOfGov[n - 1].area << "\t\t            " << listOfGov[n - 1].popularity << "\t\t            " << listOfGov[n - 1].president << endl;
	}
	if (sw == 2)
	{
		cout << endl << "\nНаименование      Столица        Площадь(км^2)        Численность населения(млн. чел.)         Имя президента\n";
		for (int i = 0; i < current_size; i++)
		{

			cout << listOfGov[i].name << "\t   " << listOfGov[i].capital << "\t       " << listOfGov[i].area << "\t\t            " << listOfGov[i].popularity << "\t\t            " << listOfGov[i].president << endl;
		}
	}
	cout << endl << endl;
	cout << "Что вы хотите сделать дальше?." << endl;
	cin >> choice;
}
void search()
{
	int choose; int none = 0; struct GOVERNMENT searching[1];
	printf("Введите номер необходимого вида поиска:\n");
	printf("1 - поиск по наименованию\n");
	cin >> choose;
	if (choose == 1)
	{
		printf("Введите наименование государства: ");
		cin.ignore();
		cin.getline(searching[0].name, 30);
		cout << endl << "\nНаименование      Столица        Площадь(км^2)        Численность населения(млн. чел.)         Имя президента\n";
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
			printf("Не было найдено ни одной записи\n");
		}
	}
	cout << "Что вы хотите сделать дальше?." << endl;
	cin >> choice;
}