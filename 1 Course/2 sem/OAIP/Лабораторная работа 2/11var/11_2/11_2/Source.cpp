//Реализовать функции ввода с клавиатуры, вывода на экран и поиска. 
//Справочник автомобилей. Марка автомобиля, цвет, заводской номер, дата выпуска, тип кузова (седан, универсал и т. п.), 
//дата последнего техосмотра, владелец. Выбор транспортных средств по владельцу.

#include <iostream>
#include <fstream>
#define SIZE 1
using namespace std;

union automobile
{
    char brand[16];
    char owner[16];
    char color[8];
    int number;
    int date;
    int techno;
    char type[16];
};

automobile users[SIZE];

void input();
void output();
void find();

int main() {
    setlocale(LC_CTYPE, "rus");
    system("chcp 1251");
    system("cls");
    int choice;
    int lets = 1;
    while (lets == 1) {
        cout << "(1) - Ввод информации\n"
            << "(2) - Вывод на экран\n"
            << "(3) - Поиск по владельцу\n"
            << "(4) - Выход из программы\n" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            input();
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            output();
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            find();
            system("pause");
            system("cls");
            break;
        case 4: lets = 0; break;
        }
    }
}

void input() {
    int enter, buffer;
    ofstream out;          // поток для записи
    out.open("myfile.txt"); // окрываем файл для записи
    if (out.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "\nВведите владельца "; cin >> users[i].owner;
            out << users[i].owner << endl;
            cout << "\nВведите марку автомобиля "; cin >> users[i].brand;
            out << users[i].brand << endl;
            cout << "\nВведите цвет автомобиля "; cin >> users[i].color;
            out << users[i].color << endl;
            cout << "\nВведите заводской номер "; cin >> users[i].number;
            out << users[i].number << endl;
            cout << "\nВведите дату выпуска "; cin >> users[i].date;
            out << users[i].date << endl;
            cout << "\nВведите тип кузова "; cin >> users[i].type;
            out << users[i].type << endl;
        }
    }
    else {
        cout << "Error!" << endl;
    }
    out.close();
}

void output() {
    ifstream in("myfile.txt"); // окрываем файл для чтения
    string strInput;
    if (in.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "Авто номер " << i + 1;
            cout << "\nВладелец ";
            in >> strInput;
            cout << strInput << endl;;
            cout << "\nМарка ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nЦвет ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nЗаводской номер ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nДата выпуска ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nТип кузова ";
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

void find() {
    float f = false;
    char find[8];
    char* find2 = new char[8];
    string strInput;
    ifstream in("myfile.txt");
    cout << "Введите владельца для поиска "; cin >> find;
    if (in.is_open()) {
        while (in.good()) {
            in >> find2;
            if (strcmp(find2, find) == 0) {
                f = true;
                cout << "\nВладелец ";
                cout << find2 << endl;;
                cout << "\nМарка ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nЦвет ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nЗаводской номер ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nДата выпуска ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nТип кузова ";
                in >> strInput;
                cout << strInput << endl;
            }
        }
        if (f == false) {
            cout << "Не найдено" << endl;
        }
    }
}