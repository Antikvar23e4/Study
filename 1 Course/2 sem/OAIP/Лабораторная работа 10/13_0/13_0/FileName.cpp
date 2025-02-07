
// 2 9 10
#include <iostream>
#include <queue>
using namespace std;
struct Tree          //������
{
    int key;         //����
    char text[5];    //����� - �� ����� 4 ����
    Tree* Left, * Right;
};

Tree* makeTree(Tree* Root);       //�������� ������
Tree* list(int i, char* s);       //�������� ������ ��������
Tree* insertElem(Tree* Root, int key, char* s);  //���������� ������ ��������
Tree* search(Tree* n, int key);   //����� �������� �� ����� 
Tree* delet(Tree* Root, int key); //�������� �������� �� �����
void view(Tree* t, int level);    //����� ������ 
int count(Tree* t, char letter);  //������� ���������� ����
void delAll(Tree* t);             //������� ������
void levelOrderTraversal(Tree* root); // 3
int countRightLeaves(Tree* root);
int countRightLeaves(Tree* root); // 2
int countNodesWithValueK(Tree* node, int k); // 9
int sumOfKeys(Tree* node); // 10
int countEvenKeys(Tree* node); // 12
void printLevelSum(Tree* p1); // ����

int c = 0;         //���������� ����
Tree* Root = NULL;   //��������� �����

void main()
{
    setlocale(0, "Russian");
    int key, choice, n;
    Tree* rc; char s[5], letter;
    for (;;)
    {
        cout << "1 -  �������� ������\n";
        cout << "2 -  ���������� ��������\n";
        cout << "3 -  ����� �� �����\n";
        cout << "4 -  �������� ��������\n";
        cout << "5 -  ����� ������\n";
        cout << "6 -  ������� ���������� ����\n";
        cout << "7 -  ������� ������\n";
        cout << "8 -  ����� ���� ��������� ������ �� �������\n";
        cout << "9 -  (2var)����� ���������� ������� ������, ������� �������� ������� ��������� ���������\n";
        cout << "10 -  (9var) ����� ���������� ������ ������, �������� ������� ����� k\n";
        cout << "11 -  (10var) ����� ����� �������� ���� ������ ������� ������\n";
        cout << "12 -  ������� ����� �������� ������ ������� ������\n";
        cout << "0 -  �����\n";
        cout << "��� �����?\n";
        cin >> choice;
        cout << "\n";
        switch (choice)
        {
        case 1:  Root = makeTree(Root);  break;
        case 2:  cout << "\n������� ����: "; cin >> key;
            cout << "������� �����: "; cin >> s;
            insertElem(Root, key, s); break;
        case 3:  cout << "\n������� ����: ";  cin >> key;
            rc = search(Root, key);
            cout << "��������� �����= ";
            puts(rc->text); break;
        case 4:  cout << "\n������� ��������� ����: "; cin >> key;
            Root = delet(Root, key);  break;
        case 5:  if (Root->key >= 0)
        {
            cout << "������ ��������� �� 90 ����. �����" << endl;
            view(Root, 0);
        }
              else cout << "������ ������\n"; break;
        case 6:  cout << "\n������� �����: "; cin >> letter;
            n = count(Root, letter);
            cout << "���������� ����, ������������ � ����� " << letter;
            cout << " ����� " << n << endl; break;
        case 7:  delAll(Root); break;
        case 8: levelOrderTraversal(Root); break;
        case 9: {
            int ress = countRightLeaves(Root);
            cout << "���������� ������� ������, ������� �������� ������� ��������� ��������� ����� " << ress << endl;
            break;
        }
        case 10: {
            int k;
            cout << "������� k "; cin >> k;
            int numNodesWithK = countNodesWithValueK(Root, k);
            cout << "���������� ������ �� ��������� " << k << ": " << numNodesWithK << endl;
            break;
        }
        case 11: {
            int sum = sumOfKeys(Root);
            cout << "����� �������� ������ ���� ������ ������: " << sum << endl;
            break;
        }
        case 12: {
            printLevelSum(Root);
            break;
        }
        case 0:  exit(0);
        }
    }
}

Tree* makeTree(Tree* Root)    //�������� ������
{
    int key; char s[5];
    cout << "����� ����� - ������������� �����\n\n";
    if (Root == NULL)  // ���� ������ �� �������
    {
        cout << "������� ���� �����: "; cin >> key;
        cout << "������� ����� �����: "; cin >> s;
        Root = list(key, s);  // ��������� ��������� �� ������
    }
    while (1)                //���������� ���������
    {
        cout << "\n������� ����: ";  cin >> key;
        if (key < 0) break;       //������� ������ (���� < 0)   
        cout << "������� �����: ";  cin >> s;
        insertElem(Root, key, s);
    }
    return Root;
}
Tree* list(int i, char* s)     //�������� ������ ��������
{
    Tree* t = new Tree[sizeof(Tree)];
    t->key = i;
    for (i = 0; i < 5; i++)
        *((t->text) + i) = *(s + i);
    t->Left = t->Right = NULL;
    return t;
}

Tree* insertElem(Tree* Root, int key, char* s)
{
    if (!Root)   //���� ������ ������
    {
        Root = list(key, s);   //������� ������
        return Root;
    }
    Tree* temp = Root;   //��������� ��������� �� ������
    while (temp)
    {
        if (key < temp->key)  //���� ���� ������, ��� � ������� ����, ���� �����
        {
            if (temp->Left)
            {
                temp = temp->Left;
            }
            else
            {
                temp->Left = list(key, s);  //���� ����� ��������� ������, ������� ����� �������
                return Root;
            }
        }
        else   //����� ���� ������
        {
            if (temp->Right)
            {
                temp = temp->Right;
            }
            else
            {
                temp->Right = list(key, s);  //���� ������ ��������� ������, ������� ����� �������
                return Root;
            }
        }
    }
    return Root;   //���������� ��������� �� ������ ������
}

Tree* delet(Tree* Root, int key)  //�������� �������� �� �����
{  // Del, Prev_Del - ��������� ������� � ��� ���������� ;
  // R, Prev_R - �������, �� ������� ���������� ���������, � ��� ��������; 
    Tree* Del, * Prev_Del, * R, * Prev_R;
    Del = Root;
    Prev_Del = NULL;
    while (Del != NULL && Del->key != key)//����� �������� � ��� �������� 
    {
        Prev_Del = Del;
        if (Del->key > key)
            Del = Del->Left;
        else
            Del = Del->Right;
    }
    if (Del == NULL)              // ������� �� ������
    {
        puts("\n��� ������ �����");
        return Root;
    }
    if (Del->Right == NULL) // ����� �������� R ��� ������
        R = Del->Left;
    else
        if (Del->Left == NULL)
            R = Del->Right;
        else
        {
            Prev_R = Del; //����� ������ ������� �������� � ����� ���������
            R = Del->Left;
            while (R->Right != NULL)
            {
                Prev_R = R;
                R = R->Right;
            }
            if (Prev_R == Del) // ������ ������� ��� ������ R � ��� �������� Prev_R 
                R->Right = Del->Right;
            else
            {
                R->Right = Del->Right;
                Prev_R->Right = R->Left;
                R->Left = Prev_R;
            }
        }
    if (Del == Root) Root = R;  //�������� ����� � ������ ��� �� R
    else
        // ��������� R �������������� � �������� ���������� ����
        if (Del->key < Prev_Del->key)
            Prev_Del->Left = R; // �� ����� ����� 
        else
            Prev_Del->Right = R;  // �� ������ �����
    int tmp = Del->key;
    cout << "\n������ ������� � ������ " << tmp << endl;
    delete Del;
    return Root;
}

Tree* search(Tree* n, int key)  //����� �������� �� ����� 
{
    Tree* rc = n;
    if (rc != NULL)
    {
        if (key < (key, n->key))
            rc = search(n->Left, key);
        else
            if (key > (key, n->key))
                rc = search(n->Right, key);
    }
    else
        cout << "��� ������ ��������\n";
    return rc;
}

int count(Tree* t, char letter) //������� ���������� ����
{
    if (t)
    {
        count(t->Right, letter);
        if (*(t->text) == letter)
            c++;
        count(t->Left, letter);
    }
    return c;
}

void view(Tree* t, int level) //����� ������ 
{
    if (t)
    {
        view(t->Right, level + 1);  //����� ������� ���������
        for (int i = 0; i < level; i++)
            cout << "   ";
        int tm = t->key;
        cout << tm << ' ';
        puts(t->text);
        view(t->Left, level + 1);  //����� ������ ���������
    }
}

void delAll(Tree* t) //������� ������
{
    if (t != NULL)
    {
        delAll(t->Left);
        delAll(t->Right);
        delete t;
    }
}

void levelOrderTraversal(Tree* root)
{
    if (root == nullptr) {
        return;
    }

    queue<Tree*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            Tree* node = q.front();
            q.pop();

            cout << "(" << node->key << ", " << node->text << ") ";

            if (node->Left != nullptr) {
                q.push(node->Left);
            }

            if (node->Right != nullptr) {
                q.push(node->Right);
            }
        }

        cout << endl;
    }
}

int countRightLeaves(Tree* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->Right == NULL && root->Left == NULL) {
        return 1;
    }
    return countRightLeaves(root->Left) + countRightLeaves(root->Right);
}

int countNodesWithValueK(Tree* node, int k) {
    if (node == NULL) {
        return 0;
    }
    int count = 0;
    if (node->key == k) {
        count++;
    }
    count += countNodesWithValueK(node->Left, k);
    count += countNodesWithValueK(node->Right, k);
    return count;
}

int sumOfKeys(Tree* node) {
    if (node == NULL) {  // ������� ������: ������ ������
        return 0;
    }
    else {  // ����������� ������: �� ������ ������
        return node->key + sumOfKeys(node->Left) + sumOfKeys(node->Right);
    }
}

int countEvenKeys(Tree* node) {
    if (node == NULL) {
        return 0;
    }

    int count = 0;
    if (node->key % 2 == 0) {
        count++;
    }

    count += countEvenKeys(node->Left);
    count += countEvenKeys(node->Right);

    return count;
}

void printLevelSum(Tree* p1) {
    if (p1 == nullptr) {
        return; // ��������� ������� ������
    }
    queue<Tree*> q;
    q.push(p1);
    int level = 0;
    int levelSum = 0;
    int nodesLeftOnLevel = 1;
    while (!q.empty()) {
        Tree* currentNode = q.front();
        q.pop();
        levelSum += currentNode->key;
        if (currentNode->Left != nullptr) {
            q.push(currentNode->Left);
        }
        if (currentNode->Right != nullptr) {
            q.push(currentNode->Right);
        }
        nodesLeftOnLevel--;
        if (nodesLeftOnLevel == 0) {
            cout << "Level " << level << " sum: " << levelSum << endl;
            level++;
            levelSum = 0;
            nodesLeftOnLevel = q.size();
        }
    }
}