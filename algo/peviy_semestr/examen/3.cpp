#include <iostream>
using namespace std;

int main(){
    int a;
    cout << "Введите любое число: " << endl;
    while (true){
        if (cin >> a){
            break;
        }
        cout << "Ошибка ввода, попробуйте еще раз\n";
        cin.clear();
        cin.ignore(999, '\n');
    }
    cout << "Введено: " << a << endl;

}