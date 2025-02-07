//Студенты.Ф.И.О., дата поступления, специальность, группа, факультет, средний балл.Выбор по среднему баллу.
//Дату поступления реализовать с помощью битового поля, факультет  с помощью перечисления.
#include <iostream>   
#include <windows.h>
# define str_len 50                             
# define size 30  

using namespace std;

void enter_new();
void del();
void out();
void search();

struct NOTE
{
	char name[str_len];
	char date[str_len];
	char speciality[str_len];
	char group[str_len];
	char ball[str_len];
	enum Efacultys Efaculty;
	
};

struct DateTime //Опишем структуру с битовыми полями
{
	unsigned short Day : 5;   //5 бит для дня
	unsigned short Month : 4; //4 для месяца
	unsigned short Year : 7;  //7 для года от 0 до 99
};

DateTime d;
struct NOTE listOfNot[size];
struct NOTE bad;
struct NOTE change[1];

int current_size = 0;
int choice;
int check = 0;
int current_check = 0, current_checkName = 0;
int buf = 0;
int facultet;

enum Efacultys
{
	TOV=1,
	HTIT,
	PIM,
	FIT,
} ;



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
	int i;      //И еще одну, в которую будет поступать ввод данных
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "ФИО: ";
		cin >> listOfNot[current_size].name;
		cout << endl << "Дата поступления: " << endl;;//Введем дату
		cout << "Введите день(1-31):" << '\t'; cin >> i; d.Day = i;
		cout << "Введите месяц (1-12):" << '\t'; cin >> i; d.Month = i;
		cout << "Введите год (00-99) :" << '\t'; cin >> i; d.Year = i;
		//И выведем их с показателем размера в памяти
		cout << endl << "Дата: " << d.Day << "." << d.Month << ".20" << d.Year << " ";
		cout << endl << "Специальность: ";
		cin >> listOfNot[current_size].speciality;
		cout << endl << "Группа: ";
		cin >> listOfNot[current_size].group;
		cout << endl << "Средний балл: ";
		cin >> listOfNot[current_size].ball;
		cout << "Введите ваш факультет (1 - ТОВ, 2 - ХТИТ, 3 - ПИМ, 4 - ФИТ ): " << endl;
		cin >> facultet;

		switch (facultet) {
		case 1:
			listOfNot[current_size].Efaculty = TOV;
			break;
		case 2:
			listOfNot[current_size].Efaculty = HTIT;
			break;
		case 3:
			listOfNot[current_size].Efaculty = PIM;
			break;
		case 4:
			listOfNot[current_size].Efaculty = FIT;
			break;
		}
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
			if (strcmp(listOfNot[i].name, listOfNot[i + 1].name) > 0)
			{
				change[1] = listOfNot[i];
				listOfNot[i] = listOfNot[i + 1];
				listOfNot[i + 1] = change[1];
				check++;
			}
		}
	} while (check > 0);
	cout << "Мы закончили." << endl;
	cin >> choice;
}



void del()
{
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			listOfNot[de1] = listOfNot[de1 + 1];
		current_size = current_size - 1;
		current_check--;
	}
	if (d == 99)
	{
		current_check--;
		for (int i = 0; i < size; i++)
			listOfNot[i] = bad;
	}

	cout << "Мы закончили." << endl;
	cin >> choice;
}

void out()
{
	int sw, n;
	char fucku[30];
	cout << "1-вывод 1 строки" << endl;
	cout << "2-вывод всех строк" << endl;
	cin >> sw;



	if (sw == 1)
	{
		cout << "Номер выводимой строки " << endl;   cin >> n;  cout << endl;
		cout << endl << "\nФИО      Дата поступления         Специальность        Группа        Средний балл        Факультет\n";
		cout << listOfNot[n - 1].name << "\t   "  << d.Day << "." << d.Month << ".20" << d.Year << " " << "\t       " << listOfNot[n - 1].speciality << "\t\t            " << listOfNot[n - 1].group << "\t\t            "<< listOfNot[n - 1].ball << "\t   ";
		switch (listOfNot[n-1].Efaculty) {
		case 1:
			cout << " ТОВ. " << endl;
			break;
		case 2:
			cout << "ХТИТ. " << endl;
			break;
		case 3:
			cout << "ПИМ. " << endl;
			break;
		case 4:
			cout << " ФИТ. " << endl;
			break;
		}
	}
	if (sw == 2)
	{
		cout << endl << "\nФИО      Дата поступления         Специальность        Группа        Средний балл        Факультет\n";
		for (int i = 0; i < current_size; i++)
		{

			cout << listOfNot[i].name << "\t   " << d.Day << "." << d.Month << ".20" << d.Year << " " << "\t       " << listOfNot[i].speciality << "\t\t            " << listOfNot[i].group  << "\t\t            " << listOfNot[i].ball << "\t   ";
			switch (listOfNot[i].Efaculty) {
			case 1:
				cout << " ТОВ. " << endl;
				break;
			case 2:
				cout << " ХТИТ. " << endl;
				break;
			case 3:
				cout << " ПИМ. " << endl;
				break;
			case 4:
				cout << "ФИТ. " << endl;
				break;
			}
		}
	}
	cout << endl << endl;
	cout << "Мы закончили." << endl;
	cin >> choice;
}

void search()
{
	int choose; int none = 0; struct NOTE searching[1]; char balle[str_len];
	printf("Введите номер необходимого вида поиска:\n");
	printf("1 - поиск по среднему баллу\n");
	cin >> choose;
	if (choose == 1)
	{
		cout << "Введите соедний балл: " << endl;
		cout << "Средний балл" << endl;
		cin >> balle;
		cout << endl << "\nФИО      Дата поступления         Специальность        Группа        Средний балл        Факультет\n";
		for (int i = 0; i < current_size; i++)
		{
			if (strcmp(listOfNot[i].ball, balle) == 0)
			{
				cout << listOfNot[i].name << "\t   " <<  d.Day << "." << d.Month << ".20" << d.Year << " " << "\t       " << listOfNot[i].speciality << "\t\t            " << listOfNot[i].group << " " << "\t       " << listOfNot[i].ball << "\t   " ;
				switch (listOfNot[current_size].Efaculty) {
				case 1:
					cout << "ТОВ. " << endl;
					break;
				case 2:
					cout << " ХТИТ. " << endl;
					break;
				case 3:
					cout << " ПИМ. " << endl;
					break;
				case 4:
					cout << "ФИТ. " << endl;
					break;
				}
			
			}
		}
	}
	cout << "Мы закончили." << endl;
	cin >> choice;
}

