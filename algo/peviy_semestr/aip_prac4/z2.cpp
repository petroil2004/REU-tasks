#include <iostream>
#include <random>
#include <string>

using namespace std;

int main(){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-99, 99);
    int N = 0;
    int M = 0;
    int k = 0;
    int max_i = 0;
    int max_j = 0;
    int max_el = 0;
    int num = 0;
    int first_num = 0;

    cout << "Введите количество строк матрицы: ";
    cin >> N;
    cout << endl;
    cout << "Введите количество столбцов матрицы: ";
    cin >> M;
    cout << endl;
    cout << "Введите k: ";
    cin >> k;
    cout << endl;

    int matrix[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = dist(gen);
        }
    }

    cout << "Исходная матрица: " << endl << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
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
            for (int j = 0; j < M; j++) {
                if (abs(matrix[i][j]) > abs(max_el)) {
                    max_el = matrix[i][j];
                    max_i = i;
                    max_j = j;
                }
        }
    }

    cout << "Максимальный элемент по модулю: " << max_el << endl;
    cout << "Строка: " << max_i + 1 << endl;
    cout << "Столбец: " << max_j + 1 << endl << endl;

    for (int j=0; j < M; j++) {
        swap(matrix[max_i][j], matrix[k-1][j]);
    }

    cout << "Поменяли строки в матрице: " << endl << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
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

    for (int i=0; i < N; i++) {
        swap(matrix[i][max_j], matrix[i][k-1]);
    }

    cout << "Поменяли столбцы в матрице: " << endl << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
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
    cout << "k-тая строка и стобец: " << k << endl;
}   

