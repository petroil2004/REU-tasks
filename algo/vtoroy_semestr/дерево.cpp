#include <iostream>
using namespace std;

class Tree {
public:
    int x;
    Tree *left, *right, *mom;

    Tree(int x, Tree* mom = NULL) {
        this->x = x;
        this->mom = mom;
        left = NULL;
        right = NULL;
    }

    void Show(int level) {
        for (int i = 0; i < level; i++) cout << "   ";
        cout << x << endl;
    }
};

Tree* root = NULL;

void add(Tree* r, int x) {
    if (x > r->x) {
        if (r->right != NULL) add(r->right, x);
        else r->right = new Tree(x, r);
    } else {
        if (r->left != NULL) add(r->left, x);
        else r->left = new Tree(x, r);
    }
}

void print_tree(Tree* r, int level) {
    if (r == NULL) return;

    print_tree(r->right, level + 1);
    r->Show(level);
    print_tree(r->left, level + 1);
}

void delete_tree(Tree* r) {
    if (r == NULL) return;

    delete_tree(r->left);
    delete_tree(r->right);
    delete r;
}

int count(Tree* r) {
    if (r == NULL) return 0;
    return 1 + count(r->left) + count(r->right);
}

bool find(Tree* r, int x) {
    if (r == NULL) return false;
    if (r->x == x) return true;

    if (x > r->x) return find(r->right, x);
    else return find(r->left, x);
}

Tree* find_min(Tree* r) {
    while (r->left != NULL) r = r->left;
    return r;
}

Tree* delete_node(Tree* r, int x) {
    if (r == NULL) return NULL;

    if (x < r->x) {
        r->left = delete_node(r->left, x);
        if (r->left) r->left->mom = r;
    } else if (x > r->x) {
        r->right = delete_node(r->right, x);
        if (r->right) r->right->mom = r;
    } else {
        if (r->left == NULL && r->right == NULL) {
            delete r;
            return NULL;
        } else if (r->left == NULL) {
            Tree* temp = r->right;
            temp->mom = r->mom;
            delete r;
            return temp;
        } else if (r->right == NULL) {
            Tree* temp = r->left;
            temp->mom = r->mom;
            delete r;
            return temp;
        } else {
            Tree* temp = find_min(r->right);
            r->x = temp->x;
            r->right = delete_node(r->right, temp->x);
            if (r->right) r->right->mom = r;
        }
    }
    return r;
}

int menu() {
    cout << "\n0. EXIT\n"
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

bool live = false;

void add_element() {
    int x;
    cout << "Введите число: ";
    cin >> x;

    if (!live) {
        root = new Tree(x);
        live = true;
    } else {
        add(root, x);
    }
}

void print_element() {
    if (!live) cout << "Дерево пустое\n";
    else print_tree(root, 0);
}

void find_element() {
    if (!live) {
        cout << "Дерево пустое\n";
        return;
    }

    int x;
    cout << "Введите число для поиска: ";
    cin >> x;

    if (find(root, x)) cout << "Найдено\n";
    else cout << "Не найдено\n";
}

void count_element() {
    if (!live) cout << "Дерево пустое\n";
    else cout << "Количество элементов: " << count(root) << endl;
}

void delete_all() {
    if (live) {
        delete_tree(root);
        root = NULL;
        live = false;
    }
    cout << "Удалено / дерево пустое\n";
}

void delete_element() {
    if (!live) {
        cout << "Дерево пустое\n";
        return;
    }

    int x;
    cout << "Введите число для удаления: ";
    cin >> x;

    root = delete_node(root, x);

    if (root) root->mom = NULL;
    else live = false;

    cout << "Удалено (если существовало)\n";
}

void action(int choice) {
    switch (choice) {
        case 1: add_element(); break;
        case 2: print_element(); break;
        case 3: find_element(); break;
        case 4: count_element(); break;
        case 5: delete_all(); break;
        case 6: delete_element(); break;
        default: cout << "Ошибка\n";
    }
}

int main() {
    while (true) {
        int choice = menu();
        if (choice == 0) return 0;
        action(choice);
    }
}