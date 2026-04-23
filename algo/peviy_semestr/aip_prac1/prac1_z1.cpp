#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    float x, y;
    cin >> x;
    cin >> y;
    if (x == 0.0 || y == 0.0)
        cout << "точка на оси\n";
    else if (x > 0.0 && y > 0.0)
    {
        cout << "точка в первой четверти\n";
    }
    else if (x < 0.0 && y > 0.0)
    {
        cout << "точка во второй четверти\n";
    }
    else if (x < 0.0 && y < 0.0)
    {
        cout << "точка в третьей четверти\n";
    }
    else if (x > 0.0 && y < 0.0)
    {
        cout << "точка в четвертой четверти\n";
    }
}
