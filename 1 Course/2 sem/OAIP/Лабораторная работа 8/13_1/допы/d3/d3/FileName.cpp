//Создать очередь с вещественными числами, и заполнить ее с клавиатуры.
//Выполнить циклический сдвиг элементов в очереди так, чтобы в ее начале был расположен наибольший элемент.
#include <iostream>

struct QueueNode {
    int data;           
    QueueNode* next;   
};


class Queue {
private:
    QueueNode* front;   
    QueueNode* rear;    
    int size;           
public:
    Queue() {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }


    void enqueue(int value) {
        QueueNode* newNode = new QueueNode;
        newNode->data = value;
        newNode->next = nullptr;

        if (front == nullptr) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    int dequeue() {
        if (front == nullptr) {
            std::cerr << "Очередь пуста" << std::endl;
            return -1;
        }

        QueueNode* temp = front;
        int value = temp->data;

        front = front->next;
        delete temp;
        size--;

        return value;
    }

    void rotate() {
        if (front == nullptr || front == rear) {
            return;
        }

        int maxIndex = 0;
        int maxValue = front->data;
        QueueNode* current = front;
        for (int i = 1; i < size; i++) {
            current = current->next;
            if (current->data > maxValue) {
                maxIndex = i;
                maxValue = current->data;
            }
        }

        for (int i = 0; i < maxIndex; i++) {
            enqueue(dequeue());
        }
    }
    void display() {
        if (front == nullptr) {
            std::cout << "Очередь пуста" << std::endl;
            return;
        }

        QueueNode* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    Queue q;

    std::cout << "Введите элементы очереди" << std::endl;
    double element;
    while (std::cin >> element) {
        q.enqueue(element);
    }
    q.display();
    q.rotate();
    q.display();

}
