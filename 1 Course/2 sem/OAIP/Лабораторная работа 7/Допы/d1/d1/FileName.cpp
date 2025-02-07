//1. Дана величина a строкового типа из четного количества символов. Получить и напечатать величину b, состоящую из символов первой половины величины a,
//записанных в обратном порядке, после которых идут символы второй половины ве-личины a, также записанные в обратном порядке .
#include <iostream>
#include <cstring>

using namespace std;

struct StackNode {
    char data;
    StackNode* next;
};

class Stack {
private:
    StackNode* top;

public:
    Stack() {
        top = nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(char data) {
        StackNode* newNode = new StackNode;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (top == nullptr) {
            cerr << "Стек пустой" << endl;
            return '\0';
        }
        StackNode* temp = top;
        char data = top->data;
        top = top->next;
        delete temp;
        return data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    char* a = new char;
    cin >> a;
    int len = strlen(a);
    Stack firstHalf;
    Stack secondHalf;

    cout << "\nПервая половина: ";
    for (int i = 0; i < len / 2; i++) {
        firstHalf.push(a[i]);
        cout << a[i];
    }
    cout << "\nВторая половина: ";
    for (int i = len / 2; i < len; i++) {
        secondHalf.push(a[i]);
        cout << a[i];
    }
    cout << "\nРезультат: ";
    while (!firstHalf.isEmpty()) {
        cout << firstHalf.pop();
    }
    while (!secondHalf.isEmpty()) {
        cout << secondHalf.pop();
    }

    cout << endl;

    return 0;
}