//5lab
//Создать список, содержащий элементы целого типа.
//Найти сумму отрицательных двухзначных элементов или вы - дать сообщение, что таких элементов нет.

#include <iostream>
#include <fstream>
using namespace std;
struct list {
    int number;
    list* next;
};

void insert(list*&, float); //функция добавления элемента 
float del(list*&, float);   //функция удаления 
int IsEmpty(list*);         //функция, которая проверяет, пуст ли список
void printList(list*);      //функция вывода
void menu(void);            //функция, показывающая меню
void sum(list*);            //Найти сумму отрицательных двухзначных элементов
void toFile(list*& p);      //Запись в файл
void fromFile(list*& p);    //Считывание из файла

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL;
    int choice;
    int value;
    menu();//вывести меню 
    cout << " ? ";
    cin >> choice;
    while (choice != 7) {
        switch (choice)
        {
        case 1:
            cout << "Введите число ";//добавить число в список
            cin >> value;
            insert(first, value);
            menu();
            break;
        case 2:
            if (!IsEmpty(first)) { //удалить число из списка
                cout << "Введите удаляемое число ";
                cin >> value;
                if (del(first, value)) {
                    cout << "Удалено число " << value << endl;
                    printList(first);
                }
                else {
                    cout << "Число не найдено" << endl;
                }
            }
            else {
                cout << "Список пуст" << endl;
            }
            menu();
            break;
        case 3:   sum(first);//вычисление суммы  
            menu();
            break;
        case 4:
            printList(first);
            menu();
            break;
        case 5:    toFile(first);
            menu();
            break;
        case 6:    fromFile(first);
            menu();
            break;
        default:
            cout << "Неправильный выбор" << endl;
            menu();
            break;
        }
        cout << "?  ";
        cin >> choice;
    }
    cout << "Конец" << endl;
    return 0;
}

void menu(void)//Вывод меню 
{
    cout << "\nСделайте выбор:" << endl;
    cout << " 1 - Ввод числа" << endl;
    cout << " 2 - Удаление числа" << endl;
    cout << " 3 - Найти сумму отрицательных двухзначных элементов" << endl;
    cout << " 4 - Вывод списка в консольное окно" << endl;
    cout << " 5 - Запись списка в файл" << endl;
    cout << " 6 - Вывод списка из файла" << endl;
    cout << " 7 - Выход" << endl;
}

void insert(list*& p, float value)//Добавление числа value в список 
{
    list* newP = new list;
    if (newP != NULL)//есть ли место?  
    {
        newP->number = value;
        newP->next = p;
        p = newP;
    }
    else {
        cout << "Операция добавления не выполнена" << endl;
    }
}

float del(list*& p, float value)//Удаление числа 
{
    list* previous, * current, * temp;
    if (value == p->number)
    {
        temp = p;
        p = p->next;//отсоединить узел 
        delete temp;//освободить отсоединенный узел 
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->number != value)
        {
            previous = current;
            current = current->next;//перейти к следующему 
        }
        if (current != NULL)
        {
            temp = current;
            previous->next = current->next;
            free(temp);
            return value;
        }
    }
    return 0;
}

int IsEmpty(list* p)//Список  пустой? (1-да, 0-нет) 
{
    return p == NULL;
}



void printList(list* p)//Вывод списка 
{
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        cout << "Список:" << endl;
        while (p != NULL)
        {
            cout << "-->" << p->number;
            p = p->next;
        }
        cout << "-->NULL" << endl;
    }
}

void sum(list* p) { //Найти сумму отрицательных двухзначных элементов   
    int sm = 0;
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        while (p != NULL)
        {
            if (p->number <= -10 && p->number >= -99 ) {
                sm = sm + (p->number);
            }
            p = p->next;
        }
        if (sm != 0) {
            cout << "Сумма отрицательных двухзначных элементов , равна " << sm << endl;
        }
        else {
            cout << "Отрицательных двухзначных элементов, нет" << endl;
        }
    }
}

void toFile(list*& p) {
    list* temp = p;
    list buf;
    ofstream frm("mList.dat");
    if (frm.fail())
    {
        cout << "\n Ошибка открытия файла";
        exit(1);
    }
    while (temp)
    {
        buf = *temp;
        frm.write((char*)&buf, sizeof(list));
        temp = temp->next;
    }
    frm.close();
    cout << "Список записан в файл mList.dat\n";
}

void fromFile(list*& p)//Считывание из файла
{
    list buf, * first = nullptr;
    ifstream frm("mList.dat");
    if (frm.fail())
    {
        cout << "\n Ошибка открытия файла";
        exit(1);
    }
    frm.read((char*)&buf, sizeof(list));
    while (!frm.eof())
    {
        insert(first, buf.number);
        cout << "-->" << buf.number;
        frm.read((char*)&buf, sizeof(list));
    }
    cout << "-->NULL" << endl;
    frm.close();
    p = first;
    cout << "\nСписок считан из файла mList.dat\n";
}