#include <iostream>
using namespace std;

class Drob {
    public:
        int chislitel;
        int znamenatel;
        void print(){
            cout << chislitel << "/" << znamenatel << "\n";
            
        };

        Drob plus(Drob a){
            Drob b;
            b.chislitel = chislitel * a.znamenatel + znamenatel * a.chislitel;
            b.znamenatel = znamenatel * a.znamenatel;
            return b;
        };

        Drob minus(Drob a){
            Drob b;
            b.chislitel = chislitel * a.znamenatel - znamenatel * a.chislitel;
            b.znamenatel = znamenatel * a.znamenatel;
            return b;
        };

        Drob mult(Drob a){
            Drob b;
            b.chislitel = chislitel * a.chislitel;
            b.znamenatel = znamenatel * a.znamenatel;
            return b;
        };

        Drob divid(Drob a){
            Drob b;
            b.chislitel = chislitel * a.znamenatel;
            b.znamenatel = znamenatel * a.chislitel;
            return b;
        };
};

int main(){
    Drob z;
    z.chislitel = 10;
    z.znamenatel = 15;

    Drob v;
    v.chislitel = 5;
    v.znamenatel = 12;

    cout << "Исходные дроби: \n";
    cout << "z = ";
    z.print();
    cout << "v = ";
    v.print();
    cout << "\n";

    cout << "z + v = ";
    z.plus(v).print();

    cout << "z - v = ";
    z.minus(v).print();

    cout << "z * v = ";
    z.mult(v).print();

    cout << "z / v = ";
    z.divid(v).print();


};