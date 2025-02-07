//Вы работаете в компании, занимающейся оптово - розничной продажей различных товаров.
//Вашей задачей является отслеживание финансовой стороны работы компании.
//Деятельность Вашей компании организована следующим образом : Ваша компания торгует товарами из определенного спектра.
//Каждый из этих товаров характеризуется наименованием, оптовой ценой, розничной ценой и справочной информацией.
//В Вашу компанию обращаются покупатели.
//Для каждого из них Вы запоминаете в базе данных стандартные данные
//(наименование, адрес, телефон, контактное лицо) и составляете по каждой сделке документ, запоминая наряду с покупателем количество купленного им товара и дату покупки.
//Обычно покупатели в рамках одной сделки покупают не один товар, а сразу несколько.

//1^наименование, адрес, телефон, контактное лицо,кол-во купленных товаров, дата покупки
//2^наименованием, оптовой ценой, розничной ценой и справочной информацией
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MAX 30

int _stateMenu;
int _personalAccountMenu;
int _serviceAccountMenu;
int _productMenu;
bool _authorizationStatus = false;
int _serviceId = 0;
int _service1Id = 0;
char path[50] = "data.txt";
int _amountOfClients = 0;
int _amountOfService = 0;

struct Base
{
	string name;
	string adress;
	string phone_number;
	string fio;
	string kolvo;
	string data;
	int service_id;
}BaseList[30];

struct Service
{
	string name;
	int opt;
	string rozn;
	string description;
	int service1_id;
}ServiceList[30];

void Menu();
void PersonalAccount();
void PersonalAccountMenu();
void ProductList();
void ProductListMenu();
void ServiceAccountMenu();
void ServiceSearch(int);
void AddService(char name[]);
void InputFile(char name[]);
void RemoveFile(char name[]);
void ReadFile(char name[]);
void ClearFile(char name[]);
void AddClients(char name[]);
void ClientSearch(int);
bool Unique(int);
bool UniqueService(int);
void WriteStructure(char name[]);

int find_free(void)
{
	register int t;
	for (t = 0; BaseList[t].name[0] && t < MAX; ++t);
	if (t == MAX) return -1;
	return t;
}

int main()
{
	setlocale(LC_ALL, "rus");
	Menu();
	while (_stateMenu != 0) {

		switch (_stateMenu)
		{
		case 1:
		{
			system("cls");
			ProductListMenu();
			system("cls");
			Menu();
			break;
		}
		case 2:
		{
			system("cls");
			PersonalAccountMenu();
			system("cls");
			Menu();
			break;
		}
		case 3:
		{
			system("cls");
			ServiceAccountMenu();
			system("cls");
			Menu();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "Вы вышли из системы!" << endl;
			system("pause");
			system("cls");
			return 0;
			break;
		}

		default:
		{
			system("cls");
			cout << "Неверно введен номер действия!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
		}

	}
}

void Menu() {
	cout << "Выберите действие:" << endl
		<< "(1) Составление документов" << endl
		<< "(2) Зарегистрировать клиента" << endl
		<< "(3) Запись товаров" << endl
		<< "(4) Выход" << endl
		<< "Ваш выбор: ";
	cin >> _stateMenu;
}

void ProductList() {
	cout << "Выберите действие:" << endl
		<< "(1) Выход в главное меню" << endl
		<< "(2) Отсортировать (недоступно)" << endl
		<< "(3) Поиск по номеру" << endl
		<< "Ваш выбор: ";
	cin >> _productMenu;
}

void PersonalAccount() {
	cout << "Выберите действие:" << endl
		<< "(1) Выход в главное меню" << endl
		<< "(2) Список клиентов" << endl
		<< "(3) Просмотр личной информации клиента по его айди" << endl
		<< "(4) Очистить базу" << endl
		<< "(5) Удаление клиентской базы" << endl
		<< "(6) Добавление клиента" << endl
		<< "(7) Чтение данных из файла" << endl

		<< "Ваш выбор: ";
	cin >> _personalAccountMenu;
}

void ServicelAccount() {
	cout << "Выберите действие:" << endl
		<< "(1) Выход в главное меню" << endl
		<< "(2) Список товаров" << endl
		<< "(3) Просмотр товара по его айди" << endl
		<< "(4) Очистить базу" << endl
		<< "(5) Удаление базы товаров" << endl
		<< "(6) Добавление товара" << endl
		<< "Ваш выбор: ";
	cin >> _serviceAccountMenu;
}

void ServiceAccountMenu()
{
	cout << "Введите название файла" << endl;
	cin >> path;
	ifstream fin(path);
	if (fin.is_open())
	{
		_authorizationStatus = true;
	}
	else
	{
		AddService(path);
		_authorizationStatus = true;
	}
	fin.close();

	system("cls");
	ServicelAccount();
	while (_serviceAccountMenu != 1 && _authorizationStatus)
	{
		switch (_serviceAccountMenu)
		{
		case 2:
		{
			system("cls");
			ReadFile(path);
			system("pause");
			system("cls");
			ServicelAccount();
			break;
		}
		case 3:
		{
			system("cls");
			cout << "Введите идентификационный номер клиента ";
			int n;
			cin >> n;
			system("cls");
			ServiceSearch(n);
			system("pause");
			system("cls");
			ServicelAccount();
			break;
		}
		case 4:
		{
			system("cls");
			ClearFile(path);
			system("pause");
			system("cls");
			ServicelAccount();
			break;
		}
		case 5:
		{
			system("cls");
			RemoveFile(path);
			system("pause");
			system("cls");
			ServicelAccount();
			break;
		}
		case 6:
		{
			system("cls");
			AddService(path);
			system("pause");
			system("cls");
			ServicelAccount();
			break;
		}
		default:
		{
			system("cls");
			cout << "Неверно введен номер действия!" << endl;
			system("pause");
			system("cls");
			ServicelAccount();
			break;
		}
		}
	}
}

void PersonalAccountMenu()
{
	cout << "Введите название клиентской базы" << endl;
	cin >> path;
	ifstream fin(path);
	if (fin.is_open())
	{
		_authorizationStatus = true;
	}
	else
	{
		AddClients(path);
		_authorizationStatus = true;
	}
	fin.close();

	system("cls");
	PersonalAccount();
	while (_personalAccountMenu != 1 && _authorizationStatus)
	{
		switch (_personalAccountMenu)
		{
		case 2:
		{
			system("cls");
			ReadFile(path);
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		case 3:
		{
			system("cls");
			cout << "Введите идентификационный номер товара ";
			int n;
			cin >> n;
			system("cls");
			ClientSearch(n);
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		case 4:
		{
			system("cls");
			ClearFile(path);
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		case 5:
		{
			system("cls");
			RemoveFile(path);
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		case 6:
		{
			system("cls");
			AddClients(path);
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		case 7:
		{
			system("cls");
			WriteStructure(path);
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		default:
		{
			system("cls");
			cout << "Неверно введен номер действия!" << endl;
			system("pause");
			system("cls");
			PersonalAccount();
			break;
		}
		}
	}
}

void ProductListMenu()
{
	if (_authorizationStatus)
	{
		ProductList();
		while (_productMenu != 1)
		{
			switch (_productMenu)
			{
			case 2:
			{
				system("cls");
				cout << "Вы отсортировали записи!" << endl;
				system("pause");
				system("cls");
				ProductList();
				break;
			}
			case 3:
			{
				system("cls");
				cout << "Вы выбрали площадь!" << endl;
				system("pause");
				system("cls");
				ProductList();
				break;
			}
			default:
			{
				system("cls");
				cout << "Неверно введен номер действия!" << endl;
				system("pause");
				system("cls");
				ProductList();
				break;
			}
			}
		}
	}
	else
	{
		system("cls");
		cout << "Необходимо выбрать клиентскую базу для работы\n";
	}
}

void InputFile(char name[])
{

	ofstream fout(name, ios_base::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		system("cls");
		_serviceId = find_free();

		cout << "Введите данные для записи в файл:" << endl;

		cout << "Введите название:" << endl;
		getline(cin, BaseList[_serviceId].name);
		getline(cin, BaseList[_serviceId].name);
		fout << "Название:" << endl << BaseList[_serviceId].name << endl;

		cout << "Введите адрес:" << endl;
		getline(cin, BaseList[_serviceId].adress);
		fout << "Адрес:" << endl << BaseList[_serviceId].adress << endl;

		cout << "Введите телефон:" << endl;
		cin >> BaseList[_serviceId].phone_number;
		fout << "Телефон:" << endl << BaseList[_serviceId].phone_number << endl;
		
		cout << "Введите контактное лицо:" << endl;
		cin >> BaseList[_serviceId].fio;
		fout << "Контактное лицо:" << endl << BaseList[_serviceId].fio << endl;

		cout << "Введите колличество товара:" << endl;
		cin >> BaseList[_serviceId].kolvo;
		fout << "Колличество:" << endl  << BaseList[_serviceId].kolvo << endl;

		cout << "Введите дату покупки:" << endl;
		cin >> BaseList[_serviceId].data;
		fout << "Дата:" << endl << BaseList[_serviceId].data << endl;

		cout << "Введите уникальный номер:" << endl;
		int id;
		cin >> id;

		if (!Unique(id))
		{
			while (!Unique(id))
			{
				cout << "Номер не уникальный! Введите другой номер:" << endl;
				cin >> id;
			}
		}
		BaseList[_serviceId].service_id = id;
		fout << "Номер:" << endl << BaseList[_serviceId].service_id << endl;
		fout << "\n_____________________________________________\n";
	}
	fout.close();
	system("cls");
}

void InputFileService(char name[])
{

	ofstream fout(name, ios_base::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		system("cls");
		_serviceId = find_free();

		cout << "Введите данные для записи в файл:" << endl;

		cout << "Введите название товара:" << endl;
		getline(cin, ServiceList[_service1Id].name);
		getline(cin, ServiceList[_service1Id].name);
		fout << "Название товара:" << endl << ServiceList[_serviceId].name << endl;

		cout << "Введите розничную цену:" << endl;
		getline(cin, ServiceList[_service1Id].rozn);
		fout << "Розничная цена:" << endl << ServiceList[_serviceId].rozn << endl;

		cout << "Введите оптовую цену:" << endl;
		getline(cin, ServiceList[_service1Id].opt);
		fout << "Оптовая цена:" << endl << ServiceList[_serviceId].opt << endl;

		cout << "Введите описание товара:" << endl;
		cin >> ServiceList[_service1Id].description;
		fout << "Описание товара:" << endl << ServiceList[_service1Id].description << endl;

		cout << "Введите уникальный номер товара:" << endl;
		int id;
		cin >> id;

		if (!UniqueService(id))
		{
			while (!UniqueService(id))
			{
				cout << "Номер не уникальный! Введите другой номер:" << endl;
				cin >> id;
			}
		}
		ServiceList[_service1Id].service1_id = id;
		fout << "Номер:" << endl << ServiceList[_service1Id].service1_id << endl;
		fout << "\n_____________________________________________\n";
	}
	fout.close();
	system("cls");
}

void RemoveFile(char name[])
{
	system("cls");
	if (remove(name)) {
		cout << "Ошибка удаления файла!" << endl;
	}
	else
	{
		for (int i = 0; i < _amountOfClients; i++)
		{
			BaseList[i].name = "";
			BaseList[i].service_id = -1;
			BaseList[i].adress = "";
			BaseList[i].phone_number = "";
			BaseList[i].fio = "";
			BaseList[i].kolvo = "";
			BaseList[i].data = "";
		}
		_serviceId = -1;
		cout << "Учетная запись " << name << " успешно удалена!" << endl;
	}
}

void ReadFile(char name[])
{
	ifstream fin(name);
	if (!fin.is_open())
	{
		cout << "Файл не может быть открыт!\n";
	}
	else
	{
		system("cls");
		cout << "Данные из файла: \n";
		string data;
		while (!fin.eof())
		{
			data = "";
			getline(fin, data);
			cout << data << endl;
		}
	}
	fin.close();
}

void ClearFile(char name[])
{
	ofstream fout(name, ios_base::out | ios_base::trunc);
	system("cls");
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	{
		cout << "Данные " << name << " были удалены" << endl;
		_serviceId = -1;
		system("pause");
		system("cls");
	}
	fout.close();
}

void AddClients(char name[]) {
	cout << "Сколько клиентов вы хотите занести в базу?\n";
	int n = 0;
	cin >> n;
	_amountOfClients += n;
	for (int i = 0; i < n; i++)
	{
		InputFile(path);
	}
}

void AddService(char name[]) {
	cout << "Сколько товаров вы хотите занести в базу?\n";
	int n = 0;
	cin >> n;
	_amountOfService += n;
	for (int i = 0; i < n; i++)
	{
		InputFileService(path);
	}
}

void ClientSearch(int n)
{
	bool flag = false;
	for (int i = 0; i < MAX; i++)
	{
		if (BaseList[i].service_id == n)
		{
			cout << "Название:" << BaseList[i].name << endl;
			cout << "Адрес:" << BaseList[i].adress << endl;
			cout << "Телефон:" << BaseList[i].phone_number << endl;
			cout << "Контактное лицо:" << BaseList[i].fio << endl;
			cout << "Колличество товара:" << BaseList[i].kolvo << endl;
			cout << "Дата:" << BaseList[i].data << endl;
			flag = true;
		}
	}
	if (!flag)
	{
		cout << "Клиента с таким номером нет" << endl;
	}
}

void ServiceSearch(int n)
{
	bool flag = false;
	for (int i = 0; i < MAX; i++)
	{
		if (ServiceList[i].service1_id == n)
		{
			cout << "Название товара:" << ServiceList[i].name << endl;
			cout << "Оптовая цена:" << ServiceList[i].opt << endl;
			cout << "Розничная цена:" << ServiceList[i].rozn << endl;
			cout << "Описание:" << ServiceList[i].description << endl;
			flag = true;
		}
	}
	if (!flag)
	{
		cout << "Товара с таким номером нет" << endl;
	}
}

bool Unique(int n) {

	for (int i = 0; i < MAX; i++)
	{
		if (BaseList[i].service_id == n)
		{
			return false;
		}
	}
	return true;
}

bool UniqueService(int n) {

	for (int i = 0; i < MAX; i++)
	{
		if (ServiceList[i].service1_id == n)
		{
			return false;
		}
	}
	return true;
}

void WriteStructure(char name[])
{
	ifstream fin(name);
	if (!fin.is_open())
	{
		cout << "Файл не может быть открыт!\n";
	}
	else
	{
		if (_authorizationStatus)
		{
			string data;
			int i = 0;
			getline(fin, data);
			while (!fin.eof())
			{
				getline(fin, data);
				BaseList[i].name = data;
				getline(fin, data);
				getline(fin, data);
				BaseList[i].adress = data;
				getline(fin, data);
				getline(fin, data);
				BaseList[i].phone_number = data;
				getline(fin, data);
				getline(fin, data);
				BaseList[i].fio = data;
				getline(fin, data);
				getline(fin, data);
				BaseList[i].kolvo = data;
				getline(fin, data);
				getline(fin, data);
				BaseList[i].data= data;
				getline(fin, data);
				getline(fin, data);
				BaseList[i].service_id = stoi(data);
				getline(fin, data);
				getline(fin, data);
				getline(fin, data);
				i++;
			}
		}
		else
		{
			string data;
			int i = 0;
			getline(fin, data);
			while (!fin.eof())
			{
				getline(fin, data);
				ServiceList[i].name = stoi(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].opt= stoi(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].rozn = stoi(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].description = stof(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].service1_id = stoi(data);
				getline(fin, data);
				getline(fin, data);
				getline(fin, data);
				i++;
			}
		}
		fin.close();
	}
}