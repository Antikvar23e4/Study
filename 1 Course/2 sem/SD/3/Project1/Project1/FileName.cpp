//Вы работаете в компании, занимающейся оптово - розничной продажей различных товаров.
//Вашей задачей является отслеживание финансовой стороны работы компании.
//Деятельность Вашей компании организована следующим образом : Ваша компания торгует товарами из определенного спектра.
//Каждый из этих товаров характеризуется наименованием, оптовой ценой, розничной ценой и справочной информацией.
//В Вашу компанию обращаются покупатели.
//Для каждого из них Вы запоминаете в базе данных стандартные данные
//(наименование, адрес, телефон, контактное лицо) и составляете по каждой сделке документ, запоминая наряду с покупателем количество купленного им товара и дату покупки.
//Обычно покупатели в рамках одной сделки покупают не один товар, а сразу несколько.

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
      
        cout << "Контактное лицо: " << client1.fio << endl;
        cout << "Адрес: " << client1.adress << endl;
        cout << "Телефон: " << client1.phone << endl;
        cout << "Дата: " << client1.data << endl;
        cout << "Наименование товара: " << client1.tovar.name << endl;
        cout << "Оптовая цена: " << client1.tovar.opt << endl;
        cout << "Розничная цена: " << client1.tovar.rozn<< endl;
        cout << "Справочная информация: " << client1.tovar.info << endl;
        cout << "Индек = " << client1.index << endl;
        
    }
}

void findClientIndex(list<Client> list)
{
    int number;
    cout << "Введите индекс клиента: \n > " << endl;
    cin >> number;

    for (Client client1 : list)
    {
        if (client1.index == number)
        {
            cout << "Контактное лицо: " << client1.fio << endl;
            cout << "Адрес: " << client1.adress << endl;
            cout << "Телефон: " << client1.phone << endl;
            cout << "Дата: " << client1.data << endl;
            cout << "Наименование товара: " << client1.tovar.name << endl;
            cout << "Оптовая цена: " << client1.tovar.opt << endl;
            cout << "Розничная цена: " << client1.tovar.rozn << endl;
            cout << "Справочная информация: " << client1.tovar.info << endl;
            cout << "Индекc = " << client1.index << endl;
        }
    }
}

Client EnterClient(list<Client> list)
{
    Client client;

    cout << "Введите контактное лицо: " << endl;
    cin >> client.fio;
  

    client.index = list.size();

    int Num;
    system("cls");
    cout << "Выберите товар: " << endl;
    cout << "(1) Калибратор" << endl
        << "(2) Тепловизор" << endl
        << "(3) Предохранитель" << endl
        << "(4) Клемма" << endl
        << "(5) Вентилятор" << endl
        << "(6) Осциллограф" << endl
        << "Ваш выбор: ";
    cin >> Num;

    switch (Num)
    {
    case 1:
        client.tovar.name = "Калибратор";
        client.tovar.opt = 100;
        client.tovar.rozn = 125;
        client.tovar.info =  "FLUKE 789 КАЛИБРАТОР-МУЛЬТИМЕТР ПЕТЛИ ТОКА";
        break;

    case 2:
        client.tovar.name = "Тепловизор";
        client.tovar.opt = 200;
        client.tovar.rozn = 225;
        client.tovar.info = "FLUKE TIS ТЕПЛОВИЗОР (ТЕПЛОВИЗИОННЫЙ СКАНЕР)";
        break;

    case 3:
        client.tovar.name = "Предохранитель";
        client.tovar.opt = 100;
        client.tovar.rozn = 125;
        client.tovar.info = "FS-52GF-16/250";
        break;

    case 4:
        client.tovar.name = "Клемма";
        client.tovar.opt = 10;
        client.tovar.rozn = 25;
        client.tovar.info = "TS-1R";
        break;

    case 5:
        client.tovar.name = "Вентилятор";
        client.tovar.opt = 100;
        client.tovar.rozn = 125;
        client.tovar.info = "CF3-2B";
        break;

    case 6:
        client.tovar.name = "Осциллограф";
        client.tovar.opt = 200;
        client.tovar.rozn = 225;
        client.tovar.info = "TDS-2024C 4КАН.200МГЦ ЦИФРОВОЙ ОСЦИЛЛОГРАФ";
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
    cout << "Введите путь к файлу: ";
    cin >> path;

    if (remove(path) == 0)
    {
        cout << "Файл удалён\n";
        system("pause");
    }
    else
        cout << "Файл не найден\n";
}

void saveFile(Company company)
{
    char* path = new char[100];
    cout << "Введите название файла: ";
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
    cout << "Введите название файла: ";
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
    cout << "Введите имя того, кого хотите удалить: \n > ";
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
    cout << "Выберите действие:" << endl
        << "(1) Ввести данные" << endl
        << "(2) Вывести информацию из файла" << endl
        << "(3) Сохранить информацию в файл" << endl
        << "(4) Удаление информации из файла" << endl
        << "(5) Удалить файл " << endl
        << "(6) Вывести всех клиентов " << endl
        << "(7) Найти клиента по индексу" << endl
        << "(8) Завершить программу" << endl
        << "Ваш выбор: ";
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
