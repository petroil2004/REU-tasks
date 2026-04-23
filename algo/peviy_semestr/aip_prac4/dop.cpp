#include <iostream>
#include <iomanip> 


using namespace std;

int main() {
    const int size = 10; 

    cout << "\033[46m" << "   " << "\033[0m" << "|";
    for (int j = 1; j <= size; j++)
        cout << "\033[46m" << setw(4) << j << "\033[0m";        
    cout << "\n--------------------------------------------\n";

    for (int i = 1; i <= size; i++) {
        cout << "\033[46m" << setw(2) << i << " "<< "\033[0m" << "|";
        for (int j = 1; j <= size; j++) {
            if (i == j || i == 10 || j == 10) {
                cout << "\033[45m" << setw(4) << i * j << "\033[0m";
            }
            else if ((i == 5 && j < i) || (j == 5 && i < j)) {
                cout << "\033[42m" << setw(4) << i * j << "\033[0m";
            }
            else if ((i == 8 && j < i) || (j == 8 && i < j)) {
                cout << "\033[43m" << setw(4) << i * j << "\033[0m";
            }
            else {
                cout << setw(4) << i * j;
            }
        }
        cout << '\n';
    }
}