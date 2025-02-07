#include "myQueue.h"
void Spisok::POSTROENIE()
//ѕостроение очереди на базе однонаправленного списка
//без заглавного звена.
//no - указатель на начало очереди.
//ko - указатель на конец очереди.
{
    node* r;
    int el;

    cout << "¬водите элементы очереди:\n";
    cin >> el;
    if (el != 0)
    {
        r = new (node);
        (*r).elem = el;
        (*r).sled = NULL;
        no = r; ko = r;
        cin >> el;
        while (el != 0)
        {
            if (el < 0) {
                r = new (node);
                (*r).elem = el;
                (*r).sled = NULL;
                (*ko).sled = r;
                ko = r;
            }
            cin >> el;
        }
    }
    else
    {
        r = NULL; no = r; ko = r;
    }
}

void Spisok::VYVOD()
//¬ывод содержимого очереди.
//no - указатель на начало очереди.
//ko - указатель на конец очереди.
{
    node* r;
    cout << "ќчередь: "; r = no;
    while (r != NULL)
    {
        cout << (*r).elem << " "; r = (*r).sled;
    }
    cout << endl;
}

void Spisok::DOBAVLENIE(int el)
//ƒобавление звена с информационным полем el к очереди,
//определенной указател€ми  no и ko.
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
//”даление звена из очереди, определенной указател€ми
//no и ko, с помещением его информационного пол€ в
//параметр klad.
{
    node* q;

    if (no == NULL)
        cout << "”далить нельз€, так как очередь пуста!\n";
    else
    {
        klad = (*no).elem; q = no;
        no = (*no).sled; delete q;
    }
}

void Spisok::OCHISTKA()
//¬озврат выделенной пам€ти в "кучу".
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

int Spisok::findMax() {
    if (no == NULL) { // если очередь пуста
        return -1; // вернуть код ошибки или выбросить исключение
    }
    int max = no->elem; // предположим, что первый элемент максимальный
    node* curr = no->sled; // начинаем со второго элемента
    while (curr != NULL) { // проходим по всем остальным элементам
        if (curr->elem > max) { // если текущий элемент больше максимального
            max = curr->elem; // обновл€ем максимальный элемент
        }
        curr = curr->sled; // переходим к следующему элементу
    }
    return max;
}