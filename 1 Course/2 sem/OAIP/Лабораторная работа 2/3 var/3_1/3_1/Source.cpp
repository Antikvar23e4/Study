//Ученики. Ф.И.О., класс (цифра+буква) предметы, оценки, средний балл.
//Выбор по фамилии. Класс реали-зовать с помощью битового поля, предметы  через перечисление.
#include <iostream>
#define SIZE 3
using namespace std;

enum subjects {
    MATH = 1,
    OAIP,
    BD,
    HISTORY
};

struct Class
{
    unsigned short Number : 4;
} nl[SIZE];

struct Students
{
    char fio[4];
    enum subjects subject[2];
    int estimation[2];
    struct Class;
};

Students student[SIZE];

void vvod(int size);
void vivod(int size);
void poisk(int size);
int deletion(int size);

int main() {
    setlocale(LC_CTYPE, "rus");
    int vibor;
    int lets = 1;
    int size = SIZE;
    while (lets == 1) {
        cout << "(1) - Ввод с клавиатуры\n"
            << "(2) - Вывод на экран\n"
            << "(3) - Удаление\n"
            << "(4) - Поиск по фамилии\n" << endl;
        cin >> vibor;

        switch (vibor) {
        case 1:
            system("cls");
            vvod(size);
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        case 2:
            system("cls");
            vivod(size);
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        case 3:
            system("cls");
            size = deletion(size);
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        case 4:
            system("cls");
            poisk(size);
            system("pause");
            system("cls");
            cout << "Введите 1 для продолжения ";
            cin >> lets;
            break;
        }
    }
}

void vvod(int size) {
    int enter, enter1, buffer;
    for (int i = 0; i < size; i++) {
        cout << "Ученик номер " << i + 1;
        cout << "\nВведите ФИО "; cin >> student[i].fio;
        cout << "\nВведите два предмета:\n"
            << "\n1.Математический анализ"
            << "\n2.Основы алгоритмизации и программирования"
            << "\n3.Базы данных"
            << "\n4.История\n";
        cin >> enter;
        cin >> enter1;
        student[i].subject[0] = subjects(enter);
        student[i].subject[1] = subjects(enter1);
        cout << "\nВведите две оценки ";
        cin >> student[i].estimation[0];
        cin >> student[i].estimation[1];
        cout << "\nВведите номер класса "; cin >> buffer; nl[i].Number = buffer;
        cout << endl << endl;
    }
}

void vivod(int size) {
    for (int i = 0; i < size; i++) {
        cout << "Ученик номер " << i + 1;
        cout << "\nФИО " << student[i].fio;
        cout << "\nПредмет:\n";
        for (int j = 0; j < 2; j++) {
            switch (student[i].subject[j]) {
            case 1:
                cout << "Математический анализ\n";
                break;
            case 2:
                cout << "Основы алгоритмизации и программирования\n";
                break;
            case 3:
                cout << "Базы данных\n";
                break;
            case 4:
                cout << "История\n";
                break;
            }
            cout << "Оценка " << student[i].estimation[j] << endl;
        }
        cout << "Класс \n" << nl[i].Number;
        cout << endl << endl;
    }
}

void poisk(int size) {
    float f = false;
    char poisk[4];
    cout << "Введите ФИО для поиска "; cin >> poisk;
    for (int i = 0; i < size; i++) {
        if (strcmp(student[i].fio, poisk) == 0) {
            f = true;
            cout << "Ученик номер " << i + 1;
            cout << "\nФИО " << student[i].fio;
            cout << "\nПредмет:\n";
            for (int j = 0; j < 2; j++) {
                switch (student[i].subject[j]) {
                case 1:
                    cout << "Математический анализ\n";
                    break;
                case 2:
                    cout << "Основы алгоритмизации и программирования\n";
                    break;
                case 3:
                    cout << "Базы данных\n";
                    break;
                case 4:
                    cout << "История\n";
                    break;
                }
                cout << "Оценка " << student[i].estimation[j] << endl << endl;
            }
            cout << "Класс " << nl[i].Number;
        }
    }
    if (f == false) {
        cout << "Не найдено" << endl;
    }
}

int deletion(int size) {
    cout << "Введите номер для удаления: ";
    int del;
    cin >> del;
    if (size != del) {
        for (int i = del - 1; i < size - 1; i++) {
            student[i] = student[i + 1];
        }
    }
    size--;
    cout << "\nСтрока успешно удалена" << endl;
    return size;
}
