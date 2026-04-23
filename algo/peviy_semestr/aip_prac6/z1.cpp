#include <iostream>
using namespace std;


int main() {
    char mass[128];
    cout << endl << "ВВЕДИТЕ СЛОВА (ЛАТИНИЦЕЙ), РАЗДЕЛЯЯ ИХ ПРОБЕЛАМИ: " << endl << endl;
    cin.getline(mass, 128, '\n');
    int st = 0;
    int max_len = 0;
    int fin;

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
                bool repeat = false;
                for (int a = st; a <= fin; a++) {
                    if (repeat) break;
                    for (int b = a + 1; b <= fin; b++) {
                        if (mass[a] == mass[b]) {
                            repeat = true;
                            break;
                        }
                    }
                }
                if (!repeat && len > max_len) {
                    max_len = len;
                }
            }
            st = i + 1;
        }
    }

    cout << endl << "Слово максимальной длины без повторяющихся символов состоит из: " \
        << max_len << " символов" << endl << endl;
}
