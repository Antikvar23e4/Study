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
				cout << "������� ������ ��� ������ � ����:" << endl;
				cout << "������� �������� ������:" << endl;
				cin >> ServiceList[index].name;

				cout << "������� �������  ����:" << endl;
				cin >> ServiceList[index].opt;

				cout << " ������� ��������� ����:" << endl;
				cin >> ServiceList[index].rozn;

				cout << "������� �������� ������:" << endl;
				cin >> ServiceList[index].description;

				cout << "������� ���������� ����� ������:" << endl;
				int id;
				cin >> id;

				if (!UniqeProduct(id))
				{
					while (!UniqeProduct(id))
					{
						cout << "����� �� ����������! ������� ������ �����:" << endl;
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
		cout << "������� ������ ��� ������ � ����:" << endl;

		cout << "������� �������� ������:" << endl;
		getline(cin, ClientList[index].name);
		getline(cin, ClientList[index].name);

		cout << "������� �����:" << endl;
		getline(cin, ClientList[index].adress);

		cout << "������� �������:" << endl;
		cin >> ClientList[index].phone_number;

		cout << "������� ���������� ����:" << endl;
		cin >> ClientList[index].fio;

		cout << "������� ����:" << endl;
		cin >> ClientList[index].data;
		
		cout << "������� �����������:" << endl;
		cin >> ClientList[index].kolvo;

		cout << "������� ���������� ����� �������:" << endl;
		int id;
		cin >> id;

		if (!Uniqe(id))
		{
			while (!Uniqe(id))
			{
				cout << "����� �� ����������! ������� ������ �����:" << endl;
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
			cout << "�� ����� �� �������!" << endl;
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
			cout << "������� ������ ����� ��������!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
		}

	}
}

void Menu() {
	cout << "�������� ��������:" << endl
		<< "(1) ����������� ���������� " << endl
		<< "(2) ���������������� �������" << endl
		<< "(3) �����" << endl
		<< "(4) ����������" << endl
		<< "��� �����: ";
	cin >> _stateMenu;
}

void Sort() {
	cout << "�������� ��������:" << endl
		<< "(1) ���������� ������� " << endl
		<< "(2) ����������� ���������� " << endl
		<< "(3) ���������� ��������� " << endl
		<< "(4) ���������� �������� " << endl
		<< "(5) ������� ����������  " << endl
		<< "(6) ������� ���� ������ " << endl
		<< "(7) ��������������� ����� �� ���� " << endl
		<< "(8) �������� ����� �� ������� " << endl
		<< "(9) ����� � ������� ���� " << endl
		<< "��� �����: ";
	cin >> _sortMenu;
}

void SortMenu()
{
	cout << "������� �������� ���� �������" << endl;
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
			cout << "���� ������������!\n";
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
			cout << "���� ������������!\n";
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
			cout << "���� ������������!\n";
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
			cout << "���� ������������!\n";
			system("pause");
			system("cls");
			Sort();
			break;
		}
		case 5: {
			system("cls");
			QuickSort(ServiceList, 0, _amountOfService - 1);
			FromStructureToFile(1);
			cout << "���� ������������!\n";
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
			cout << "������� ������ ����� ��������!" << endl;
			system("pause");
			system("cls");
			Sort();
			break;
		}
		}
	}


}

void PersonalAccount() {
	cout << "�������� ��������:" << endl
		<< "(1) ����� � ������� ����" << endl
		<< "(2) ������ ��������" << endl
		<< "(3) �������� ������ ���������� ������� �� ��� ����" << endl
		<< "(4) �������� ����" << endl
		<< "(5) �������� ����" << endl
		<< "(6) ���������� ��������" << endl
		<< "(7) ���������� ��������" << endl
		<< "��� �����: ";
	cin >> _personalAccountMenu;
}

void PersonalAccountMenu()
{
	cout << "������� �������� ���������� ����" << endl;
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
			cout << "������� ����������������� ����� ������� ";
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
			cout << "������� ������ ����� ��������!" << endl;
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
	cout << "�������� ��������:" << endl
		<< "(1) ����� � ������� ����" << endl
		<< "(2) ������� ����" << endl
		<< "(3) �������� �� ����" << endl
		<< "(4) ��������� �� ����" << endl
		<< "(5) ���� �� ������" << endl
		<< "(6) �������� ����" << endl
		<< "(7) �������� ���������� ����" << endl
		<< "(8) ���������� �������" << endl
		<< "��� �����: ";
	cin >> _productMenu;
}

void ProductListMenu()
{
	cout << "������� �������� ���� �������" << endl;
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
			cout << "������� ����������������� ����� ������ ";
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
			cout << "������� ����������������� ����� ������ ";
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
			cout << "������� ����������������� ����� ������ ";
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
			cout << "������� ������ ����� ��������!" << endl;
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
		cout << "������ �������� �����!" << endl;
	}
	else
	{
		system("cls");
		_clientId = find_free();

		cout << "������� ������ ��� ������ � ����:" << endl;

		cout << "������� ��������:" << endl;
		getline(cin, ClientList[_clientId].name);
		getline(cin, ClientList[_clientId].name);
		fout << "��������:" << endl << ClientList[_clientId].name << endl;

		cout << "������� �����:" << endl;
		getline(cin, ClientList[_clientId].adress);
		fout << "�����:" << endl << ClientList[_clientId].adress << endl;

		cout << "������� �������:" << endl;
		cin >> ClientList[_clientId].phone_number;
		fout << "�������:" << endl << ClientList[_clientId].phone_number << endl;

		cout << "������� ���������� ����:" << endl;
		cin >> ClientList[_clientId].fio;
		fout << "���������� ����:" << endl << ClientList[_clientId].fio << endl;

		cout << "������� ����������� ������:" << endl;
		cin >> ClientList[_clientId].kolvo;
		fout << "�����������:" << endl << ClientList[_clientId].kolvo << endl;

		cout << "������� ���� �������:" << endl;
		cin >> ClientList[_clientId].data;
		fout << "����:" << endl << ClientList[_clientId].data << endl;

		cout << "������� ���������� �����:" << endl;
		int id;
		cin >> id;

		if (!Uniqe(id))
		{
			while (!Uniqe(id))
			{
				cout << "����� �� ����������! ������� ������ �����:" << endl;
				cin >> id;
			}
		}
		ClientList[_clientId].client_id = id;
		fout << "�����:" << endl << ClientList[_clientId].client_id << endl;
		fout << "\n_____________________________________________\n";
	}
	fout.close();
	system("cls");
}
void RemoveFile(char name[])
{
	system("cls");
	if (remove(name)) {
		cout << "������ �������� �����!" << endl;
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
		cout << "������� ������ " << name << " ������� �������!" << endl;
	}

}

void ReadFile(char name[])
{
	ifstream fin(name);
	if (!fin.is_open())
	{
		cout << "���� �� ����� ���� ������!\n";
	}
	else
	{
		system("cls");
		cout << "������ �� �����: \n";
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
		cout << "���� �� ����� ���� ������!\n";
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
		cout << "������ �������� �����!" << endl;
	}
	{
		cout << "������ " << name << " ���� �������" << endl;
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

	cout << "������� �������� �� ������ ������� � ����?\n";
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
			cout << "��������:" << ClientList[i].name << endl;
			cout << "�����:" << ClientList[i].adress << endl;
			cout << "�������:" << ClientList[i].phone_number << endl;
			cout << "���������� ����:" << ClientList[i].fio << endl;
			cout << "����������� ������:" << ClientList[i].kolvo << endl;
			cout << "����:" << ClientList[i].data << endl;
			flag = true;
		}
	}
	if (!flag)
	{
		cout << "������� � ����� ������� ���" << endl;
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
	cout << "������� ��������� �� ������ ������� � ����?\n";
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
		cout << "������ �������� �����!" << endl;
	}
	else
	{
		system("cls");
		_productId = find_freeProduct();

		cout << "������� ������ ��� ������ � ����:" << endl;

		cout << "������� �������� ������:" << endl;
		cin >> ServiceList[_productId].name;
		fout << "�������� ������:\n" << ServiceList[_productId].name << endl;

		cout << "������� ������� ����:" << endl;
		cin >> ServiceList[_productId].opt;
		fout << "������� ����:\n" << ServiceList[_productId].opt << endl;

		cout << "������� ��������� ����:" << endl;
		cin >> ServiceList[_productId].rozn;
		fout << "��������� ����:\n" << ServiceList[_productId].rozn << endl;

		cout << "������� �������� ������:" << endl;
		cin >> ServiceList[_productId].description;
		fout << "�������� ������:\n" << ServiceList[_productId].description << endl;

		cout << "������� ���������� ����� ��������:" << endl;
		int id;
		cin >> id;

		if (!UniqeProduct(id))
		{
			while (!UniqeProduct(id))
			{
				cout << "����� �� ����������! ������� ������ �����:" << endl;
				cin >> id;
			}

		}

		ServiceList[_productId].service_id = id;
		fout << "����� ��������:\n" << ServiceList[_productId].service_id << endl;
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
			cout << "�������� ������:" << ServiceList[i].name << endl;
			cout << "������� ����:" << ServiceList[i].opt << endl;
			cout << "��������� ����:" << ServiceList[i].rozn << endl;
			cout << "��������:" << ServiceList[i].description << endl;
			flag = true;
		}
	}
	if (!flag)
	{
		cout << "������ � ����� ������� ���" << endl;
	}
}

void RemoveFileProduct(char name[])
{
	system("cls");
	if (remove(name)) {
		cout << "������ �������� �����!" << endl;
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
		cout << "������� ������ " << name << " ������� �������!" << endl;
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
			cout << "������ �������� �����!" << endl;
		}
		{
			for (int i = 0; i < _amountOfService; i++)
			{

				fout << "�������� ������:\n" << ServiceList[i].name << endl;
				fout << "������� ����:\n" << ServiceList[i].opt << endl;
				fout << "��������� ����:\n" << ServiceList[i].rozn << endl;
				fout << "�������� ������:\n" << ServiceList[i].description << endl;
				fout << "����� ������:\n" << ServiceList[i].service_id << endl;
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
			cout << "������ �������� �����!" << endl;
		}
		else
		{
			for (int i = 0; i < MAX; i++)
			{

				fout << "�������� :\n" << ClientList[i].name << endl;
				fout << "�����:\n" << ClientList[i].adress << endl;
				fout << "�������:\n" << ClientList[i].phone_number << endl;
				fout << "���������� ����:\n" << ClientList[i].fio << endl;
				fout << "����������� ������:\n" << ClientList[i].kolvo << endl;
				fout << "����:\n" << ClientList[i].data << endl;
				fout << "����� �������:\n" << ClientList[i].client_id << endl;
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
	while (left < right) // ���� ������� �� ���������
	{
		while ((a[right].opt >= pivot.opt) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			a[left] = a[right]; // ���������� ������� [right] �� ����� ������������
			left++; // �������� ����� ������� ������
		}
		while ((a[left].opt <= pivot.opt) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			a[right] = a[left]; // ���������� ������� [left] �� ����� [right]
			right--; // �������� ������ ������� ������
		}
	}
	a[left] = pivot; // ������ ����������� ������� �� �����
	//	pivot = left;
		//left = l_hold;
		//right = r_hold;
	if (l_hold < left) // ���������� �������� ���������� ��� ����� � ������ ����� �������
		QuickSort(a, l_hold, left - 1);
	if (r_hold > left)
		QuickSort(a, left + 1, r_hold);
}

void Filter()
{
	string str;
	cout << "������� ���������, �� ������� ������� ����������\n";
	cin >> str;
	system("cls");
	for (int i = 0; i < _amountOfClients; i++)
	{
		size_t pos = ClientList[i].name.find(str);
		if (pos != std::string::npos)
		{
			cout << "��������: " << ClientList[i].name << endl;
			cout << "�����: " << ClientList[i].adress << endl;
			cout << "�������: " << ClientList[i].phone_number << endl;
			cout << "���������� ����: " << ClientList[i].fio << endl;
			cout << "�����������: " << ClientList[i].kolvo << endl;
			cout << "����: " << ClientList[i].data << endl;
			cout << "\n_____________________________________________\n";
		}
	}

}

void InterpolatingSearch()
{

	int x = 0; //������� ������� �������, � ������� ������������ �������
	int a = 0; //����� ������� �������, ��� ������� �����
	int b = _amountOfService; //������ ������� �������, ��� ������� �����
	cout << "�������� ����, ������� ����� �����\n";
	int WhatFind; //��������, ������� ����� �����
	cin >> WhatFind;
	system("cls");
	bool found; //���������-����, ����������� True ���� ������� �������

	for (found = false; (ServiceList[a].opt < WhatFind) && (ServiceList[b].opt > WhatFind) && !found; )
	{
		//���������� ������������� ���������� ��������, ������� ����� ������������ � �������
		x = a + ((WhatFind - ServiceList[a].opt) * (b - a)) / (ServiceList[b].opt - ServiceList[a].opt);
		//��������� ����� ������ �������, ���� ������� �� �������
		if (ServiceList[x].opt < WhatFind)
			a = x + 1;
		else if (ServiceList[x].opt > WhatFind)
			b = x - 1;
		else
		{
			found = true;
			cout << "��������: " << ServiceList[x].name << endl;
			cout << "������� ����: " << ServiceList[x].opt << endl;
			cout << "��������� ����: " << ServiceList[x].rozn << endl;
			cout << "��������: " << ServiceList[x].description << endl;
			cout << "\n_____________________________________________\n";

		}

	}


	if (ServiceList[a].opt == WhatFind)
	{
		cout << "��������: " << ServiceList[a].name << endl;
		cout << "������� ����: " << ServiceList[a].opt << endl;
		cout << "��������� ����: " << ServiceList[a].rozn << endl;
		cout << "��������: " << ServiceList[a].description << endl;
		cout << "\n_____________________________________________\n";
	}
	else if (ServiceList[b].opt == WhatFind)
	{
		cout << "��������: " << ServiceList[b].name << endl;
		cout << "������� ����: " << ServiceList[b].opt << endl;
		cout << "��������� ����: " << ServiceList[b].rozn << endl;
		cout << "��������: " << ServiceList[b].description << endl;
		cout << "\n_____________________________________________\n";
	}
	else
		cout << "��������, ����� �� ��� ������." << endl;


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
	cout << "������� ������ �������� ��������\n";
	cin >> key;
	system("cls");
	int midd = 0, left = 0, right = n;
	while (1)
	{
		midd = (left + right) / 2;

		if (key < ServiceList[midd].service_id)       // ���� ������� ������ �������� � ������
			right = midd - 1;      // ������� ������ ������� ������
		else if (key > ServiceList[midd].service_id)  // ���� ������� ������ �������� � ������
			left = midd + 1;	   // ������� ����� ������� ������
		else                       // ����� (�������� �����)
		{
			cout << "��������: " << ServiceList[midd].name << endl;
			cout << "������� ����: " << ServiceList[midd].opt << endl;
			cout << "��������� ����: " << ServiceList[midd].rozn << endl;
			cout << "��������: " << ServiceList[midd].description << endl;
			cout << "\n_____________________________________________\n";
			break;           // ������� ���������� ������ ������
		}
		if (left > right)          // ���� ������� ���������� 

		{
			cout << "������� �� ������\n";
			break;
		}

	}
}