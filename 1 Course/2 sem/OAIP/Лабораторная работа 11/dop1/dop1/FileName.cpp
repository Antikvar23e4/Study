
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

// ���������, ����������� ��������
struct Subscriber {
    string name;  // ���
    string phone;  // ����� ��������
    string tariff;  // �����

    // ����������� �� ���������
    Subscriber() {}

    // ����������� � �����������
    Subscriber(string name, string phone, string tariff) {
        this->name = name;
        this->phone = phone;
        this->tariff = tariff;
    }
};

// �����, �������������� �������� ������
class BinaryTree {
public:
    // ���������, ����������� ���� ������
    struct Node {
        Subscriber subscriber;  // �������
        Node* left;  // ����� �������
        Node* right;  // ������ �������

        // ����������� � �����������
        Node(Subscriber subscriber, Node* left = nullptr, Node* right = nullptr) {
            this->subscriber = subscriber;
            this->left = left;
            this->right = right;
        }
    };

    Node* root;  // ������ ������

    // ����������� ������� ��� ���������� ���� � ������
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

    // ����������� ������� ��� ������ ����� ������ �� �����
    void printTree(Node* node) {
        if (node != nullptr) {
            printTree(node->left);
            cout << "���: " << node->subscriber.name << endl;
            cout << "����� ��������: " << node->subscriber.phone << endl;
            cout << "�����: " << node->subscriber.tariff << endl;
            cout << endl;
            printTree(node->right);
        }
    }

    // ����������� ������� ��� ������ �������� �� ������ ��������
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

    // ����������� ������� ��� �������� ����� ��������� �� ������ ������
    void countTariffs(Node* node, map<string, int>& countMap) {
        if (node != nullptr) {
            countTariffs(node->left, countMap);
            countMap[node->subscriber.tariff]++;
            countTariffs(node->right, countMap);
        }
    }


    // ����������� �� ���������
    BinaryTree() {
        root = nullptr;
    }

    // ������� ��� ���������� �������� � ������
    void addSubscriber(Subscriber subscriber) {
        root = addNode(root, subscriber);
    }

    // ������� ��� ������ ���� ���� ������ �� �����
    void printDatabase() {
        printTree(root);
    }

    // ������� ��� ������ �������� �� ������ ��������
    Subscriber* findSubscriber(string phone) {
        return findSubscriber(root, phone);
    }

    // ������� ��� ������ �������� ��������������� ������
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

        cout << "�������� �������������� �����: " << mostPopularTariff << endl;
    }
};

// ������� ��� ������ ���� ������ �� �����
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

// ������� ��� ������ ���� ������ � ����
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

    //���������� �������� � ����
    tree.addSubscriber(Subscriber("Henry", "45370", "Tariff A"));
    tree.addSubscriber(Subscriber("Keitha", "31237", "Tariff B"));
    tree.addSubscriber(Subscriber("Rihanna", "32699", "Tariff C"));
    tree.addSubscriber(Subscriber("Joe", "47247", "Tariff A"));

    //����� ���� ����
    tree.printDatabase();

    cout << "������� ����� �������� "; cin >> number;
    cout << endl << endl;

    Subscriber* subscriber = tree.findSubscriber(number);
    if (subscriber != nullptr) {
        cout << "������� ������: " << subscriber->name << ", " << subscriber->phone << ", " << subscriber->tariff << endl;
    }
    else {
        cout << "������� �� ������" << endl;
    }
    cout << endl << endl;
    //����� ������ ����������� ������
    tree.printMostPopularTariff();
    return 0;
}