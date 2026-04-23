#include <iostream>
using namespace std;

class STUDENT {
    string name; 
    int age; 
    float grade; 
public:
    STUDENT* next;
    string GetName(){
        return name;
    };
    int GetAge() const{
        return age;
    };
    float GetGrade() const{
        return grade;
    };
    void SetName(string n){
        name = n;
    };
    void SetAge(int a){
        age = a;
    };
    void SetGrade(float g){
        grade = g;
    };
    void Set(string n, int a, float g){
        name = n;
        age = a;
        grade = g;
    };
    void Show(){
        cout << "Имя: " << name << " Возраст: " << 
        age << " Рейтинг: " << grade << endl;
    };
    STUDENT () {}
    STUDENT(string n, int a, float g){
        name = n;
        age = a;
        grade = g;
    }
};

void printSTUDENT(STUDENT* f){
    f->Show();
    if (f->next != NULL) printSTUDENT(f->next);
}

void addSTUDENT(STUDENT* f, string n, int a, float g){
    if (f->next != NULL) addSTUDENT(f->next, n, a, g);
    else
        f->next = new STUDENT(n, a, g);
}

void delete_all(STUDENT* f){
    if (f->next != NULL) delete_all(f->next);
    delete f;
}

void delete_el(STUDENT* child, int del_num, int st, STUDENT* mom){
    if (del_num > st && child->next != NULL) delete_el(child->next, del_num, st+1, child);
    if (del_num == st) mom->next = child->next;
    if (st > del_num) return;
}

int menu(){
    cout << "0. EXIT\n" << 
    "1. Добавить студента в начало\n" <<
    "2. Добавить студента в середину\n" <<
    "3. Добавить студента в конец\n" <<
    "4. PRINT STUDENTS\n" <<
    "5. Удалить всех студентов\n" <<
    "6. Удалить студента в середине\n";
    int a;
    cin >> a;
    return a;
}

int main(){
    STUDENT* first = new STUDENT();
    bool live = false;
    string n;
    int a;
    float g;
    while (true){
        switch(menu()){
            case 0:
                return 0;
                break;
            case 1:
                cout << "Введите имя: ";
                cin >> n;
                cout << "Введите возраст: ";
                cin >> a;
                cout << "Введите рейтинг: ";
                cin >> g;
                if (!live){
                    first = new STUDENT(n, a, g);
                    live = true;
                } else {
                    STUDENT* newFirst = new STUDENT(n, a, g);
                    newFirst->next = first;
                    first = newFirst;
                }
                break;
            case 2: {
                cout << "Введите имя: ";
                cin >> n;
                cout << "Введите возраст: ";
                cin >> a;
                cout << "Введите рейтинг: ";
                cin >> g;
                if (!live){
                    first = new STUDENT(n, a, g);
                    live = true;
                    break;
                }
                int index;
                cout << "Введите индекс (начиная с 0): ";
                cin >> index;
                if (index == 0) {
                    STUDENT* newFirst = new STUDENT(n, a, g);
                    newFirst->next = first;
                    first = newFirst;
                    break;
                }
                STUDENT* current = first;
                int i = 1;
                while (current->next != NULL && i < index) {
                    current = current->next;
                    i++;
                }
                STUDENT* new_el = new STUDENT(n, a, g);
                new_el->next = current->next;
                current->next = new_el;
                break;
            }
            case 3:
                cout << "Введите имя: ";
                cin >> n;
                cout << "Введите возраст: ";
                cin >> a;                
                cout << "Введите рейтинг: ";
                cin >> g;       
                if (!live){
                    first = new STUDENT(n, a, g);
                    live = true;
                }
                else addSTUDENT(first, n, a, g);
                break;
            case 4:
                if (live) printSTUDENT(first);
                else cout << "Cписок пуст\n";
                break;
            case 5:
                if (live) delete_all(first);
                live = false;
                cout << "Удалено / список пуст\n";
                break;
            case 6:
                cout << "Введите индекс (начиная с 0): ";
                int index;
                cin >> index;
                if (index < 0) cout << "Ошибка, введите положительное число\n";
                if (index > 0) delete_el(first, index, 0, NULL);
                if (index == 0) {
                    STUDENT* temp = first;
                    if (first->next != NULL) first = first->next;
                    else live = false;
                    delete temp;
                }
                cout << "Удалено\n";
                break;
            default: cout << "Ошибка\n";
                break;
        }
    }
}