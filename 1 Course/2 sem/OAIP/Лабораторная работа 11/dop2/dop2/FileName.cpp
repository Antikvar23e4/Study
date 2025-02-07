#include<iostream>
#include <vector>

using namespace std;

struct node
{
    int key;
    node* parent;
    char color;
    node* left;
    node* right;
};
class RBtree
{
public:
    node* root;
    node* q;
    RBtree()
    {
        q = NULL;
        root = NULL;
    }
    void insert();
    void insertfix(node*);
    void leftrotate(node*);
    void rightrotate(node*);
    void del();
    node* successor(node*);
    void delfix(node*);
    void disp();
    void display(node*);
    void search();
    void findMinRedPath(node* current, vector<int>& path, int& minRedCount, int currentRedCount);
};
void RBtree::insert()
{
    int z, i = 0;
    cout << "\nВведите ключ: ";
    cin >> z;
    node* p, * q;
    node* t = new node;
    t->key = z;
    t->left = NULL;
    t->right = NULL;
    t->color = 'r';
    p = root;
    q = NULL;
    if (root == NULL)
    {
        root = t;
        t->parent = NULL;
    }
    else
    {
        while (p != NULL)
        {
            q = p;
            if (p->key < t->key)
                p = p->right;
            else
                p = p->left;
        }
        t->parent = q;
        if (q->key < t->key)
            q->right = t;
        else
            q->left = t;
    }
    insertfix(t);
}
void RBtree::insertfix(node* t)
{
    node* u;
    if (root == t)
    {
        t->color = 'b';
        return;
    }
    while (t->parent != NULL && t->parent->color == 'r')
    {
        node* g = t->parent->parent;
        if (g->left == t->parent)
        {
            if (g->right != NULL)
            {
                u = g->right;
                if (u->color == 'r')
                {
                    t->parent->color = 'b';
                    u->color = 'b';
                    g->color = 'r';
                    t = g;
                }
            }
            else
            {
                if (t->parent->right == t)
                {
                    t = t->parent;
                    leftrotate(t);
                }
                t->parent->color = 'b';
                g->color = 'r';
                rightrotate(g);
            }
        }
        else
        {
            if (g->left != NULL)
            {
                u = g->left;
                if (u->color == 'r')
                {
                    t->parent->color = 'b';
                    u->color = 'b';
                    g->color = 'r';
                    t = g;
                }
            }
            else
            {
                if (t->parent->left == t)
                {
                    t = t->parent;
                    rightrotate(t);
                }
                t->parent->color = 'b';
                g->color = 'r';
                leftrotate(g);
            }
        }
        root->color = 'b';
    }
}

void RBtree::del()
{
    if (root == NULL)
    {
        cout << "\nДерево пустое";
        return;
    }
    int x;
    cout << "\nВведите ключ: ";
    cin >> x;
    node* p;
    p = root;
    node* y = NULL;
    node* q = NULL;
    int found = 0;
    while (p != NULL && found == 0)
    {
        if (p->key == x)
            found = 1;
        if (found == 0)
        {
            if (p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }
    if (found == 0)
    {
        cout << "\nЭлемент не найден";
        return;
    }
    else
    {
        cout << "\nУдалённый элемент: " << p->key;
        cout << "\nЦвет: ";
        if (p->color == 'b')
            cout << "Чёрный\n";
        else
            cout << "Красный\n";

            if (p->parent != NULL)
                cout << "\nРодитель: " << p->parent->key;
            else
                cout << "\nРодителя нет  ";
        if (p->right != NULL)
            cout << "\nПравый дочерний: " << p->right->key;
        else
            cout << "\nНет правого дочернего  ";
        if (p->left != NULL)
            cout << "\nЛевый дочерний: " << p->left->key;
        else
            cout << "\nНет левого дочернего  ";
        cout << "\nЭлемент удалён";
        if (p->left == NULL || p->right == NULL)
            y = p;
        else
            y = successor(p);
        if (y->left != NULL)
            q = y->left;
        else
        {
            if (y->right != NULL)
                q = y->right;
            else
                q = NULL;
        }
        if (q != NULL)
            q->parent = y->parent;
        if (y->parent == NULL)
            root = q;
        else
        {
            if (y == y->parent->left)
                y->parent->left = q;
            else
                y->parent->right = q;
        }
        if (y != p)
        {
            p->color = y->color;
            p->key = y->key;
        }
        if (y->color == 'b')
            delfix(q);
    }
}

void RBtree::delfix(node* p)
{
    node* s;
    while (p != root && p->color == 'b')
    {
        if (p->parent->left == p)
        {
            s = p->parent->right;
            if (s->color == 'r')
            {
                s->color = 'b';
                p->parent->color = 'r';
                leftrotate(p->parent);
                s = p->parent->right;
            }
            if (s->right->color == 'b' && s->left->color == 'b')
            {
                s->color = 'r';
                p = p->parent;
            }
            else
            {
                if (s->right->color == 'b')
                {
                    s->left->color == 'b';
                    s->color = 'r';
                    rightrotate(s);
                    s = p->parent->right;
                }
                s->color = p->parent->color;
                p->parent->color = 'b';
                s->right->color = 'b';
                leftrotate(p->parent);
                p = root;
            }
        }
        else
        {
            s = p->parent->left;
            if (s->color == 'r')
            {
                s->color = 'b';
                p->parent->color = 'r';
                rightrotate(p->parent);
                s = p->parent->left;
            }
            if (s->left->color == 'b' && s->right->color == 'b')
            {
                s->color = 'r';
                p = p->parent;
            }
            else
            {
                if (s->left->color == 'b')
                {
                    s->right->color = 'b';
                    s->color = 'r';
                    leftrotate(s);
                    s = p->parent->left;
                }
                s->color = p->parent->color;
                p->parent->color = 'b';
                s->left->color = 'b';
                rightrotate(p->parent);
                p = root;
            }
        }
        p->color = 'b';
        root->color = 'b';
    }
}

void RBtree::leftrotate(node* p)
{
    if (p->right == NULL)
        return;
    else
    {
        node* y = p->right;
        if (y->left != NULL)
        {
            p->right = y->left;
            y->left->parent = p;
        }
        else
            p->right = NULL;
        if (p->parent != NULL)
            y->parent = p->parent;
        if (p->parent == NULL)
            root = y;
        else
        {
            if (p == p->parent->left)
                p->parent->left = y;
            else
                p->parent->right = y;
        }
        y->left = p;
        p->parent = y;
    }
}
void RBtree::rightrotate(node* p)
{
    if (p->left == NULL)
        return;
    else
    {
        node* y = p->left;
        if (y->right != NULL)
        {
            p->left = y->right;
            y->right->parent = p;
        }
        else
            p->left = NULL;
        if (p->parent != NULL)
            y->parent = p->parent;
        if (p->parent == NULL)
            root = y;
        else
        {
            if (p == p->parent->left)
                p->parent->left = y;
            else
                p->parent->right = y;
        }
        y->right = p;
        p->parent = y;
    }
}

node* RBtree::successor(node* p)
{
    node* y = NULL;
    if (p->left != NULL)
    {
        y = p->left;
        while (y->right != NULL)
            y = y->right;
    }
    else
    {
        y = p->right;
        while (y->left != NULL)
            y = y->left;
    }
    return y;
}

void RBtree::disp()
{
    display(root);
}
void RBtree::display(node* p)
{
    if (root == NULL)
    {
        cout << "\nДерево пустое";
        return;
    }
    if (p != NULL)
    {
        cout << "\n Ключ: " << p->key;
        cout << "\n Цвет: ";
        if (p->color == 'b')
            cout << "Чёрный";
        else
            cout << "Красный";
        if (p->parent != NULL)
            cout << "\n Родитель: " << p->parent->key;
        else
            cout << "\n Родителя нет  ";
        if (p->right != NULL)
            cout << "\n Правый дочерний: " << p->right->key;
        else
            cout << "\n Нет правого дочернего  ";
        if (p->left != NULL)
            cout << "\n Левый дочерний: " << p->left->key;
        else
            cout << "\n Нет левого дочернего.  ";
        if (p->left)
        {
            cout << "\nЛево.\n";
            display(p->left);
        }
        if (p->right)
        {
            cout << "\nПраво.\n";
            display(p->right);
        }
        
    }
}
void RBtree::search()
{
    if (root == NULL)
    {
        cout << "\nДерево пустое\n";
        return;
    }
    int x;
    cout << "\n Введите ключ: ";
    cin >> x;
    node* p = root;
    int found = 0;
    while (p != NULL && found == 0)
    {
        if (p->key == x)
            found = 1;
        if (found == 0)
        {
            if (p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }
    if (found == 0)
        cout << "\nЭлемент не найлден";
    else
    {
        cout << "\n\t Найденный элемент: ";
        cout << "\n Ключ: " << p->key;
        cout << "\n Цвет: ";
        if (p->color == 'b')
            cout << "Чёрный";
        else
            cout << "Красный";
        if (p->parent != NULL)
            cout << "\n Родитель: " << p->parent->key;
        else
            cout << "\n Родителя нет  ";
        if (p->right != NULL)
            cout << "\n Правый дочерний: " << p->right->key;
        else
            cout << "\n Нет правого дочернего  ";
        if (p->left != NULL)
            cout << "\n Левый дочерний: " << p->left->key;
        else
            cout << "\n Нет левого дочернего  ";
        cout << endl;

    }
}
void RBtree::findMinRedPath(node* current, vector<int>& path, int& minRedCount, int currentRedCount)
{
    if (current == NULL) {
        return;
    }
    if (current->color == 'R') {
        currentRedCount++;
    }
    if (current->left == NULL && current->right == NULL) {
        if (currentRedCount < minRedCount) {
            path.clear();
            minRedCount = currentRedCount;
        }
        if (currentRedCount == minRedCount) {
            path.push_back(current->key);
        }
        return;
    }
    findMinRedPath(current->left, path, minRedCount, currentRedCount);
    findMinRedPath(current->right, path, minRedCount, currentRedCount);
}



int main()
{
    setlocale(LC_CTYPE, "rus");
    int ch, y = 0;
    RBtree obj;
    do
    {
        cout << "\n 1. Вставка элемента ";
        cout << "\n 2. Удаление элемента";
        cout << "\n 3. Поиск элемента";
        cout << "\n 4. Вывод дерева ";
        cout << "\n 5. Путь от корня к некоторому листу, содержащий минимальное количество красных вершин ";
        cout << "\n 6. Выход ";
        cout << "\nВаш выбор: ";
        cin >> ch;
        switch (ch)
        {
        case 1: obj.insert();
            cout << "\nЭлемент вставлен\n";
            break;
        case 2: obj.del();
            break;
        case 3: obj.search();
            break;
        case 4: obj.disp();
            break;
        case 6: y = 1;
            break;
        case 5: {
            vector<int> path;
            int minRedCount = INT_MAX;
            obj.findMinRedPath(obj.root, path, minRedCount, 0);
            cout << "Путь от корня к некоторому листу, содержащий минимальное количество красных вершин: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i] << " ";
            }
            cout << endl;            break;
        }
        default: cout << "\nНеправильный выбор";
        }
        cout << endl;

    } while (y != 1);
    return 1;
}