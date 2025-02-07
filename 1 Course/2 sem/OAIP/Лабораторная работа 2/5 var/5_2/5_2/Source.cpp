#include <iostream>
#include <fstream>
#define SIZE 2
using namespace std;

union PersorLibrary
{
    char author[8];
    char name[8];
    char paren[8];
    char razdel[10];
    char location[10];
    bool here;
};

PersorLibrary users[SIZE];

void vvod();
void vivod();
void poisk();

int main() {
    setlocale(LC_CTYPE, "rus");
    int vibor;
    int lets = 1;
    while (lets == 1) {
        cout << "(1) - Ввод с клавиатуру\n"
            << "(2) - Вывод на экран\n"
            << "(3) - Удаление\n";
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
    int enter, buffer;
    ofstream out;          // поток для записи
    out.open("myfile.txt"); // окрываем файл для записи
    if (out.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "НОМЕР СТРОКИ " << i + 1;
            cout << endl << "ФАМИЛИЯ АВТОРА "; cin >> users[i].author;
            out << users[i].author << endl;
            cout << endl << "НАЗВАНИЕ КНИГИ "; cin >> users[i].name;
            out << users[i].name << endl;
            cout << "\nИЗДАТЕЛЬСТВО "; cin >> users[i].paren;
            out << users[i].paren << endl;
            cout << endl << "РАЗДЕЛ БИБЛИОТЕКИ "; cin >> users[i].razdel;
            out << users[i].razdel << endl;
            cout << endl << "ПРОИСХОЖДЕНИЕ КНИГИ "; cin >> users[i].location;
            out << users[i].location << endl;
            cout << endl << "НАЛИЧИЕ " << endl
                << "(1) - есть" << endl
                << "(0) - нет" << endl; cin >> buffer;
            if (buffer == 1) {
                users[i].here = true;
            }
            else {
                users[i].here = false;
            }
            out << users[i].here << endl;
            cout << endl << endl;
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
            cout << "Книга номер " << i + 1;
            cout << "\nАвтор ";
            in >> strInput;
            cout << strInput << endl;;
            cout << "\nНазвание ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nИздательство ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nРаздел библиотеки ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\nПроисхождение ";
            in >> strInput;
            cout << strInput << endl;
            in >> strInput;
            cout << "\nНаличие в библиотеке " << strInput << endl;
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
    cout << "Введите автора для поиска "; cin >> poisk;
    if (in.is_open()) {
        while (in.good()) {
            in >> poisk2;
            if (strcmp(poisk2, poisk) == 0) {
                f = true;
                cout << "\nАвтор ";
                cout << poisk2 << endl;;
                cout << "\nНазвание ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nИздательство ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nРаздел библиотеки ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\nПроисхождение ";
                in >> strInput;
                cout << strInput << endl;
                in >> strInput;
                cout << "\nНаличие в библиотеке " << strInput << endl;
                cout << endl << endl;
            }
        }
        if (f == false) {
            cout << "Не найдено" << endl;
        }
    }
}