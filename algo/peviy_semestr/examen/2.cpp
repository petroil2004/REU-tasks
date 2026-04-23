#include <iostream>
using namespace std;

int sumDig(int a){
    int summa = 0;
    if (a < 0){
        a = -a;
    }
    while (a){
        summa += a % 10;
        a = a / 10;
    }
    return summa;
}

int main(){
    int z, x, c = 0;
    cout << "Введите два или три числа: ";
    cin >> z >> x;
    int s1 = sumDig(z);
    int s2 = sumDig(x);

    int maxnum = s1;

    if (s1 < s2){
        maxnum = s2;
    }

    if (cin.peek() != '\n'){
        cin >> c;
        int s3 = sumDig(c);
        if (s3 > maxnum){
            maxnum = s3;
        }
    }

    cout << "Максимальная сумма цифр среди введённых чисел: " << maxnum << endl;

}