
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;
    BinaryTree() : root(nullptr) {}

    // Добавление элемента в бинарное дерево
    void add(int val) {
        TreeNode* newNode = new TreeNode(val);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        TreeNode* current = root;
        while (true) {
            if (val < current->val) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            }
            else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
        }
    }
    void printTree(TreeNode* node, int level = 0, char branch = ' ') {
        if (node == nullptr) {
            return;
        }
        printTree(node->right, level + 1, '/');
        for (int i = 0; i < level; i++) {
            cout << "   ";
        }
        cout << branch << "--" << node->val << endl;
        printTree(node->left, level + 1, '\\');
    }

    // Поиск элемента в бинарном дереве
    bool search(int val) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->val == val) {
                return true;
            }
            else if (val < current->val) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return false;
    }
    // Обход дерева (прямой, обратный, симметричный)
    void traversePreorder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->val << " ";
        traversePreorder(node->left);
        traversePreorder(node->right);
    }

    void traverseInorder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        traverseInorder(node->left);
        cout << node->val << " ";
        traverseInorder(node->right);
    }

    void traversePostorder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        traversePostorder(node->left);
        traversePostorder(node->right);
        cout << node->val << " ";
    }
    int findMax(TreeNode* node) {
        if (node == nullptr) {
            return -1;
        }
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->val;
    }

    int findMin(TreeNode* node) {
        if (node == nullptr) {
            return -1;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->val;
    }

    int findDistance(TreeNode* node, int n1, int n2) {
        if (node == nullptr) {
            return -1;
        }
        // Находим LCA (наименьший общий предок) n1 и n2
        TreeNode* lca = findLCA(node, n1, n2);
        if (lca == nullptr) {
            return -1;
        }
        // Находим расстояние от LCA до n1
        int dist1 = findLevel(lca, n1, 0);
        if (dist1 == -1) {
            return -1;
        }
        // Находим расстояние от LCA до n2
        int dist2 = findLevel(lca, n2, 0);
        if (dist2 == -1) {
            return -1;
        }
        // Суммируем расстояния и вычитаем удвоенную длину пути от LCA до одного из узлов
        return dist1 + dist2 - 2 * findLevel(lca, lca->val, 0);
    }

        // Вспомогательная функция для поиска уровня узла
        int findLevel(TreeNode* node, int n, int level) {
        if (node == nullptr) {
            return -1;
        }
        if (node->val == n) {
            return level;
        }
        int left = findLevel(node->left, n, level + 1);
        if (left == -1) {
            return findLevel(node->right, n, level + 1);
        }
        return left;
    }
    void deleteNode(int val) {
        root = deleteNodeHelper(root, val);
    }
    TreeNode* deleteNodeHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }
        else if (val < node->val) {
            node->left = deleteNodeHelper(node->left, val);
        }
        else if (val > node->val) {
            node->right = deleteNodeHelper(node->right, val);
        }
        else {
            // случай 1: узел не имеет потомков
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            // случай 2: узел имеет только одного потомка
            else if (node->left == nullptr) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
            }
            // случай 3: узел имеет двух потомков
            else {
                int minVal = findMin(node->right);
                node->val = minVal;
                node->right = deleteNodeHelper(node->right, minVal);
            }
        }
        return node;
    }
    TreeNode* findLCA(TreeNode* node, int n1, int n2) {
        if (node == nullptr) {
            return nullptr;
        }
        // Если текущий узел содержит один из искомых узлов, возвращаем его
        if (node->val == n1 || node->val == n2) {
            return node;
        }
        // Рекурсивно ищем LCA в левом и правом поддеревьях
        TreeNode* leftLCA = findLCA(node->left, n1, n2);
        TreeNode* rightLCA = findLCA(node->right, n1, n2);
        // Если оба поддерева вернули непустые значения, текущий узел является LCA
        if (leftLCA != nullptr && rightLCA != nullptr) {
            return node;
        }
        // Если только одно из поддеревьев вернуло непустое значение, продолжаем поиск в этом поддереве
        return (leftLCA != nullptr) ? leftLCA : rightLCA;
    }

    void clearTree(TreeNode* root) {
        if (!root) {
            return;
        }
        clearTree(root->left);
        clearTree(root->right);
        delete root;
    }

    void mixedTraversal(TreeNode* root) {
        std::stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* curr = st.top();
            st.pop();
            std::cout << curr->val << " ";

            if (curr->left) {
                st.push(curr->left);
            }

            if (curr->right) {
                st.push(curr->right);
            }
        }
    }
    void traverseDown(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        traverseDown(root->left);
        std::cout << root->val << " ";
        traverseDown(root->right);
    }
    int height(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftHeight = height(root->left);
        if (leftHeight == -1) {
            return -1;
        }
        int rightHeight = height(root->right);
        if (rightHeight == -1) {
            return -1;
        }
        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        return std::max(leftHeight, rightHeight) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
    void printLevelSum(TreeNode* root) {
        if (!root) {
            return; // обработка пустого дерева
        }
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        int levelSum = 0;
        int nodesLeftOnLevel = 1;
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            levelSum += node->val;
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
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
};

void writeTreeToFile(TreeNode* root, std::ofstream& fout) {
    if (root == nullptr) {
        fout << "# "; // используем символ # для обозначения пустого узла
        return;
    }
    fout << root->val << " "; // записываем значение узла
    writeTreeToFile(root->left, fout); // рекурсивно записываем левое поддерево
    writeTreeToFile(root->right, fout); // рекурсивно записываем правое поддерево
}

TreeNode* readTreeFromFile(std::ifstream& fin) {
    std::string val;
    fin >> val;
    if (val == "#") {
        return nullptr; // если встретили символ #, возвращаем nullptr
    }
    int num = std::stoi(val); // преобразуем строку в число
    TreeNode* root = new TreeNode(num); // создаем новый узел
    root->left = readTreeFromFile(fin); // рекурсивно считываем левое поддерево
    root->right = readTreeFromFile(fin); // рекурсивно считываем правое поддерево
    return root;
}

int main() {
    setlocale(LC_CTYPE, "rus");
    BinaryTree bt;
    for (;;) {
        int vibor;
        cout << endl << endl;
        cout << "1. Добавление элемента\n"
            << "2. Вывод дерева\n"
            << "3. Удаление элемента\n"
            << "4. Очистить дерево\n"
            << "5. Смешанный обход дерева\n"
            << "6. Нисходящий обход дерева\n"
            << "7. Проверка сбалансированности дерева\n"
            << "8. Запись дерева в файл\n"
            << "9. Чтение дерева из файла\n"
            << "10.Вывести сумму значений вершин по уровням\n"
            << "0. Выход\n";
        cout << "? ";
        cin >> vibor;
        cout << endl << endl;
        switch (vibor) {
        case 1: {
            int dobavl;
            cout << "Введите элемент дерева ";
            cin >> dobavl;
            while (dobavl != 0) {
                bt.add(dobavl);
                cout << "Введите элемент дерева ";
                cin >> dobavl;
            }
            break;
        }
        case 2: {
            bt.printTree(bt.root);
            break;
        }
        case 3: {
            int udal;
            cout << "Введите элемент дерева ";
            cin >> udal;
            bt.deleteNode(udal);
            break;
        }
        case 4: {
            bt.clearTree(bt.root);
            break;
        }
        case 5: {
            bt.mixedTraversal(bt.root);
            break;
        }
        case 6: {
            bt.traverseDown(bt.root);
            break;
        }
        case 7: {
            bool t = bt.isBalanced(bt.root);
            if (t == true) {
                cout << "Сбалансированно" << endl;
            }
            else {
                cout << "Не сбалансированно" << endl;
            }
            break;
        }
        case 8: {
            ofstream fout("tree.txt");
            writeTreeToFile(bt.root, fout);
            fout.close();
            break;
        }
        case 9: {
            ifstream fin("tree.txt");
            bt.root = readTreeFromFile(fin);
            fin.close();
            std::cout << "Считанное дерево:" << endl;
            bt.printTree(bt.root);
            break;
        }
        case 10: {
            bt.printLevelSum(bt.root);
            break;
        }
        case 0: {
            return 0;
            break;
        }
        }

    }
}