#include <iostream>
using namespace std;

bool isPrime(int n){
    if (n <= 1){
        return false;
    }
    for (int i = 2; i * i <= n; i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    char a;
    cout << "Введите число: ";
    while (cin.get(a)){
        if (a == '\n'){
            break;
        }
        cout << '\n' << a << " - простое? " << isPrime(a - '0') << endl;
    }

}