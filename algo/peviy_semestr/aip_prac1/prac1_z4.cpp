#include <iostream>
using namespace std;

int main() {
    int x = 0; float y = 0.0;
    cout << "Введите сумму рублей\n";
    cin >> y;
    cout << "Введите номер валюты: 1 - доллар, 2 - евро, 3 - юань\n";
    cin >> x;
    switch (x)
    { 
    case 1:
        cout << y << "рублей - это " << y / 80 << " долларов\n";
        break;
    case 2:
        cout << y << "рублей - это " << y / 95 << " евро\n";
        break;
    case 3:
        cout << y << "рублей - это " << y / 11 << " юаней\n";
        break;
    default:
        cout << "введите корректные данные\n";
}
}
// g++ prac1_z4.cpp -o prac1_z4
// ./prac1_z4