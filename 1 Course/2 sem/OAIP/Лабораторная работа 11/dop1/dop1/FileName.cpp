
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

// Структура, описывающая абонента
struct Subscriber {
    string name;  // Имя
    string phone;  // Номер телефона
    string tariff;  // Тариф

    // Конструктор по умолчанию
    Subscriber() {}

    // Конструктор с параметрами
    Subscriber(string name, string phone, string tariff) {
        this->name = name;
        this->phone = phone;
        this->tariff = tariff;
    }
};

// Класс, представляющий бинарное дерево
class BinaryTree {
public:
    // Структура, описывающая узел дерева
    struct Node {
        Subscriber subscriber;  // Абонент
        Node* left;  // Левый потомок
        Node* right;  // Правый потомок

        // Конструктор с параметрами
        Node(Subscriber subscriber, Node* left = nullptr, Node* right = nullptr) {
            this->subscriber = subscriber;
            this->left = left;
            this->right = right;
        }
    };

    Node* root;  // Корень дерева

    // Рекурсивная функция для добавления узла в дерево
    Node* addNode(Node* node, Subscriber subscriber) {
        if (node == nullptr) {
            return new Node(subscriber);
        }

        if (subscriber.phone < node->subscriber.phone) {
            node->left = addNode(node->left, subscriber);
        }
        else if (subscriber.phone > node->subscriber.phone) {
            node->right = addNode(node->right, subscriber);
        }

        return node;
    }

    // Рекурсивная функция для вывода всего дерева на экран
    void printTree(Node* node) {
        if (node != nullptr) {
            printTree(node->left);
            cout << "Имя: " << node->subscriber.name << endl;
            cout << "Номер телефона: " << node->subscriber.phone << endl;
            cout << "Тариф: " << node->subscriber.tariff << endl;
            cout << endl;
            printTree(node->right);
        }
    }

    // Рекурсивная функция для поиска абонента по номеру телефона
    Subscriber* findSubscriber(Node* node, string phone) {
        if (node == nullptr) {
            return nullptr;
        }

        if (phone < node->subscriber.phone) {
            return findSubscriber(node->left, phone);
        }
        else if (phone > node->subscriber.phone) {
            return findSubscriber(node->right, phone);
        }
        else {
            return &node->subscriber;
        }
    }

    // Рекурсивная функция для подсчета числа абонентов на каждом тарифе
    void countTariffs(Node* node, map<string, int>& countMap) {
        if (node != nullptr) {
            countTariffs(node->left, countMap);
            countMap[node->subscriber.tariff]++;
            countTariffs(node->right, countMap);
        }
    }


    // Конструктор по умолчанию
    BinaryTree() {
        root = nullptr;
    }

    // Функция для добавления абонента в дерево
    void addSubscriber(Subscriber subscriber) {
        root = addNode(root, subscriber);
    }

    // Функция для вывода всей базы данных на экран
    void printDatabase() {
        printTree(root);
    }

    // Функция для поиска абонента по номеру телефона
    Subscriber* findSubscriber(string phone) {
        return findSubscriber(root, phone);
    }

    // Функция для вывода наиболее востребованного тарифа
    void printMostPopularTariff() {
        map<string, int> countMap;
        countTariffs(root, countMap);

        string mostPopularTariff;
        int mostPopularCount = 0;

        for (auto& pair : countMap) {
            if (pair.second > mostPopularCount) {
                mostPopularTariff = pair.first;
                mostPopularCount = pair.second;
            }
        }

        cout << "Наиболее востребованный тариф: " << mostPopularTariff << endl;
    }
};

// Функция для чтения базы данных из файла
BinaryTree readDatabaseFromFile(string filename) {
    BinaryTree tree;

    ifstream file(filename);

    if (file.is_open()) {
        string name, phone, tariff;

            while (file >> name >> phone >> tariff) {
                Subscriber subscriber(name, phone, tariff);
                tree.addSubscriber(subscriber);
            }

        file.close();
    }

    return tree;
}

// Функция для записи базы данных в файл
void writeDatabaseToFile(BinaryTree tree, string filename) {
    ofstream file(filename);

    if (file.is_open()) {
        function<void(BinaryTree::Node*)> writeNode = [&](BinaryTree::Node* node) {
            if (node != nullptr) {
                file << node->subscriber.name << " " << node->subscriber.phone << " " << node->subscriber.tariff << endl;
                writeNode(node->left);
                writeNode(node->right);
            }
        };

        writeNode(tree.root);

        file.close();
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    BinaryTree tree;
    string number;

    //Добавление значений в базу
    tree.addSubscriber(Subscriber("Henry", "45370", "Tariff A"));
    tree.addSubscriber(Subscriber("Keitha", "31237", "Tariff B"));
    tree.addSubscriber(Subscriber("Rihanna", "32699", "Tariff C"));
    tree.addSubscriber(Subscriber("Joe", "47247", "Tariff A"));

    //Вывод всей базы
    tree.printDatabase();

    cout << "Введите номер телефона "; cin >> number;
    cout << endl << endl;

    Subscriber* subscriber = tree.findSubscriber(number);
    if (subscriber != nullptr) {
        cout << "Абонент найден: " << subscriber->name << ", " << subscriber->phone << ", " << subscriber->tariff << endl;
    }
    else {
        cout << "Абонент не найден" << endl;
    }
    cout << endl << endl;
    //Вывод самого популярного тарифа
    tree.printMostPopularTariff();
    return 0;
}