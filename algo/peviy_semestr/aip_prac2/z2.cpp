#include <iostream>
using namespace std;

int main() {
    int m = 1;
    int d = 1;
    int a;
    int b;
    cout << "Введите первое число: " << endl;
    cin >> a;

    cout << "Введите второе число: " << endl;
    cin >> b;

    while (a == 0 && b == 0) {
        cout << "Введите хотя бы одно число, отличное от нуля " << endl;
        cout << "Введите первое число: " << endl;
        cin >> a;
        cout << "Введите второе число: " << endl;
        cin >> b;
    }
while (d <= max(a, b)) {
    if (a % d == 0 && b % d == 0) {
        m = max(m, d);
    }
    d++;
}
 cout << "Наибольший общий делитель: " << m << endl;
}