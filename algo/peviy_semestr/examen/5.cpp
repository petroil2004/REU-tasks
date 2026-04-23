#include <iostream>
using namespace std;


int fact(int n){
    if (n <= 1){
        return 1;
    }
    return n * fact(n-1);
}

int main(){
    int digit;
    cout << "Введите цифру (0-9): ";
    cin >> digit;
    cout << "Факториал числа " << digit << " равен: " << fact(digit) << endl;
}