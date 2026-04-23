#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

int main() {
    
    int k_str;
    cout << "Введите кол-во строк\n";
    cin >> k_str;
    
    int i = 1;
    int j = 1;
    
    // Первый отступ
    cout << setw(2) << " ";


    // Заголовок
    while (j - 1 != k_str) {
        cout << setw(4) << j;
        j +=1;
    }
    cout << endl;
    
    
    while (i - 1 != k_str) {
        int stolb = 1;
        
        cout << i << " ";
        while (stolb-1 != k_str) {
            cout << setw(4) << stolb*i;
            stolb +=1;
            
        }
        cout << endl;
        i += 1;
            
        
    }
    
    
    
}