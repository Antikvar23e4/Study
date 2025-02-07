//���������� ���������� ����� f, ����������� �� ������, ���������� � ��������� ���� g, 
//�������� ��� ���� � ����� ������ ������ ��� �������� � ��� ����� 
//(� ����������� ��������� ��������� �������, ��� ����� ����, ��� � ����� ��������� ����� ������). ������������ �������.
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct QueueNode {
    char digit;
    QueueNode* next;
};

class Queue {
private:
    QueueNode* head;
    QueueNode* tail;

public:
    Queue() {
        head = tail = nullptr;
    }

    ~Queue() {
        while (head != nullptr) {
            QueueNode* node = head;
            head = head->next;
            delete node;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void enqueue(char digit) {
        QueueNode* node = new QueueNode;
        node->digit = digit;
        node->next = nullptr;

        if (isEmpty()) {
            head = tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    char dequeue() {
        if (isEmpty()) {
            throw "������� �����";
        }

        char digit = head->digit;

        QueueNode* node = head;
        head = head->next;

        delete node;

        if (isEmpty()) {
            tail = nullptr;
        }

        return digit;
    }
};

int main() {
    ifstream input("f.txt");
    ofstream output("g.txt");

    if (!input || !output) {
        cout << "���������� ������� ����" << endl;
        return 1;
    }

    string line;
    while (getline(input, line)) {
        Queue queue;

        for (char c : line) {
            if (isdigit(c)) {
                queue.enqueue(c);
            }
            else {
                output << c;
            }
        }

        while (!queue.isEmpty()) {
            output << queue.dequeue();
        }

        output << endl;
    }

    input.close();
    output.close();

    return 0;
}