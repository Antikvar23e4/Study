#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MAX 30
int _stateMenu;
int _sortMenu;
int _personalAccountMenu;
int _productMenu;
bool _authorizationStatus = false;
int _clientId = 0;
int _productId = 0;
char path[50] = "data.txt";
int _amountOfClients = 0;
int _amountOfService = 0;
struct Client {
	string name;
	string adress;
	string phone_number;
	string fio;
	string kolvo;
	string data;
	int client_id;
}ClientList[MAX];

struct Service
{
	int name;
	int opt;
	int rozn;
	int description;
	int service_id;
}ServiceList[MAX];

void Menu();
void PersonalAccount();
void PersonalAccountMenu(); 
void ProductListMenu();
void ProductListMenu();
bool UniqeProduct(int n);
void InputFile(char name[]);
void InputFileProduct(char name[]);
void RemoveFile(char name[]);
void ReadFile(char name[]);
void ClearFile(char name[]);
void AddClients(char name[]);
void RemoveFileProduct(char name[]);
void AddProduct(char name[]);
void ClientSearch(int);
void ProductSearch(int);
void WriteSttructure(char name[]);
bool Uniqe(int);
void SelectedDelete(int, int);
void FromStructureToFile(int n);
void BubbleSort();
void SelectionSort();
void InsertionSort();
void MergeSort();
void QuickSort(Service* a, int left, int right);
void merge(Service merged[], int lenD, Service L[], int lenL, Service R[], int lenR);
void MergeSort(Service data[], int lenD);
void Sort();
void SortMenu();
void Filter();
void InterpolatingSearch();
void BinarySearch();

void SelectedDelete(int index, int n)
{

	if (n == 1)// products
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ServiceList[i].service_id == index)
			{
				index = i;
				break;
			}
		}
		for (int i = index; i < _amountOfService; i++)
		{
			ServiceList[i] = ServiceList[i + 1];
		}
		_amountOfService--;
	}
	else
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ClientList[i].client_id == index)
			{
				index = i;
				break;
			}
		}
		for (int i = index; index < MAX - 1; i++)
		{
			ClientList[i] = ClientList[i + 1];
		}
	}
	FromStructureToFile(n);
}

void SelectedChange(int index, int n)
{

	if (n == 1)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ServiceList[i].service_id == index)
			{
				index = i;
				cout << "Введите данные для записи в файл:" << endl;
				cout << "Введите название товара:" << endl;
				cin >> ServiceList[index].name;

				cout << "Введите оптовую  цену:" << endl;
				cin >> ServiceList[index].opt;

				cout << " Введите розничную цену:" << endl;
				cin >> ServiceList[index].rozn;

				cout << "Введите описание товара:" << endl;
				cin >> ServiceList[index].description;

				cout << "Введите уникальный номер товара:" << endl;
				int id;
				cin >> id;

				if (!UniqeProduct(id))
				{
					while (!UniqeProduct(id))
					{
						cout << "Номер не уникальный! Введите другой номер:" << endl;
						cin >> id;
					}

				}
				ServiceList[index].service_id = id;
				break;
			}


		}

	}
	else
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ClientList[i].client_id == index)
			{
				index = i;
				break;
			}
		}
		cout << "Введите данные для записи в файл:" << endl;

		cout << "Введите название товара:" << endl;
		getline(cin, ClientList[index].name);
		getline(cin, ClientList[index].name);

		cout << "Введите адрес:" << endl;
		getline(cin, ClientList[index].adress);

		cout << "Введите телефон:" << endl;
		cin >> ClientList[index].phone_number;

		cout << "Введите контактное лицо:" << endl;
		cin >> ClientList[index].fio;

		cout << "Введите дату:" << endl;
		cin >> ClientList[index].data;
		
		cout << "Введите колличество:" << endl;
		cin >> ClientList[index].kolvo;

		cout << "Введите уникальный номер клиента:" << endl;
		int id;
		cin >> id;

		if (!Uniqe(id))
		{
			while (!Uniqe(id))
			{
				cout << "Номер не уникальный! Введите другой номер:" << endl;
				cin >> id;
			}

		}
		ClientList[index].client_id = id;

	}
	FromStructureToFile(n);
}
void FullDelete(int n)
{
	if (n == 1)
	{
		Service temp[MAX];
		for (int i = 0; i < MAX; i++)
		{
			ServiceList[i] = temp[i];
			_amountOfService = 0;
			ClearFile(path);
		}
	}
	else
	{
		Client temp[MAX];
		for (int i = 0; i < MAX; i++)
		{
			ClientList[i] = temp[i];
			ClearFile(path);
		}
	}

}

int find_free(void)
{
	register int t;

	for (t = 0; ClientList[t].name[0] && t < MAX; ++t);

	if (t == MAX) return -1; 
	return t;
}

int find_freeProduct(void)
{
	register int t;

	for (t = 0; ServiceList[t].name && t < MAX; ++t);

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
			cout << "Вы вышли из системы!" << endl;
			system("pause");
			system("cls");
			return 0;
			break;
		}
		case 4:
		{
			system("cls");
			SortMenu();
			system("pause");
			system("cls");
			Menu();
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
		<< "(1) Составление документов " << endl
		<< "(2) Зарегистрировать клиента" << endl
		<< "(3) Выход" << endl
		<< "(4) Сортировки" << endl
		<< "Ваш выбор: ";
	cin >> _stateMenu;
}

void Sort() {
	cout << "Выберите действие:" << endl
		<< "(1) Сортировка выбором " << endl
		<< "(2) Пузырьковая сортировка " << endl
		<< "(3) Сортировка вставками " << endl
		<< "(4) Сортировка слиянием " << endl
		<< "(5) Быстрая сортировка  " << endl
		<< "(6) Вывести базу данных " << endl
		<< "(7) Интерполирующий поиск по цене " << endl
		<< "(8) Бинарный поиск по индексу " << endl
		<< "(9) Выход в главное меню " << endl
		<< "Ваш выбор: ";
	cin >> _sortMenu;
}

void SortMenu()
{
	cout << "Введите название базы товаров" << endl;
	cin >> path;
	ifstream fin(path);
	if (!fin.is_open())
	{
		AddProduct(path);
	}
	fin.close();

	system("cls");
	Sort();
	while (_sortMenu != 9)
	{
		switch (_sortMenu)
		{
		case 1:
		{
			system("cls");
			SelectionSort();
			FromStructureToFile(1);
			cout << "Файл отсортирован!\n";
			system("pause"); 
			system("cls");
			Sort();
			break;
		}
		case 2:
		{
			system("cls");
			BubbleSort();
			FromStructureToFile(1);
			cout << "Файл отсортирован!\n";
			system("pause"); 
			system("cls");
			Sort();
			break;
		}
		case 3:
		{
			system("cls");
			InsertionSort();
			FromStructureToFile(1);
			cout << "Файл отсортирован!\n";
			system("pause"); 
			system("cls");
			Sort();
			break;
			break;
		}
		case 4:
		{
			system("cls");
			MergeSort(ServiceList, _amountOfService);
			FromStructureToFile(1);
			cout << "Файл отсортирован!\n";
			system("pause");
			system("cls");
			Sort();
			break;
		}
		case 5: {
			system("cls");
			QuickSort(ServiceList, 0, _amountOfService - 1);
			FromStructureToFile(1);
			cout << "Файл отсортирован!\n";
			system("pause"); 
			system("cls");
			Sort();
			break;
		}
		case 6:
		{
			system("cls");
			ReadFile(path);
			system("pause"); 
			system("cls");
			Sort();
			break;
		}
		case 7:
		{
			system("cls");
			BinarySearch();
			system("pause"); 
			system("cls");
			Sort();
			break;
		}
		case 8:
		{
			system("cls");
			BinarySearch();
			system("pause");
			system("cls");
			Sort();
			break;
		}
		default:
		{
			system("cls");
			cout << "Неверно введен номер действия!" << endl;
			system("pause");
			system("cls");
			Sort();
			break;
		}
		}
	}


}

void PersonalAccount() {
	cout << "Выберите действие:" << endl
		<< "(1) Выход в главное меню" << endl
		<< "(2) Список клиентов" << endl
		<< "(3) Просмотр личной информации клиента по его айди" << endl
		<< "(4) Очистить базу" << endl
		<< "(5) Удаление базы" << endl
		<< "(6) Добавление клиентов" << endl
		<< "(7) Фильтрация клиентов" << endl
		<< "Ваш выбор: ";
	cin >> _personalAccountMenu;
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
			cout << "Введите идентификационный номер клиента ";
			int n;
			cin >> n;
			system("cls");
			ClientSearch(n);
			WriteSttructure(path);
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
			WriteSttructure(path);
			system("pause"); 
			system("cls");
			PersonalAccount();
			break;
		}
		case 7:
		{
			system("cls");
			Filter();
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
	_authorizationStatus = false;

}

void ProductMenu() {
	cout << "Выберите действие:" << endl
		<< "(1) Выход в главное меню" << endl
		<< "(2) Вывести базу" << endl
		<< "(3) Удаление по айди" << endl
		<< "(4) Изменение по айди" << endl
		<< "(5) Поск по номеру" << endl
		<< "(6) Очистить базу" << endl
		<< "(7) Удаление клиентской базы" << endl
		<< "(8) Добавление товаров" << endl
		<< "Ваш выбор: ";
	cin >> _productMenu;
}

void ProductListMenu()
{
	cout << "Введите название базы товаров" << endl;
	cin >> path;
	ifstream fin(path);
	if (!fin.is_open())
	{
		AddProduct(path);
	}
	fin.close();

	system("cls");
	ProductMenu();
	while (_productMenu != 1)
	{
		switch (_productMenu)
		{
		case 2:
		{
			system("cls");
			ReadFile(path);
			system("pause"); 
			system("cls");
			ProductMenu();
			break;
		}
		case 3:
		{

			system("cls");
			cout << "Введите идентификационный номер товара ";
			int n;
			cin >> n;
			system("cls");
			SelectedDelete(n, 1);
			system("pause"); 
			system("cls");
			ProductMenu();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "Введите идентификационный номер товара ";
			int n;
			cin >> n;
			system("cls");
			SelectedChange(n, 1);
			system("pause"); 
			system("cls");
			ProductMenu();
			break;
		}
		case 5:
		{

			system("cls");
			cout << "Введите идентификационный номер товара ";
			int n;
			cin >> n;
			system("cls");
			ProductSearch(n);
			WriteSttructure(path);
			system("pause"); 
			system("cls");
			ProductMenu();
			break;
		}
		case 6:
		{
			system("cls");
			ClearFile(path);
			_amountOfService = 0;
			system("pause");
			system("cls");
			ProductMenu();
			break;
		}
		case 7:
		{
			system("cls");
			RemoveFileProduct(path);
			_amountOfService = 0;
			system("pause"); 
			system("cls");
			ProductMenu();
			break;
		}
		case 8:
		{
			system("cls");
			AddProduct(path);
			WriteSttructure(path);
			system("pause"); 
			system("cls");
			ProductMenu();
			break;
		}
		default:
		{
			system("cls");
			cout << "Неверно введен номер действия!" << endl;
			system("pause");
			system("cls");
			ProductMenu();
			break;
		}
		}
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
		_clientId = find_free();

		cout << "Введите данные для записи в файл:" << endl;

		cout << "Введите название:" << endl;
		getline(cin, ClientList[_clientId].name);
		getline(cin, ClientList[_clientId].name);
		fout << "Название:" << endl << ClientList[_clientId].name << endl;

		cout << "Введите адрес:" << endl;
		getline(cin, ClientList[_clientId].adress);
		fout << "Адрес:" << endl << ClientList[_clientId].adress << endl;

		cout << "Введите телефон:" << endl;
		cin >> ClientList[_clientId].phone_number;
		fout << "Телефон:" << endl << ClientList[_clientId].phone_number << endl;

		cout << "Введите контактное лицо:" << endl;
		cin >> ClientList[_clientId].fio;
		fout << "Контактное лицо:" << endl << ClientList[_clientId].fio << endl;

		cout << "Введите колличество товара:" << endl;
		cin >> ClientList[_clientId].kolvo;
		fout << "Колличество:" << endl << ClientList[_clientId].kolvo << endl;

		cout << "Введите дату покупки:" << endl;
		cin >> ClientList[_clientId].data;
		fout << "Дата:" << endl << ClientList[_clientId].data << endl;

		cout << "Введите уникальный номер:" << endl;
		int id;
		cin >> id;

		if (!Uniqe(id))
		{
			while (!Uniqe(id))
			{
				cout << "Номер не уникальный! Введите другой номер:" << endl;
				cin >> id;
			}
		}
		ClientList[_clientId].client_id = id;
		fout << "Номер:" << endl << ClientList[_clientId].client_id << endl;
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
			ClientList[i].name = "";
			ClientList[i].client_id = -1;
			ClientList[i].adress = "";
			ClientList[i].phone_number = "";
			ClientList[i].fio = "";
			ClientList[i].kolvo = "";
			ClientList[i].data = "";
		}
		_clientId = 0;
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
		int k = 0;

		while (!fin.eof())
		{
			k++;
			data = "";
			getline(fin, data);
			cout << data;
			if (k % 2 == 0)
			{
				cout << endl;
			}
		}

	}
	fin.close();
	WriteSttructure(name);
}

void WriteSttructure(char name[])
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
				ClientList[i].name = data;
				getline(fin, data);
				getline(fin, data);
				ClientList[i].adress = data;
				getline(fin, data);
				getline(fin, data);
				ClientList[i].phone_number = data;
				getline(fin, data);
				getline(fin, data);
				ClientList[i].fio = data;
				getline(fin, data);
				getline(fin, data);
				ClientList[i].kolvo = data;
				getline(fin, data);
				getline(fin, data);
				ClientList[i].data = data;
				getline(fin, data);
				getline(fin, data);
				ClientList[i].client_id = stoi(data);
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
				ServiceList[i].opt = stoi(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].rozn = stoi(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].description = stoi(data);
				getline(fin, data);
				getline(fin, data);
				ServiceList[i].service_id = stoi(data);
				getline(fin, data);
				getline(fin, data);
				getline(fin, data);
				i++;
			}
		}
		fin.close();
	}
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
		_clientId = 0;
		_productId = 0;
		for (int i = 0; i < MAX; i++)
		{
			ServiceList[i].name = -1;
			ServiceList[i].opt = -1;
			ServiceList[i].rozn = -1;
			ServiceList[i].description = -1;
			ServiceList[i].service_id = -1;

		}
		_productId = -1;
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

void ClientSearch(int n)
{
	bool flag = false;
	for (int i = 0; i < MAX; i++)
	{
		if (ClientList[i].client_id == n)
		{
			cout << "Название:" << ClientList[i].name << endl;
			cout << "Адрес:" << ClientList[i].adress << endl;
			cout << "Телефон:" << ClientList[i].phone_number << endl;
			cout << "Контактное лицо:" << ClientList[i].fio << endl;
			cout << "Колличество товара:" << ClientList[i].kolvo << endl;
			cout << "Дата:" << ClientList[i].data << endl;
			flag = true;
		}
	}
	if (!flag)
	{
		cout << "Клиента с таким номером нет" << endl;
	}
}

bool Uniqe(int n) {

	for (int i = 0; i < MAX; i++)
	{
		if (ClientList[i].client_id == n)
		{
			return false;
		}

	}
	return true;
}

bool UniqeProduct(int n) {

	for (int i = 0; i < MAX; i++)
	{
		if (ServiceList[i].service_id == n)
		{
			return false;
		}

	}
	return true;
}

void AddProduct(char name[])
{
	cout << "Сколько продуктов вы хотите занести в базу?\n";
	int n = 0;
	cin >> n;
	_amountOfService += n;
	for (int i = 0; i < n; i++)
	{
		InputFileProduct(path);
	}
}

void InputFileProduct(char name[])
{
	ofstream fout(name, ios_base::app); 
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		system("cls");
		_productId = find_freeProduct();

		cout << "Введите данные для записи в файл:" << endl;

		cout << "Введите название товара:" << endl;
		cin >> ServiceList[_productId].name;
		fout << "Название товара:\n" << ServiceList[_productId].name << endl;

		cout << "Введите оптовую цену:" << endl;
		cin >> ServiceList[_productId].opt;
		fout << "Оптовая цена:\n" << ServiceList[_productId].opt << endl;

		cout << "Введите розничную цену:" << endl;
		cin >> ServiceList[_productId].rozn;
		fout << "Розничная цена:\n" << ServiceList[_productId].rozn << endl;

		cout << "Введите описание товара:" << endl;
		cin >> ServiceList[_productId].description;
		fout << "Описание товара:\n" << ServiceList[_productId].description << endl;

		cout << "Введите уникальный номер продукта:" << endl;
		int id;
		cin >> id;

		if (!UniqeProduct(id))
		{
			while (!UniqeProduct(id))
			{
				cout << "Номер не уникальный! Введите другой номер:" << endl;
				cin >> id;
			}

		}

		ServiceList[_productId].service_id = id;
		fout << "номер продукта:\n" << ServiceList[_productId].service_id << endl;
		fout << "\n_____________________________________________\n";

	}
	fout.close();
	system("cls");
}

void ProductSearch(int n)
{
	bool flag = false;
	for (int i = 0; i < MAX; i++)
	{
		if (ServiceList[i].service_id == n)
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

void RemoveFileProduct(char name[])
{
	system("cls");
	if (remove(name)) {
		cout << "Ошибка удаления файла!" << endl;
	}
	else
	{
		for (int i = 0; i < _amountOfService; i++)
		{
			ServiceList[i].name = -1;
			ServiceList[i].opt = -1;
			ServiceList[i].rozn = -1;
			ServiceList[i].description = -1;
			ServiceList[i].service_id = -1;

		}
		_productId = -1;
		cout << "Учетная запись " << name << " успешно удалена!" << endl;
	}
	_amountOfService = 0;
}

void FromStructureToFile(int n)
{
	if (n == 1)//product
	{
		ofstream fout(path, ios_base::out | ios_base::trunc);
		system("cls");
		if (!fout.is_open())
		{
			cout << "Ошибка открытия файла!" << endl;
		}
		{
			for (int i = 0; i < _amountOfService; i++)
			{

				fout << "Название товара:\n" << ServiceList[i].name << endl;
				fout << "Оптовая цена:\n" << ServiceList[i].opt << endl;
				fout << "Розничная цена:\n" << ServiceList[i].rozn << endl;
				fout << "Описание товара:\n" << ServiceList[i].description << endl;
				fout << "Номер товара:\n" << ServiceList[i].service_id << endl;
				fout << "\n_____________________________________________\n";
			}
		}
		fout.close();

	}
	else
	{
		ofstream fout(path, ios_base::out | ios_base::trunc);
		if (!fout.is_open())
		{
			cout << "Ошибка открытия файла!" << endl;
		}
		else
		{
			for (int i = 0; i < MAX; i++)
			{

				fout << "Название :\n" << ClientList[i].name << endl;
				fout << "Адрес:\n" << ClientList[i].adress << endl;
				fout << "Телефон:\n" << ClientList[i].phone_number << endl;
				fout << "Контактное лицо:\n" << ClientList[i].fio << endl;
				fout << "Колличество товара:\n" << ClientList[i].kolvo << endl;
				fout << "Дата:\n" << ClientList[i].data << endl;
				fout << "Номер клиента:\n" << ClientList[i].client_id << endl;
				fout << "\n_____________________________________________\n";

			}



		}
		fout.close();
	}
}

void SelectionSort()
{
	int n = _amountOfService;
	for (int i = 0; i < n - 1; i++) {
		int min_idx = i;

		for (int j = i + 1; j < n; j++) {
			if (ServiceList[j].opt < ServiceList[min_idx].opt) {
				min_idx = j;
			}
		}

		if (min_idx != i) {
			swap(ServiceList[i], ServiceList[min_idx]);
		}
	}
}

void BubbleSort()
{
	int n = _amountOfService;
	bool swapped;

	for (int i = 0; i < n - 1; i++) {
		swapped = false;

		for (int j = 0; j < n - i - 1; j++) {
			if (ServiceList[j].opt > ServiceList[j + 1].opt) {
				swap(ServiceList[j], ServiceList[j + 1]);
				swapped = true;
			}
		}

		if (!swapped) {
			break;
		}
	}
}

void InsertionSort()
{
	int n = _amountOfService;

	for (int i = 1; i < n; i++) {
		Service key = ServiceList[i];
		int j = i - 1;

		while (j >= 0 && ServiceList[j].opt > key.opt) {
			ServiceList[j + 1] = ServiceList[j];
			j--;
		}

		ServiceList[j + 1] = key;
	}
}

void MergeSort(Service data[], int lenD)
{
	if (lenD > 1) {
		int middle = lenD / 2;
		int rem = lenD - middle;
		Service* L = new Service[middle];
		Service* R = new Service[rem];
		for (int i = 0; i < lenD; i++) {
			if (i < middle) {
				L[i] = data[i];
			}
			else {
				R[i - middle] = data[i];
			}
		}
		MergeSort(L, middle);
		MergeSort(R, rem);
		merge(data, lenD, L, middle, R, rem);
	}
}

void merge(Service merged[], int lenD, Service L[], int lenL, Service R[], int lenR) {
	int i = 0;
	int j = 0;
	while (i < lenL || j < lenR) {
		if (i < lenL & j < lenR) {
			if (L[i].opt <= R[j].opt) {
				merged[i + j] = L[i];
				i++;
			}
			else {
				merged[i + j] = R[j];
				j++;
			}
		}
		else if (i < lenL) {
			merged[i + j] = L[i];
			i++;
		}
		else if (j < lenR) {
			merged[i + j] = R[j];
			j++;
		}
	}
}

void QuickSort(Service* a, int left, int right)
{
	int	l_hold = left, 
		r_hold = right; 
	Service pivot;
	pivot = a[left]; 
	while (left < right) // пока границы не сомкнутся
	{
		while ((a[right].opt >= pivot.opt) && (left < right))
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			a[left] = a[right]; // перемещаем элемент [right] на место разрешающего
			left++; // сдвигаем левую границу вправо
		}
		while ((a[left].opt <= pivot.opt) && (left < right))
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		if (left != right) // если границы не сомкнулись
		{
			a[right] = a[left]; // перемещаем элемент [left] на место [right]
			right--; // сдвигаем правую границу вправо
		}
	}
	a[left] = pivot; // ставим разрешающий элемент на место
	//	pivot = left;
		//left = l_hold;
		//right = r_hold;
	if (l_hold < left) // Рекурсивно вызываем сортировку для левой и правой части массива
		QuickSort(a, l_hold, left - 1);
	if (r_hold > left)
		QuickSort(a, left + 1, r_hold);
}

void Filter()
{
	string str;
	cout << "Введите подстроку, по которой пройдет фильтрация\n";
	cin >> str;
	system("cls");
	for (int i = 0; i < _amountOfClients; i++)
	{
		size_t pos = ClientList[i].name.find(str);
		if (pos != std::string::npos)
		{
			cout << "Название: " << ClientList[i].name << endl;
			cout << "Адрес: " << ClientList[i].adress << endl;
			cout << "Телефон: " << ClientList[i].phone_number << endl;
			cout << "Контактное лицо: " << ClientList[i].fio << endl;
			cout << "Колличество: " << ClientList[i].kolvo << endl;
			cout << "Дата: " << ClientList[i].data << endl;
			cout << "\n_____________________________________________\n";
		}
	}

}

void InterpolatingSearch()
{

	int x = 0; //Текущая позиция массива, с которым сравнивается искомое
	int a = 0; //Левая граница области, где ведется поиск
	int b = _amountOfService; //Правая граница области, где ведется поиск
	cout << "Значение цены, которое нужно найти\n";
	int WhatFind; //Значение, которое нужно найти
	cin >> WhatFind;
	system("cls");
	bool found; //Переменка-флаг, принимающая True если искомое найдено

	for (found = false; (ServiceList[a].opt < WhatFind) && (ServiceList[b].opt > WhatFind) && !found; )
	{
		//Вычисление интерполяцией следующего элемента, который будет сравниваться с искомым
		x = a + ((WhatFind - ServiceList[a].opt) * (b - a)) / (ServiceList[b].opt - ServiceList[a].opt);
		//Получение новых границ области, если искомое не найдено
		if (ServiceList[x].opt < WhatFind)
			a = x + 1;
		else if (ServiceList[x].opt > WhatFind)
			b = x - 1;
		else
		{
			found = true;
			cout << "Название: " << ServiceList[x].name << endl;
			cout << "Оптовая цена: " << ServiceList[x].opt << endl;
			cout << "Розничная цена: " << ServiceList[x].rozn << endl;
			cout << "Описание: " << ServiceList[x].description << endl;
			cout << "\n_____________________________________________\n";

		}

	}


	if (ServiceList[a].opt == WhatFind)
	{
		cout << "Название: " << ServiceList[a].name << endl;
		cout << "Оптовая цена: " << ServiceList[a].opt << endl;
		cout << "Розничная цена: " << ServiceList[a].rozn << endl;
		cout << "Описание: " << ServiceList[a].description << endl;
		cout << "\n_____________________________________________\n";
	}
	else if (ServiceList[b].opt == WhatFind)
	{
		cout << "Название: " << ServiceList[b].name << endl;
		cout << "Оптовая цена: " << ServiceList[b].opt << endl;
		cout << "Розничная цена: " << ServiceList[b].rozn << endl;
		cout << "Описание: " << ServiceList[b].description << endl;
		cout << "\n_____________________________________________\n";
	}
	else
		cout << "Извините, товар не был найден." << endl;


}

void BinarySearch() {
	int n = _amountOfService;
	for (int i = 0; i < n - 1; i++) {
		int min_idx = i;

		for (int j = i + 1; j < n; j++) {
			if (ServiceList[j].service_id < ServiceList[min_idx].service_id) {
				min_idx = j;
			}
		}

		if (min_idx != i) {
			swap(ServiceList[i], ServiceList[min_idx]);
		}
	}

	int key;
	cout << "Введите индекс искомого элемента\n";
	cin >> key;
	system("cls");
	int midd = 0, left = 0, right = n;
	while (1)
	{
		midd = (left + right) / 2;

		if (key < ServiceList[midd].service_id)       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (key > ServiceList[midd].service_id)  // если искомое больше значения в ячейке
			left = midd + 1;	   // смещаем левую границу поиска
		else                       // иначе (значения равны)
		{
			cout << "Название: " << ServiceList[midd].name << endl;
			cout << "Оптовая цена: " << ServiceList[midd].opt << endl;
			cout << "Розничная цена: " << ServiceList[midd].rozn << endl;
			cout << "Описание: " << ServiceList[midd].description << endl;
			cout << "\n_____________________________________________\n";
			break;           // функция возвращает индекс ячейки
		}
		if (left > right)          // если границы сомкнулись 

		{
			cout << "Элемент не найден\n";
			break;
		}

	}
}