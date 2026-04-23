#include <iostream>
#include <random>
#include <string>

using namespace std;

int main(){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-99, 99);
    int N = 0;
    int num = 0;
    int first_num = 0;

    cout << "Введите N - количество строк и столбцов матрицы [NxN]: ";
    cin >> N;
    cout << endl;

    int matrix[N][N];

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

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
        num = matrix[i][j];
        if (num > 0){
            matrix[i][j] = 1;
        }
        else {
            matrix[i][j] = 0;
        }
        }
    }
    cout << endl;

    cout << "Заменили элементы на 0 и 1: " << endl << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Нижняя треугольная матрица: " << endl << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}