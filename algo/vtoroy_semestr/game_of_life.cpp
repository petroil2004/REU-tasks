#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


const int GRANDMA_HEAL = 15;
const int GRANDMA_DAMAGE = 5;

const int DOC_HEAL = 20;
const int DOC_DAMAGE = 10;

const int MUS_HEAL = 10;
const int MUS_DAMAGE = 15;

const int CITY_DAMAGE = 7;


class People
{
protected:

    string name;
    int age;
    int HP;

public:

    People()
    {
        name = "NoName";
        age = 0;
        HP = 100;
    }

    People(string name, int age)
    {
        this->name = name;
        this->age = age;
        HP = 100;
    }

    string GetName()
    {
        return name;
    }

    bool isAlive()
    {
        return HP > 0;
    }

    void print()
    {
        cout << name
             << " | age: "
             << age
             << " | HP: "
             << HP
             << endl;
    }

    void damage(int x)
    {
        HP -= x;

        if (HP < 0)
            HP = 0;
    }

    void heal(int x)
    {
        HP += x;

        if (HP > 100)
            HP = 100;
    }

    virtual void act(People* x)
    {
        cout << name
             << " ничего не делает с "
             << x->GetName()
             << endl;
    }
};

class GrandMa : public People
{
public:

    GrandMa(string name, int age)
        : People(name, age)
    {
        HP = 90;
    }

    void act(People* x)
    {
        cout << "Бабушка "
             << name
             << " печет пирожки для "
             << x->GetName()
             << endl;

        x->heal(GRANDMA_HEAL);

        damage(GRANDMA_DAMAGE);
    }
};

class Doc : public People
{
public:

    Doc(string name, int age)
        : People(name, age)
    {
        HP = 100;
    }

    void act(People* x)
    {
        cout << "Доктор "
             << name
             << " лечит "
             << x->GetName()
             << endl;

        x->heal(DOC_HEAL);

        damage(DOC_DAMAGE);
    }
};

class Mus : public People
{
public:

    Mus(string name, int age)
        : People(name, age)
    {
        HP = 80;
    }

    void act(People* x)
    {
        cout << "Музыкант "
             << name
             << " играет для "
             << x->GetName()
             << endl;

        x->heal(MUS_HEAL);

        damage(MUS_DAMAGE);
    }
};

void createCity(vector<People*> &city)
{
    city.push_back(new GrandMa("Alla", 80));
    city.push_back(new Doc("Oleg", 50));
    city.push_back(new Mus("Igor", 30));
    city.push_back(new Mus("Nikita", 25));
    city.push_back(new Doc("Sergey", 45));
    city.push_back(new GrandMa("Galina", 77));
}

void printCity(vector<People*> city)
{
    for (int i = 0; i < city.size(); i++)
    {
        city[i]->print();
    }

    cout << endl;
}

void randomAction(vector<People*> &city)
{
    int a = rand() % city.size();
    int b = rand() % city.size();

    while (a == b)
    {
        b = rand() % city.size();
    }

    city[a]->act(city[b]);
}

void tiredCity(vector<People*> &city)
{
    for (int i = 0; i < city.size(); i++)
    {
        city[i]->damage(CITY_DAMAGE);
    }
}

void deleteDead(vector<People*> &city)
{
    for (int i = 0; i < city.size(); i++)
    {
        if (!city[i]->isAlive())
        {
            cout
                << city[i]->GetName()
                << " умер..."
                << endl;

            delete city[i];

            city.erase(city.begin() + i);

            i--;
        }
    }
}

void lifeCycle(vector<People*> &city)
{
    int day = 1;

    while (city.size() > 1)
    {
        cout
            << "===== День "
            << day
            << " ====="
            << endl;

        randomAction(city);

        tiredCity(city);

        printCity(city);

        deleteDead(city);

        day++;
    }
}

void clearMemory(vector<People*> &city)
{
    for (int i = 0; i < city.size(); i++)
    {
        delete city[i];
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    srand(time(0));

    vector<People*> city;

    createCity(city);

    printCity(city);

    lifeCycle(city);

    cout << "Победитель:\n";

    city[0]->print();

    clearMemory(city);

    return 0;
}