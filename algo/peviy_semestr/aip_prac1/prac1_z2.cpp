#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int x;
    cin >> x;
    if (x >= 0 && x <= 39)
        cout << "оценка - плохо\n";
    else if (x >= 40 && x <= 59)
    {
        cout << "оценка - удовлетворительно\n";
    }
    else if (x >= 60 && x <= 79)
    {
        cout << "оценка - хорошо\n";
    }
    else if (x >= 80 && x <= 100)
    {
        cout << "оценка - отлично\n";
    }
}
