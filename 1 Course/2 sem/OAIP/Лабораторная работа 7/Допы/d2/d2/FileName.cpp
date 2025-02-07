#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Stack
{
    int data;
    Stack* next;
};

void push(Stack*& top, int data)
{
    Stack* new_node = new Stack;
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

void pop(Stack*& top)
{
    if (top == NULL)
    {
        cout << "Стек пуст!" << endl;
        return;
    }
    Stack* tmp = top;
    top = top->next;
    delete tmp;
}

int peek(Stack* top)
{
    if (top == NULL)
    {
        cout << "Стек пуст!" << endl;
        return -1;
    }
    return top->data;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    Stack* top = NULL;
    int num = 0, len = 0, shortest = -1, shortest_len = 0;

    ifstream fin("input.txt");
    if (!fin)
    {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    while (!fin.eof())
    {
        string line;
        getline(fin, line);
        len = line.length();
        push(top, len);
        num++;
        if (shortest == -1 || len < shortest_len)
        {
            shortest = num;
            shortest_len = len;
        }
    }

    fin.close();

    cout << "Содержимое стека: ";
    while (top != NULL)
    {
        cout << peek(top) << " ";
        pop(top);
    }
    cout << endl;

    cout << "Номер последней самой короткой строки: " << shortest << endl;
    cout << "Длина последней самой короткой строки: " << shortest_len << endl;

    return 0;
}