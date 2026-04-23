#include <iostream>
using namespace std;

int main() {
    cout << "Введите 5 целых чисел: " << endl;
    int mass[5];
    const int x = 5;
    for (int i = 0; i < x; i++) 
        cin >> mass[i];
    cout << "Получившийся список: " << endl;
    for (int i = 0; i < x; i++) 
        cout << mass[i] << " ";
    cout << endl;
    int sum = 0;
    for (int i = 0; i < x; i++) 
        sum += mass[i];
    cout << "Среднее арифметическое: " << sum / 5 << endl;
    cout << "Индексы четных элементов: " << endl;
    for (int i = 0; i < x; i++){
        if (mass[i] % 2 == 0) {
            cout << i << " ";
        }
    }
    cout << endl;
}