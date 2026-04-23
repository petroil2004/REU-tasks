#include <iostream>
#include <random>
#include <string>

using namespace std;

int main(){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-99, 99);
    int N = 0;
    cout << "Введите количество строк матрицы: ";
    cin >> N;
    cout << endl;
    int matrix[N][N];
    int maxNums[N];
    int num = 0;
    int first_num = 0;
    int index = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = dist(gen);
        }
    }

    cout << "Исходная матрица: " << endl << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
        num = matrix[i][j];
        if (i == 0) {
            cout << num << "   ";
        }
        else {
            first_num = matrix[0][j];
            if (to_string(first_num).length() == to_string(num).length()) {
                cout << num << "   ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == 2) {
                cout << num << "     ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == 1) {
                cout << num << "    ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == -1) {
                cout << num << "  ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == -2) {
                cout << num << " ";
            }
        }
    }
    cout << endl;
    }

    cout << endl;

    for (int i = 0; i < N; i++) {
        int Imax = -99999999;
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > Imax) {
                Imax = matrix[i][j];
                index = j;
            }
        }
        maxNums[i] = Imax;
        swap(matrix[i][i], matrix[i][index]);

    }
    
    cout << "Изменённая матрица: " << endl << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
        num = matrix[i][j];
        if (i == 0) {
            cout << num << "   ";
        }
        else {
            first_num = matrix[0][j];
            if (to_string(first_num).length() == to_string(num).length()) {
                cout << num << "   ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == 2) {
                cout << num << "     ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == 1) {
                cout << num << "    ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == -1) {
                cout << num << "  ";
            }
            else if (to_string(first_num).length() - to_string(num).length() == -2) {
                cout << num << " ";
            }
        }
    }
    cout << endl;
    }

    cout << endl << "Наибольшие числа в каждой из строк: " << endl << endl;

    for (int i = 0; i < N; i++) {
        cout << maxNums[i] << " ";
    }
    cout << endl;


}

