#include <iostream>
#include <string>

using namespace std;

class Drob
{
public:

    int chisl;
    unsigned int znam;

    Drob(int chisl, int znam)
    {
        this->chisl = chisl;
        this->znam = znam;
    }

    void print()
    {
        cout << chisl
             << "/"
             << znam
             << endl;
    }

    int NOD(int a, int b)
    {
        while (a && b)
        {
            int c = a % b;

            a = b;
            b = c;
        }

        return a + b;
    }

    void sokr()
    {
        int nod = NOD(chisl, znam);

        chisl /= nod;
        znam /= nod;
    }

    Drob operator+(Drob x)
    {
        Drob res(
            chisl * x.znam +
            x.chisl * znam,

            znam * x.znam
        );

        res.sokr();

        return res;
    }

    Drob operator-(Drob x)
    {
        Drob res(
            chisl * x.znam -
            x.chisl * znam,

            znam * x.znam
        );

        res.sokr();

        return res;
    }

    Drob operator*(Drob x)
    {
        Drob res(
            chisl * x.chisl,
            znam * x.znam
        );

        res.sokr();

        return res;
    }

    Drob operator/(Drob x)
    {
        Drob res(
            chisl * x.znam,
            znam * x.chisl
        );

        res.sokr();

        return res;
    }
};

Drob inputFraction(string name)
{
    int chisl;
    int znam;

    cout << "Введите числитель дроби "
         << name
         << ": ";

    cin >> chisl;

    cout << "Введите знаменатель дроби "
         << name
         << ": ";

    cin >> znam;

    return Drob(chisl, znam);
}

void printFractions(Drob a, Drob b)
{
    cout << "\nДробь a: ";
    a.print();

    cout << "Дробь b: ";
    b.print();

    cout << endl;
}

void mathOperations(Drob a, Drob b)
{
    Drob c = a + b;
    Drob d = a - b;
    Drob e = a * b;
    Drob f = a / b;

    cout << "a + b = ";
    c.print();

    cout << "a - b = ";
    d.print();

    cout << "a * b = ";
    e.print();

    cout << "a / b = ";
    f.print();
}

int main()
{
    setlocale(LC_ALL, "ru");

    Drob a = inputFraction("a");
    Drob b = inputFraction("b");

    printFractions(a, b);

    mathOperations(a, b);

    return 0;
}