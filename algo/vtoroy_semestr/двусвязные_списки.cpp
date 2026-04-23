#include <iostream>
using namespace std;

class STUDENT {
    
public:
    string name;
    int age;
    float grade;

    STUDENT* next, *mom;

    void Show() {
        cout << "Имя: " << name << " Возраст: "
             << age << " Рейтинг: " << grade << endl;
    };

    STUDENT(string name, int age, float grade) {
        this->name = name;
        this->age = age;
        this->grade = grade;
        this->next = NULL;
        this->mom = NULL;
    }
};

STUDENT* first = NULL;

void printSTUDENT(STUDENT* f) {
    f->Show();
    if (f->next != first) printSTUDENT(f->next);
}

void swap_name(string name, STUDENT* f) {
    if (first == NULL) {
        cout << "Список пуст\n";
        return;
    }

    if (first->next == first) {
        cout << "В списке один элемент\n";
        return;
    }

     if (first->next->next == first) {
        if (first->name == name || first->next->name == name) {
            first = first->next;
            cout << "Студент " << name << " поменян местами с предыдущим\n";
        } else {
            cout << "Элемент не найден\n";
        }
        return;
    }

    if (f->next->name == name) {
        STUDENT* prev = f;
        STUDENT* curr = f->next;
        STUDENT* before = prev->mom;
        STUDENT* next = curr->next;

        before->next = curr;
        curr->mom = before;

        curr->next = prev;
        prev->mom = curr;

        prev->next = next;
        next->mom = prev;

        if (prev == first) {
            first = curr;
        }
        else if (curr == first) {
            first = prev;
        }
        cout << "Студент " << name << " поменян местами с предыдущим\n";
        return;
    }

    if (f->next == first) {
        cout << "Элемент не найден\n";
        return;
    }

    swap_name(name, f->next);
}

void add_last_student(STUDENT* f, string name, int age, float grade) {
    if (f->next != first) add_last_student(f->next, name, age, grade);
    else {
        STUDENT* new_el = new STUDENT(name, age, grade);
        new_el->next = first;
        new_el->mom = f;
        f->next = new_el;
        first->mom = new_el;
    }
}

void delete_all(STUDENT* f) {
    if (f->next != first) delete_all(f->next);
    delete f;
}

void delete_el(int del_num) {
    if (del_num < 0) {
        cout << "Ошибка, введите положительное число\n";
        return;
    }

    if (first == NULL) {
        cout << "Список пуст\n";
        return;
    }

    if (del_num == 0) {
        if (first->next == first) {
            delete first;
            first = NULL;
            return;
        }

        STUDENT* temp = first;
        first->mom->next = first->next;
        first->next->mom = first->mom;
        first = first->next;
        delete temp;
        return;
    }

    STUDENT* child = first;
    int st = 0;

    while (child->next != first && st < del_num) {
        child = child->next;
        st++;
    }

    if (st != del_num) {
        cout << "Такого индекса нет\n";
        return;
    }

    child->mom->next = child->next;
    child->next->mom = child->mom;
    delete child;
}

int menu() {
    cout << "0. EXIT\n"
         << "1. Добавить студента в начало\n"
         << "2. Добавить студента в середину\n"
         << "3. Добавить студента в конец\n"
         << "4. PRINT STUDENTS\n"
         << "5. Удалить всех студентов\n"
         << "6. Удалить студента в середине\n"
         << "7. Посчитать количество элементов списка\n"
         << "8. Поменять местами с предыдущим\n";
    int a;
    cin >> a;
    return a;
}

int count(STUDENT* f){
    int c = 1;
    while (f->next != first) {
        f = f->next;
        c += 1;
    }
    return c;
};

int main() {
    bool live = false;
    string name;
    int age;
    float grade;

    while (true) {
        switch (menu()) {
            case 0:
                return 0;
                break;
            case 1:
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите возраст: ";
                cin >> age;
                cout << "Введите рейтинг: ";
                cin >> grade;

                if (!live) {
                    first = new STUDENT(name, age, grade);
                    first->next = first;
                    first->mom = first;
                    live = true;
                } else {
                    STUDENT* new_el = new STUDENT(name, age, grade);
                    new_el->next = first;
                    new_el->mom = first->mom;
                    first->mom->next = new_el;
                    first->mom = new_el;
                    first = new_el;
                }
                break;

            case 2: {
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите возраст: ";
                cin >> age;
                cout << "Введите рейтинг: ";
                cin >> grade;

                if (!live) {
                    first = new STUDENT(name, age, grade);
                    first->next = first;
                    first->mom = first;
                    live = true;
                    break;
                }

                int index;
                cout << "Введите индекс (начиная с 0): ";
                cin >> index;

                if (index < 0) {
                    cout << "Ошибка, введите положительное число\n";
                    break;
                }

                if (index == 0) {
                    STUDENT* new_el = new STUDENT(name, age, grade);
                    new_el->next = first;
                    new_el->mom = first->mom;
                    first->mom->next = new_el;
                    first->mom = new_el;
                    first = new_el;
                    break;
                }

                STUDENT* current = first;
                int i = 1;

                while (current->next != first && i < index) {
                    current = current->next;
                    i++;
                }

                STUDENT* new_el = new STUDENT(name, age, grade);
                new_el->next = current->next;
                new_el->mom = current;
                current->next->mom = new_el;
                current->next = new_el;
                break;
            }

            case 3:
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите возраст: ";
                cin >> age;
                cout << "Введите рейтинг: ";
                cin >> grade;

                if (!live) {
                    first = new STUDENT(name, age, grade);
                    first->next = first;
                    first->mom = first;
                    live = true;
                } else {
                    add_last_student(first, name, age, grade);
                }
                break;

            case 4:
                if (live) printSTUDENT(first);
                else cout << "Список пуст\n";
                break;

            case 5:
                if (live) {
                    delete_all(first);
                    first = NULL;
                    live = false;
                }
                cout << "Удалено / список пуст\n";
                break;

            case 6: {
                cout << "Введите индекс (начиная с 0): ";
                int index;
                cin >> index;

                if (!live) {
                    cout << "Список пуст\n";
                    break;
                }

                delete_el(index);

                if (first == NULL) live = false;

                cout << "Удалено\n";
                break;
            }
            
            case 7: {
                if (!live) cout << "Список пуст\n";
                else cout << "Количество элементов: " << count(first) << endl;
                break;
            }
            
            case 8: {
                cout << "Введите имя студента, которого хотите поменять с предыдущим: ";
                string change;
                cin >> change;
                swap_name(change, first);
                break;
            }

            default:
                cout << "Ошибка\n";
                break;
            
        }
    }
}