
//Ваша компания торгует товарами из определенного спектра.
// Каждый из этих товаров характеризуется наименованием, оптовой ценой, розничной ценой и справочной информацией.
//В Вашу компанию обращаются покупатели.Для каждого из них Вы запоминаете в базе данных стандартные данные(наименование, адрес, телефон, контактное лицо) и составляете по каждой сделке документ,
//  запоминая наряду с покупателем количество купленного им товара и дату покупки.
//Обычно покупатели в рамках одной сделки покупают не один товар, а сразу несколько.
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

int _stateMenu;

void Menu() {
    cout << "Выберите действие:" << endl
        << "(1) Данные о покупателе" << endl
        << "(2) Составление документа" << endl
        << "(3) Просмотр  сведений" << endl
        << "(4) Удаление из базы данных" << endl
        << "(5) Создание и запись данных в файл " << endl
        << "(6) Чтение файла " << endl
        << "(7) Удаление содержимого в файле" << endl
        << "(8) Удаление  файла" << endl
        << "Ваш выбор: ";
    cin >> _stateMenu;
}


void infile();
void outfile();
void delitus();

int client_info;


char adress[20];
char phone[20];
char name[20];
char fio[20];
char kolvo[20];
char date[20];
char path[20];



int main()
{
    setlocale(LC_ALL, "rus");
    char client_info;

    Menu();
    while (_stateMenu != 0) {

        switch (_stateMenu)
        {
        case 1:
            system("cls");
            int vibor;
            system("cls");
            cout << "Данные клиента 2 - удалить, 1 - ввести, 0 - просмотреть?" << endl;
            cin >> vibor;
            switch (vibor) {
            case 2:
                system("cls");
                cout << "Данные удалены!" << endl;
                system("pause");
                system("cls");
                Menu();
                break;
            case 1:
                system("cls");
                cout << "Введите данные!" << endl;
                cout << "Наименование:" << endl;
                cin >> name;
                cout << "Адрес:" << endl;
                cin >> adress;
                cout << "Телефон:" << endl;
                cin >> phone;
                cout << "Контактное лицо:" << endl;
                cin >> fio;
                cout << "Колличество купленных товаров: " << endl;
                cin >> kolvo;
                cout << "Дата покупки:" << endl;
                cin >> date;
                system("pause");
                system("cls");
                Menu();
                break;
            case 0:
                system("cls");
                cout << "Данные выведены!" << endl;
                cout << "Наименование:" << name << endl;
                cout << "Адрес:" << adress << endl;
                cout << "Телефон:" << phone << endl;
                cout << "Контактное лицо:" << fio << endl;
                cout << "Колличество купленных товаров: " << kolvo << endl;
                cout << "Дата покупки:" << date << endl;
                system("pause");
                system("cls");
                Menu();
                break;
            default:
                system("cls");
                cout << "Неверно введен номер действия!" << endl;
                system("pause");
                system("cls");
                Menu();
            }
            break;
            system("pause");
            system("cls");
            Menu();
            break;
        case 2:
            system("cls");
            cout << "Выберите клиента из  базы данных для составления документа: " << endl;
            cin >> client_info;
            cout << "Документ составлен!";
            cout << " Данные о пользователе ->" << endl;
            cout << "Наименование:" << name << endl;
            cout << "Адрес:" << adress << endl;
            cout << "Телефон:" << phone << endl;
            cout << "Контактное лицо:" << fio << endl;
            cout << "Колличество купленных товаров: " << kolvo << endl;
            cout << "Дата покупки:" << date << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        case 3:
            system("cls");
            cout << "Информация о покупателе" << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        case 4:
            system("cls");
            cout << "Удаление из базы данных!" << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        default:
            system("cls");
            cout << "Неверно введен номер действия!" << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        case 5:
            system("cls");
            cout << "Создание и запись данных в файл, название которого вводится с клавиатуры" << endl;
            infile();
            system("pause");
            system("cls");
            Menu();
            break;
        case 6:
            system("cls");
            cout << "Чтение файла" << endl;
            outfile();
            system("pause");
            system("cls");
            Menu();
            break;
        case 7:
            system("cls");
            cout << "Удаление содержимого в файле" << endl;
            delitus();
            system("pause");
            system("cls");
            Menu();
            break;
        case 8:
            system("cls");
            cout << "Удаление файла" << endl;
            remove(path);
            system("pause");
            system("cls");
            Menu();
            break;

        }
    }
}

void infile() {
    cout << "Enter name" << endl;
    cin >> path;

    ofstream fout(path);//создаем объект класса ofstream, связываем его с файлом в которм будет производится запись
    if (!fout.is_open())// если файл  открыт
    {
        cout << "Закройте файл!";
    }
    else //записывем строки в наш файл
    {
        fout << "\n" << name;
        fout << "\n" << adress;
        fout << "\n" << phone;
        fout << "\n" << fio;
        fout << "\n" << kolvo;
        fout << "\n" << date;
        fout << "\n" << "-------------------------------------------" << endl;

    }

    fout.close();//закрытие файла
}
void outfile() {
    char buff[50];
    ifstream fin(path); //создать объект класса ifstream и связать его с файлом, из которого будет производиться считывание
    do { //прочтение файла
        fin.getline(buff, 50);
        cout << buff << endl;
        buff[0] = 0;
    } while (!fin.eof());// пока не конец файла

}

void delitus() {
    ofstream fin(path, ios_base::out | ios_base::trunc); //константы для 1.открыть файл для записи 2.удалить содержимое файла, если он существует
    fin.close();//закрытие файла

}