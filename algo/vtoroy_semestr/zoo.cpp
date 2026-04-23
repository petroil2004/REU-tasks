#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    string name;
    int age;
    void printInfo() {
        cout << "Имя животного: " << name << endl;
        cout << "Возраст животного: " << age << endl;
    }
    Animal(string name, int age) {
        this->name = name; 
        this->age = age;
    }
};

class Zebra: public Animal {
public:
    int lanesNum;
    void makeSound() {
        cout << "Издаёт звук: и-го-го" << endl;
    }
    Zebra(string name, int age, int lanesNum) : Animal(name, age) {
        this->lanesNum = lanesNum; 
    }
};

class Camel: public Animal {
public:
    string color;
    void makeSound() {
        cout << "Издаёт звук: тьфу" << endl;
    }
    Camel(string name, int age, string color) : Animal(name, age) {
        this->color = color; 
    }
};

class Kangaroo: public Animal {
public:
    int childrenInBagNum;
    void makeSound() {
        cout << "Издаёт звук: руу" << endl;
    }
    Kangaroo(string name, int age, int childrenInBagNum) : Animal(name, age) {
        this->childrenInBagNum = childrenInBagNum;
    }
};

class Rooster: public Animal {
public:
    bool agressive;
    void makeSound() {
        cout << "Животное издаёт звук: ку-ка-ре-ку" << endl;
    }
    Rooster(string name, int age, bool agressive) : Animal(name, age) {
        this->agressive = agressive;
    }
};

int main() {
    Animal* zoo[5];
    zoo[0] = new Zebra("Marti", 6, 24);
    zoo[1] = new Camel("Maga", 11, "orange");
    zoo[2] = new Kangaroo("Poprygun", 4, 1);
    zoo[3] = new Rooster("Petya", 2, false);
    zoo[4] = new Rooster("Vasya", 3, true);

    cout << '\n';

    for (int i = 0; i < 5; i++) {
        zoo[i]->printInfo();
    }

    for (int i = 0; i < 5; i++) {
        delete zoo[i];
    }

    cout << '\n';
    
    Zebra* first = new Zebra("Marti", 6, 24);
    Camel* second = new Camel("Maga", 11, "orange");
    Kangaroo* third = new Kangaroo("Poprygun", 4, 1);
    Rooster* fourth = new Rooster("Petya", 2, false);
    Rooster* fifth = new Rooster("Vasya", 3, false);

    first->makeSound();
    second->makeSound();
    third->makeSound();
    fourth->makeSound();
    fifth->makeSound();

    cout << '\n';

    delete first;
    delete second;
    delete third;
    delete fourth;
    delete fifth;

    return 0;
}