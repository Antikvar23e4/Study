#include <iostream>
# define str_len 30                               
# define size 30  
using namespace std;

//. Реализовать функции ввода с клавиатуры, вывода на экран, удаления, поиска элементов. 
// Интерфейс пользователя осуще-ствить в виде меню.
// Личная библиотека. 
// Автор книги, название, издательство, раздел библиотеки 
// (специальная литература, хобби, домашнее хозяйство, беллетристика и т. д.), 
// происхождение (покупка, кража, подарок) и наличие книги в данный момент. 
// Выбор книг по году. Происхождение книги реализовать с помощью перечисления.
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
	cout << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для поиск по году" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
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
			cout << "1-вывод 1 строки" << endl;
			cout << "2-вывод всех строк" << endl;
			cin >> sw;
			if (sw == 1)
			{
				cout << "Номер выводимой строки " << endl;
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
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "НОМЕР СТРОКИ ";
		cout << current_size + 1;
		cout << endl << "Фамилия автора " << endl;
		cin >> list_of_books[current_size].author;
		cout << endl << "Название книги " << endl;
		cin >> list_of_books[current_size].name;
		cout << endl << "Год издания " << endl;
		cin >> list_of_books[current_size].year;
		cout << endl << "Раздел библиотеки " << endl;
		cin >> list_of_books[current_size].section;
		cout << endl << "Проихождение книги " << endl
			<< "(1) - куплена" << endl
			<< "(2) - украдена" << endl
			<< "(3) - подарена" << endl;
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
		cout << endl << "Наличие" << endl
			<< "(1) - есть" << endl
			<< "(0) - нет" << endl;
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
		cout << "Введено максимальное кол-во строк";
	cout << "Что дальше?" << endl;
	Menu();
	cin >> choice;
}
void del()
{
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			list_of_books[de1] = list_of_books[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			list_of_books[i] = bad;
	cout << "Что дальше?" << endl;
	Menu();
	cin >> choice;
}
void find()
{
	int year;
	cout << "Введите: " << endl;
	cout << "год выборки" << endl;
	cin >> year;

	for (int i = 0; i < current_size; i++)
	{
		if (list_of_books[i].year == year)
		{
			print(i);
		}
	}

	cout << "Что дальше?" << endl;
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
	cout << "Что дальше?" << endl;
	Menu();
	cin >> choice;
}
void print(int n)
{
	cout << "\n\nНОМЕР ";
	cout << n;
	cout << endl << "Фамилия автора " << endl;
	cout << list_of_books[n].author;
	cout << endl << "Название книги " << endl;
	cout << list_of_books[n].name;
	cout << endl << "Год издания " << endl;
	cout << list_of_books[n].year;
	cout << endl << "Раздел библиотеки" << endl;
	cout << list_of_books[n].section;
	cout << endl << "Происхождение книги " << endl;
	switch (list_of_books[n].origin)
	{
	case 1: cout << "куплена"; break;
		break;
	case 2: cout << "украдена"; break;
		break;
	case 3: cout << "подарена"; break;
		break;
	default:
		cout << "write 1 - 3";
		break;
	}
	cout << endl << "Наличие " << endl;
	if (list_of_books[n].availability.a)
	{
		cout << "Есть в наличии" << endl;
	}
	else
	{
		cout << "Нет в наличии" << endl;
	}
}
