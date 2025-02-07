//�� ��������� � ��������, ������������ ������ - ��������� �������� ��������� �������.
//����� ������� �������� ������������ ���������� ������� ������ ��������.
//������������ ����� �������� ������������ ��������� ������� : ���� �������� ������� �������� �� ������������� �������.
//������ �� ���� ������� ��������������� �������������, ������� �����, ��������� ����� � ���������� �����������.
//� ���� �������� ���������� ����������.
//��� ������� �� ��� �� ����������� � ���� ������ ����������� ������
//(������������, �����, �������, ���������� ����) � ����������� �� ������ ������ ��������, ��������� ������ � ����������� ���������� ���������� �� ������ � ���� �������.
//������ ���������� � ������ ����� ������ �������� �� ���� �����, � ����� ���������.

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <list>

using namespace std;
int _stateMenu;

struct Tovar
{
    string name;
    string info;
    int opt;
    int rozn;
};

struct Client
{
    int index;
    string adress;
    string phone;
    string fio;
    Tovar tovar;
    int kolvo;
    char data[20];
};

struct Company
{
    string NameCompany;
    list<Client> listClient;
}; 
void printAllesClients(list<Client> list)
{
    for (Client client1 : list)
    {
      
        cout << "���������� ����: " << client1.fio << endl;
        cout << "�����: " << client1.adress << endl;
        cout << "�������: " << client1.phone << endl;
        cout << "����: " << client1.data << endl;
        cout << "������������ ������: " << client1.tovar.name << endl;
        cout << "������� ����: " << client1.tovar.opt << endl;
        cout << "��������� ����: " << client1.tovar.rozn<< endl;
        cout << "���������� ����������: " << client1.tovar.info << endl;
        cout << "����� = " << client1.index << endl;
        
    }
}

void findClientIndex(list<Client> list)
{
    int number;
    cout << "������� ������ �������: \n > " << endl;
    cin >> number;

    for (Client client1 : list)
    {
        if (client1.index == number)
        {
            cout << "���������� ����: " << client1.fio << endl;
            cout << "�����: " << client1.adress << endl;
            cout << "�������: " << client1.phone << endl;
            cout << "����: " << client1.data << endl;
            cout << "������������ ������: " << client1.tovar.name << endl;
            cout << "������� ����: " << client1.tovar.opt << endl;
            cout << "��������� ����: " << client1.tovar.rozn << endl;
            cout << "���������� ����������: " << client1.tovar.info << endl;
            cout << "�����c = " << client1.index << endl;
        }
    }
}

Client EnterClient(list<Client> list)
{
    Client client;

    cout << "������� ���������� ����: " << endl;
    cin >> client.fio;
  

    client.index = list.size();

    int Num;
    system("cls");
    cout << "�������� �����: " << endl;
    cout << "(1) ����������" << endl
        << "(2) ����������" << endl
        << "(3) ��������������" << endl
        << "(4) ������" << endl
        << "(5) ����������" << endl
        << "(6) �����������" << endl
        << "��� �����: ";
    cin >> Num;

    switch (Num)
    {
    case 1:
        client.tovar.name = "����������";
        client.tovar.opt = 100;
        client.tovar.rozn = 125;
        client.tovar.info =  "FLUKE 789 ����������-���������� ����� ����";
        break;

    case 2:
        client.tovar.name = "����������";
        client.tovar.opt = 200;
        client.tovar.rozn = 225;
        client.tovar.info = "FLUKE TIS ���������� (�������������� ������)";
        break;

    case 3:
        client.tovar.name = "��������������";
        client.tovar.opt = 100;
        client.tovar.rozn = 125;
        client.tovar.info = "FS-52GF-16/250";
        break;

    case 4:
        client.tovar.name = "������";
        client.tovar.opt = 10;
        client.tovar.rozn = 25;
        client.tovar.info = "TS-1R";
        break;

    case 5:
        client.tovar.name = "����������";
        client.tovar.opt = 100;
        client.tovar.rozn = 125;
        client.tovar.info = "CF3-2B";
        break;

    case 6:
        client.tovar.name = "�����������";
        client.tovar.opt = 200;
        client.tovar.rozn = 225;
        client.tovar.info = "TDS-2024C 4���.200��� �������� �����������";
        break;

        default:
        break;
    }
    system("cls");
    return client;
}

void deleteFile()
{
    char* path = new char[100];
    cout << "������� ���� � �����: ";
    cin >> path;

    if (remove(path) == 0)
    {
        cout << "���� �����\n";
        system("pause");
    }
    else
        cout << "���� �� ������\n";
}

void saveFile(Company company)
{
    char* path = new char[100];
    cout << "������� �������� �����: ";
    cin >> path;

    ofstream file(path);
    file << "           Clients\n";

    for (auto item : company.listClient)
    {
        file << "-----------------------------------\n";
        file << item.fio << endl;
        file << item.adress << endl;
        file << item.phone << endl;
        file << item.data << endl;
        file << item.tovar.name << endl;
        file << item.tovar.opt << endl;
        file << item.tovar.rozn << endl;
        file << item.tovar.info << endl;
        file << item.index << endl;
        file << "-----------------------------------\n";
        file.close();
    }
}

char* readFile(Company& company)
{
    Company TimeCompany;
    std::string line;
    char* path = new char[100];
    cout << "������� �������� �����: ";
    cin >> path;
    std::ifstream in(path);
    if (in.is_open())
    {
        string type = "";
        while (getline(in, line))
        {

            Client client;

            getline(in, line);
            client.fio = line;
            getline(in, line);
            client.adress = line;
            getline(in, line);
            client.phone = line;
            getline(in, line);
            client.tovar.name = line;
            getline(in, line);
            client.tovar.opt = stoi(line);
            getline(in, line);
            client.tovar.rozn = stoi(line);
            getline(in, line);
            client.tovar.info = line;
            getline(in, line);
            client.index = stoi(line);

            getline(in, line);
            TimeCompany.listClient.push_back(client);

        }
    }
    company = TimeCompany;
    in.close();
    return path;
}

void readAndDeleteInfo()
{
    Company company;

    char* path = readFile(company);

    remove(path);

    ofstream file(path);
    string name;
    cout << "������� ��� ����, ���� ������ �������: \n > ";
    cin >> name;

   
    file << "------------------------------\n";
    file << "           Clients\n";
    file << "------------------------------\n";
    for (auto item : company.listClient)
    {
        if (name != item.fio)
        {
            file << item.fio << endl;
            file << item.adress << endl;
            file << item.phone << endl;
            file << item.data << endl;
            file << item.tovar.name << endl;
            file << item.tovar.opt << endl;
            file << item.tovar.rozn << endl;
            file << item.tovar.info << endl;
            file << item.index << endl;

            file.close();
        }
    }
    file.close();
}

void Menu() {
    cout << "�������� ��������:" << endl
        << "(1) ������ ������" << endl
        << "(2) ������� ���������� �� �����" << endl
        << "(3) ��������� ���������� � ����" << endl
        << "(4) �������� ���������� �� �����" << endl
        << "(5) ������� ���� " << endl
        << "(6) ������� ���� �������� " << endl
        << "(7) ����� ������� �� �������" << endl
        << "(8) ��������� ���������" << endl
        << "��� �����: ";
    cin >> _stateMenu;
}

int main()
{
    setlocale(LC_ALL, "rus");
    Company company;
    ofstream file;

    Menu();
    while (_stateMenu != 0) {

        switch (_stateMenu)
        {
        case 1:
            system("cls");
            company.listClient.push_back(EnterClient( company.listClient));
            Menu();
            break;
        case 2:
            system("cls");
            readFile(company);
            system("pause");
            Menu();
            break;
        case 3:
            system("cls");
            saveFile(company);
            system("pause");
            Menu();
            break;
        case 4:
            system("cls");
            readAndDeleteInfo();
            system("pause");
            Menu();
            break;
        case 5:
            system("cls");
            deleteFile();
            Menu();
            break;
        case 6:
            system("cls");
            printAllesClients(company.listClient);
            system("pause");
            Menu();
            break;
        case 7:
            system("cls");
            findClientIndex(company.listClient);
            system("pause");
            Menu();
            break;
        case 8:
            system("cls");
            return 0;
        }
    }
    system("cls");
}
