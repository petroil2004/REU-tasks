#include <iostream>
using namespace std;

int main(){
    cout << "Введите два или три числа:\n";
    int a, b, c = 0;
    cin >> a >> b;
    int maxnum = a;
    int minnum = b;
    if (a < b) {
        maxnum = b;
        minnum = a;
    }
    if (cin.peek() != '\n'){
        cin >> c;
        if (c > maxnum) {
            maxnum = c;
        }
        if (c < minnum) {
            minnum = c;
        }
    }
    cout << "Наибольшее: " << maxnum << endl;
    cout << "Наименьшее: " << minnum << endl;
}