#include <iostream>
using namespace std;

class Tree {
public:
    int value;
    Tree *left, *right, *mom;
    Tree(int value, Tree* mom = NULL) {
        this->value = value; 
        this->mom = mom;
        left = right = NULL;
    }
    void printNode(int level) {
        for (int i = 0; i < level; i++) cout << "   ";
        cout << value << endl;
    }
};

Tree* root = NULL;
bool live = false;

int getHeight(Tree* node) {
    if (!node) return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

int getBalance(Tree* node) {
    if (!node) return 0;
    return getHeight(node->right) - getHeight(node->left);
}

Tree* rotateLeft(Tree* node) {
    Tree* newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left) newRoot->left->mom = node;
    newRoot->left = node;
    newRoot->mom = node->mom;
    node->mom = newRoot;
    return newRoot;
}

Tree* rotateRight(Tree* node) {
    Tree* newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right) newRoot->right->mom = node;
    newRoot->right = node;
    newRoot->mom = node->mom;
    node->mom = newRoot;
    return newRoot;
}

Tree* rotateRightLeft(Tree* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Tree* rotateLeftRight(Tree* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Tree* balanceSubtree(Tree* node) {
    if (!node) return node;
    int nodeBalance = getBalance(node);
    if (nodeBalance > 1) {
        int rightBalance = getBalance(node->right);
        if (rightBalance < 0) return rotateRightLeft(node);
        else return rotateLeft(node);
    }
    if (nodeBalance < -1) {
        int leftBalance = getBalance(node->left);
        if (leftBalance > 0) return rotateLeftRight(node);
        else return rotateRight(node);
    }
    return node;
}

Tree* add(Tree* node, int value) {
    if (!node) return new Tree(value);
    if (value > node->value) {
        node->right = add(node->right, value);
        if (node->right) node->right->mom = node;
    } else {
        node->left = add(node->left, value);
        if (node->left) node->left->mom = node;
    }
    return balanceSubtree(node);
}

Tree* add(int value) {
    root = add(root, value);
    live = true;
    return root;
}

void printTree(Tree* node, int level) {
    if (!node) return;
    printTree(node->right, level + 1);
    node->printNode(level);
    printTree(node->left, level + 1);
}

bool findValue(Tree* node, int value) {
    if (!node) return false;
    if (node->value == value) return true;
    if (value > node->value) return findValue(node->right, value);
    else return findValue(node->left, value);
}

int countNodes(Tree* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

Tree* findMinNode(Tree* node) {
    while (node && node->left) node = node->left;
    return node;
}

Tree* deleteNode(Tree* node, int value) {
    if (!node) return NULL;
    if (value < node->value) node->left = deleteNode(node->left, value);
    else if (value > node->value) node->right = deleteNode(node->right, value);
    else {
        if (!node->left || !node->right) {
            Tree* temp = node->left ? node->left : node->right;
            if (temp) temp->mom = node->mom;
            delete node;
            return temp;
        }
        Tree* temp = findMinNode(node->right);
        node->value = temp->value;
        node->right = deleteNode(node->right, temp->value);
    }
    return balanceSubtree(node);
}

Tree* removeCurrentNode(Tree* node) {
    if (!node->left || !node->right) {
        Tree* temp = node->left ? node->left : node->right;
        if (temp) temp->mom = node->mom;
        delete node;
        return temp;
    }
    Tree* temp = findMinNode(node->right);
    node->value = temp->value;
    node->right = deleteNode(node->right, temp->value);
    return node;
}

void deleteTree(Tree* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int menu() {
    cout << "\n0. Выход\n"
         << "1. Добавить элемент\n"
         << "2. Напечатать дерево\n"
         << "3. Найти элемент\n"
         << "4. Количество элементов\n"
         << "5. Удалить всё дерево\n"
         << "6. Удалить элемент\n";
    int a;
    cin >> a;
    return a;
}

void chooseAdd() {
    int value;
    cout << "Введите число: ";
    cin >> value;
    add(value);
}

void choosePrint() {
    if (live) printTree(root, 0);
    else cout << "Дерево пустое\n";
}

void chooseFind() {
    if (!live) {
        cout << "Дерево пустое\n";
        return;
    }
    int value;
    cout << "Введите число для поиска: ";
    cin >> value;
    cout << (findValue(root, value) ? "Найдено\n" : "Не найдено\n");
}

void chooseCount() {
    if (!live) cout << "Дерево пустое\n";
    else cout << "Количество элементов: " << countNodes(root) << endl;
}

void chooseDeleteTree() {
    if (live) {
        deleteTree(root);
        root = NULL;
        live = false;
    }
    cout << "Удалено / дерево пустое\n";
}

void chooseDeleteValue() {
    if (!live) {
        cout << "Дерево пустое\n";
        return;
    }
    int value;
    cout << "Введите число для удаления: ";
    cin >> value;
    root = deleteNode(root, value);
    if (root) root->mom = NULL;
    else live = false;
    cout << "Удалено (если существовало)\n";
}

void processAction(int choice) {
    if (choice == 1) chooseAdd();
    else if (choice == 2) choosePrint();
    else if (choice == 3) chooseFind();
    else if (choice == 4) chooseCount();
    else if (choice == 5) chooseDeleteTree();
    else if (choice == 6) chooseDeleteValue();
}

int main() {
    while (true) {
        int choice = menu();
        if (choice == 0) return 0;
        processAction(choice);
    }
}