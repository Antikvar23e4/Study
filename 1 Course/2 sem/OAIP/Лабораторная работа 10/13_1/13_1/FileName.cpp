#include <iostream>
#include <queue>
using namespace std;

struct Tree {
    int key;
    char text[5];
    Tree* Left;
    Tree* Right;
};

Tree* makeTree(Tree* Root);       //Создание дерева
Tree* list(int i, char* s);       //Создание нового элемента
Tree* insertElem(Tree* Root, int key, char* s);  //Добавление нового элемента
Tree* search(Tree* n, int key);   //Поиск элемента по ключу 
Tree* delet(Tree* Root, int key); //Удаление элемента по ключу
void view(Tree* t, int level);    //Вывод дерева 
int count(Tree* t, char letter);  //Подсчет количества слов
void delAll(Tree* t);             //Очистка дерева
void printNodesOnLevel(Tree* Root, int level);
int countNodesOnLevel(Tree* Root, int level);
void printNodes(vector<int> nodes);
int countRightLeaves(Tree* root);
int countRightLeaves(Tree* root); // 2
int countNodesWithValueK(Tree* node, int k); // 9
int sumOfKeys(Tree* node); // 10
int countEvenKeys(Tree* node); // 12

int c = 0;         //количество слов
Tree* Root = NULL;   //указатель корня


Tree* makeTree(Tree* Root) {
    int key;
    char s[5];
    cout << "Конец ввода - отрицательное числоnn";
    if (Root == NULL) {
        cout << "Введите ключ корня: ";
        cin >> key;
        cout << "Введите слово корня: ";
        cin >> s;
        Root = list(key, s);
    }
    while (1) {
        cout << "nВведите ключ: ";
        cin >> key;
        if (key < 0) break;
        cout << "Введите слово: ";
        cin >> s;
        insertElem(Root, key, s);
    }
    return Root;
}

Tree* list(int i, char* s) {
    Tree* t = new Tree[sizeof(Tree)];
    t->key = i;
    for (i = 0; i < 5; i++)
        *((t->text) + i) = *(s + i);
    t->Left = t->Right = NULL;
    return t;
}

Tree* insertElem(Tree* t, int key, char* s) {
    Tree* Prev = 0;
    int find = 0;
    while (t && !find) {
        Prev = t;
        if (key == t->key)
            find = 1;
        else if (key < t->key)
            t = t->Left;
        else
            t = t->Right;
    }
    if (!find) {
        t = list(key, s);
        if (key < Prev->key)
            Prev->Left = t;
        else
            Prev->Right = t;
    }
    return t;
}

void printLevelSum(Tree* root) {
    queue<Tree*> q;
    q.push(root);
    int level = 0;
    while (!q.empty()) {
        int size = q.size();
        int sum = 0;
        for (int i = 0; i < size; i++) {
            Tree* node = q.front();
            q.pop();
            sum += node->key;
            if (node->Left) q.push(node->Left);
            if (node->Right) q.push(node->Right);
        }
        cout << "Level " << level << " sum: " << sum << endl;
        level++;
    }
}

int main() {
    setlocale(0, "Russian");
    Tree* root = NULL;
    root = makeTree(root);
    printLevelSum(root);
    return 0;
}
