#include <iostream>
using namespace std;

int main() {
    int num = 0;
    int count = 1;
    cin >> num;
    if (num == 0) {
        cout << 1 << endl;
        return 0;
    }
    else if (num < 0) {
        cout << "Введите положительное число" << endl;
        cin >> num;
    }
    int fact = num;
    while (count < num) {
        fact = fact * count;
        count += 1;
    }
    cout << fact << endl;
}   