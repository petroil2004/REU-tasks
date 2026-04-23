#include <iostream>
using namespace std;

int main() {
    char a;
    cout << "Введите число: " << endl;
    
    while (cin.get(a)) {
        if (a == '\n') {
            break;
        }
        
        // Работаем с уже прочитанным символом
        if (a >= '0' && a <= '9') {
            if ((a - '0') % 2 == 0) {
                a = '0';  // '==' было ошибкой, нужно '='
            }
        }
        cout << a;
    }
    cout << '\n';
    
    return 0;
}