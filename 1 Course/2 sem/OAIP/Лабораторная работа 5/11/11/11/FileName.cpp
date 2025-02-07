//Создать список, содержащий символы. Найти символ, равный введенному с клавиатуры, вывести этот символ и предыдущий.

#include <iostream>
#include <fstream>

using namespace std;

struct list
{
	char symbol;
	list* next;
};

void insert(list*& p, char value); //Добавление символа в начало списка
void printList(list* p);       //Вывод списка 
void toFile(list*& p);         //Запись в файл
void fromFile(list*& p);       //Считывание из файла
float del(list*& p, float value);
void search(list*& p);
int IsEmpty(list*);
void menu(void); //Вывод меню 



int main()
{
	setlocale(LC_CTYPE, "Russian");
	list* first = nullptr;
	int choice; char value; char prev;
	menu();    // вывести меню 
	cout << " ? ";
	cin >> choice;
	while (choice != 7)
	{
		switch (choice)
		{
		case 1:  	cout << "Введите символ ";
			cin >> value;
			insert(first, value);
			printList(first);
			break;
		case 2: printList(first);
			break;
		case 3: if (!IsEmpty(first)) // удалить число из списка
		{
			cout << "Введите удаляемый символ из списка ";
			cin >> value;
			if (del(first, value))
			{
				cout << "Удален символ " << value << endl;
				printList(first);
			}
			else
				cout << "Символ не найден" << endl;
		}
			  else
			cout << "Список пуст" << endl;
			break;
		case 4:
			search(first);
			break;
		case 5:    toFile(first);
			break;
		case 6:    fromFile(first);
			break;
		default:   cout << "Неправильный выбор" << endl;
			menu(); break;
		}
		cout << "?  ";
		cin >> choice;
	}
	return 0;
}

void insert(list*& p, char value) //Добавление символа в начало списка
{
	list* newP = new list;
	if (newP != NULL)     //есть ли место?  
	{
		newP->symbol = value;
		newP->next = p;
		p = newP;
	}
	else
		cout << "Операция добавления не выполнена" << endl;
}

void printList(list* p)  //Вывод списка 
{
	if (p == NULL)
		cout << "Список пуст" << endl;
	else
	{
		cout << "Список:" << endl;
		while (p != NULL)
		{
			cout << "-->" << p->symbol;
			p = p->next;
		}
		cout << "-->NULL" << endl;
	}
}

void toFile(list*& p)
{
	list* temp = p;
	list buf;
	ofstream frm("text.txt");
	if (frm.fail())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	while (temp)
	{
		buf = *temp;
		frm.write((char*)&buf, sizeof(list));
		temp = temp->next;
	}
	frm.close();
	cout << "Список записан в файл text.txt\n";
}

void fromFile(list*& p)          //Считывание из файла
{
	list buf, * first = nullptr;
	ifstream frm("text.txt");
	if (frm.fail())
	{
		cout << "\n Ошибка открытия файла";
		exit(1);
	}
	frm.read((char*)&buf, sizeof(list));
	while (!frm.eof())
	{
		insert(first, buf.symbol);
		cout << "-->" << buf.symbol;
		frm.read((char*)&buf, sizeof(list));
	}
	cout << "-->NULL" << endl;
	frm.close();
	p = first;
	cout << "\nСписок считан из файла text.txt\n";
}

float del(list*& p, float value)  // Удаление числа 
{
	list* previous, * current, * temp;
	if (value == p->symbol)
	{
		temp = p;
		p = p->next;    // отсоединить узел 
		delete temp;      //освободить отсоединенный узел 
		return value;
	}
	else
	{
		previous = p;
		current = p->next;
		while (current != NULL && current->symbol != value)
		{
			previous = current;
			current = current->next; // перейти к следующему 
		}
		if (current != NULL)
		{
			temp = current;
			previous->next = current->next;
			free(temp);
			return value;
		}
	}
	return 0;
}

void search(list*& p)
{
	char s, real, s1, s2;
	cout << "Введите символ" << endl;
	cin >> s;
	if (p == NULL) cout << "Список пуст" << endl;
	else
	{
		while (p != NULL)
		{
			real = p->symbol;
			p = p->next;
			if (p != NULL) {

				if (p->symbol == s) {
					s1 = s; s2 = real;
				};
			}

		}
		if (s1 == 0) cout << "Таких элементов нет";
		cout << "Найденный|предыдущий элементы : " << s1 << "|" << s2 << endl;
	}
}

int IsEmpty(list* p) //Список  пустой? (1-да, 0-нет) 
{
	return p == NULL;
}


void menu(void)     //Вывод меню 
{
	cout << "Сделайте выбор:" << endl;
	cout << " 1 - Ввод символа" << endl;
	cout << " 2 - Вывод списка" << endl;
	cout << " 3 - Удаление символа из списка" << endl;
	cout << " 4 - Поиск символа" << endl;
	cout << " 5 - Запись списка в файл" << endl;
	cout << " 6 - Чтение списка из файла" << endl;
	cout << " 7 - Выход" << endl;
}

