#include <iostream>
using namespace std;

int main() {
    float x = 0.0;
    cin >> x;

    if (!cin)
        cout << "некорректный ввод\n";
    else if (x > 0.0)
    {
        cout << "положительное\n";
    }
    else if (x < 0.0)
    {
        cout << "отрицательное\n";
    }
    else if (x == 0.0)
    {
        cout << "ноль\n";
    }

}
