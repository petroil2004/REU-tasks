#include <iostream>
#include <cmath>

using namespace std;

void read(double *x, double *eps) {
    cout << "Введите x: ";
    cin >> *x;
    cout << "Введите точность в формате 0.0001: ";
    cin >> *eps;
}

double sin_tailor(double x, double eps) {
    double temp = x;
    double sum = temp;
    int n = 0;
    while (fabs(temp) > eps) {
        double a = (-x * x) / ((2 * n + 2) * (2 * n + 3));
        temp = temp * a;
        sum += temp;
        n += 1;
    }
    return fabs(sum);
}

int main() {
    double result;
    double eps = 0;
    double x = 0;
    read(&x, &eps);
    result = sin_tailor(x, eps);
    cout << "Реальное значение sin: " << sin(x) << endl;
    cout << "Значение sin через ряд Тейлора: " << result << endl;
    return 0;
}