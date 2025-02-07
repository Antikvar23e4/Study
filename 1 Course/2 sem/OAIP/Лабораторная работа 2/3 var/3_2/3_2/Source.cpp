//Ломбард. База хранимых товаров и недвижимости: анкетные данные клиента, наименование товара, оце-ночная стоимость; 
//сумма, выданная под залог, дата сдачи, срок хранения. Выбор товаров по наименованию.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define SIZE 2

void vvod();
void vivod();
void poisk();

union Lombard {
    char fio[4];
    char tovar[10];
    int sum;
    int zalog;
    char date[5];
    char hranenie[5];
} user[SIZE];

int main() {
    setlocale(LC_CTYPE, "rus");
    int vibor;
    int lets = 1;
    while (lets == 1) {
        cout << "(1) - Ввод с клавиатуры\n"
            << "(2) - Вывод на экран\n"
            << "(3) - Поиск по наименованию\n";
        cin >> vibor;

        switch (vibor) {
        case 1:
            system("cls");
            vvod();
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        case 2:
            system("cls");
            vivod();
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        case 3:
            system("cls");
            poisk();
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        }
    }
}

void vvod() {
    int enter, enter1;
    ofstream out("myfile.txt"); // окрываем файл для записи
    if (out.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "Товар номер " << i + 1;
            cout << "\nВведите ФИО "; cin >> user[i].fio;
            out << user[i].fio << endl;
            cout << "\nВведите наименование товара "; cin >> user[i].tovar;
            out << user[i].tovar << endl;
            cout << "\nВведите оценочную стоимость "; cin >> user[i].sum;
            out << user[i].sum << endl;
            cout << "\nВведите сумму, выданную под залог "; cin >> user[i].zalog;
            out << user[i].zalog << endl;
            cout << "\nВведите дату сдачи "; cin >> user[i].date;
            out << user[i].date << endl;
            cout << "\nВведите срок хранения "; cin >> user[i].hranenie;
            out << user[i].hranenie << endl;
            cout << "Запись в файл выполнена" << endl;
        }
    }
    else {
        cout << "Error!" << endl;
    }
    out.close();
}

void vivod() {
    ifstream in("myfile.txt"); // окрываем файл для чтения
    string strInput;
    if (in.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "Товар номер " << i + 1;
            cout << "\nФИО ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nНаименование товара ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nОценочная стоимость ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nСумма, выданная под залог ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nДата сдачи ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nСрок хранения ";
            in >> strInput;
            cout << strInput << endl;
            cout << endl << endl;
        }
    }
    else {
        cout << "Error!" << endl;
    }
    in.close();
}

void poisk() {
    float f = false;
    char poisk[4];
    char* poisk2 = new char[4];
    string strInput;
    ifstream in("myfile.txt");
    cout << "Введите ФИО для поиска "; cin >> poisk;
    if (in.is_open()) {
        while (in.good()) {
            in >> poisk2;
            if (strcmp(poisk2, poisk) == 0) {
                f = true;
                cout << "\nФИО " << poisk2 << endl;
                cout << "\nНаименование товара ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nОценочная стоимость ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nСумма, выданная под залог ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nДата сдачи ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nСрок хранения ";
                in >> strInput;
                cout << strInput << endl;
                cout << endl << endl;
            }
        }
        if (f == false) {
            cout << "Не найдено" << endl;
        }
    }
}
