#include <iostream>
using namespace std;


int main() {
    char mass[128];
    cout << endl << "ВВЕДИТЕ СЛОВА (ЛАТИНИЦЕЙ), РАЗДЕЛЯЯ ИХ ПРОБЕЛАМИ: " << endl << endl;
    cin.getline(mass, 128, '\n');
    int st = 0;
    int max_len = 0;
    int fin;
    int number = 1;
    int max_number;
    int count = 0;

    for (int i = 0; mass[i] != '\0'; i++) {
        if (mass[i] == ' ' || mass[i+1] == '\0') {
            if (mass[i] == ' ' ) {
                fin = i - 1;
            }
            else {
                fin = i;
            }
            int len = fin - st + 1;
            if (len > 0) {
                bool palindrom = true;
                for (int a = st, b = fin; a <= fin; a++, b--) {
                    if (mass[a] != mass[b]) {
                        palindrom = false;
                    }
                }
                if (palindrom) {
                    count += 1;
                    if (len > max_len) {
                        max_len = len;
                        max_number = number;
                    }
                }
            }
            st = i + 1;
            number += 1;
        }
    }


    cout << endl << "НОМЕР САМОГО ДЛИННОГО ПАЛИНДРОМА: " << max_number << endl << endl;
    cout << endl << "НОМЕР САМОГО ДЛИННОГО ПАЛИНДРОМА (СРЕДИ ПАЛИНДРОМОВ): " << count << endl << endl;
}
