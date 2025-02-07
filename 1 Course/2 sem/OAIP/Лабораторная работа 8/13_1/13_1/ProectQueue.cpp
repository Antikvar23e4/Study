//Создать очередь для массива целых(положительных и отрицательных) чисел.
//функции для ввода, вывода и удаления элементов очереди.
//При вводе чисел в очередь помещать только отрицательные элементы.
//Найти минимальный и максимальный элемент очереди.
//Вывести все элементы очереди и посчитать их количество.

#include<iostream>
using namespace std;

struct node
{
    int elem;
    node* sled;
};
class Spisok {
private:
    node* no, * ko;
    int klad;
public:
    Spisok() { no = ko = NULL; }
    void POSTROENIE();
    void VYVOD();
    void DOBAVLENIE(int);
    int  Set_Udal() { return klad; }
    void YDALENIE();
    void OCHISTKA();
};

void main()
{
    setlocale(LC_ALL, "Rus");
    Spisok A;
    int el;

    A.POSTROENIE();
    A.VYVOD();
    cout << "Введите добавляемый элемент: ";
    cin >> el;
    A.DOBAVLENIE(el); A.VYVOD();
    cout << "Удалим элемент из очереди.\n";
    A.YDALENIE(); A.VYVOD();
    el = A.Set_Udal();
    cout << "Информационное поле удаленного звена: " << el << endl;
    A.OCHISTKA();

    cout << "\n";
    system("PAUSE");
}

void Spisok::POSTROENIE()
//Построение очереди на базе однонаправленного списка
//без заглавного звена.
//no - указатель на начало очереди.
//ko - указатель на конец очереди.
{
    node* r;
    int el;

    cout << "Вводите элементы очереди:\n";
    cin >> el;
    if (el != 0)
    {
        r = new (node);
        (*r).elem = el; (*r).sled = NULL;
        no = r; ko = r; cin >> el;
        while (el != 0)
        {
            r = new (node);
            (*r).elem = el; (*r).sled = NULL;
            (*ko).sled = r; ko = r; cin >> el;
        }
    }
    else
    {
        r = NULL; no = r; ko = r;
    }
}

void Spisok::VYVOD()
//Вывод содержимого очереди.
//no - указатель на начало очереди.
//ko - указатель на конец очереди.
{
    node* r;
    cout << "Очередь: "; r = no;
    while (r != NULL)
    {
        cout << (*r).elem << " "; r = (*r).sled;
    }
    cout << endl;
}

void Spisok::DOBAVLENIE(int el)
//Добавление звена с информационным полем el к очереди,
//определенной указателями  no и ko.
{
    node* r;

    r = new (node);
    (*r).elem = el; (*r).sled = NULL;
    if (no != NULL)
    {
        (*ko).sled = r; ko = r;
    }
    else
    {
        no = r; ko = r;
    }
}

void Spisok::YDALENIE()
//Удаление звена из очереди, определенной указателями
//no и ko, с помещением его информационного поля в
//параметр klad.
{
    node* q;

    if (no == NULL)
        cout << "Удалить нельзя, так как очередь пуста!\n";
    else
    {
        klad = (*no).elem; q = no;
        no = (*no).sled; delete q;
    }
}

void Spisok::OCHISTKA()
//Возврат выделенной памяти в "кучу".
{
    node* q;

    q = no;
    if (no != NULL)
    {
        while (no != ko)
        {
            no = (*q).sled;
            delete q;  q = no;
        }
        delete no;
        no = ko = NULL;
    }
}


