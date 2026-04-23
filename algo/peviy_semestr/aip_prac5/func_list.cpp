#include <iostream>
#include <cmath>
using namespace std;

void input(int a[], int b) {
    for (int i = 0; i < b; i++){
        cin >> a[i];
        cout << " ";
    }
    cout << endl;
}

void output(int a[], int b) {
    for (int i = 0; i < b; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

int min_search(int a[], int b) {
    int min = a[0];
    for (int i = 1; i < b; i++) {
        if (a[i] < min){
            min = a[i];
        }
    }
    return min;
}

int max_search(int a[], int b) {
    int max = a[0];
    for (int i = 1; i < b; i++) {
        if (a[i] > max){
            max = a[i];
        }
    }
    return max;
}

void bubble_sort(int a[], int b){
    for (int i = 0; i + 1 < b; i++){
        for (int j = 0; j + 1 < b; j++){
            if (a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void biggerThan(int a[], int b, int c){
    for (int i = 0; i < b; i++){
        if (a[i] > c){
            cout << a[i] << " ";
        }
    }
    cout << endl;
}

void negative_replace(int a[],int b){
    for (int i = 0; i < b; i++){
        if (a[i] < 0){
            a[i] = 0;
        }
    }
}

int sum(int a[], int b){
    int summary = 0;
    for (int i = 0; i < b; i++){
        summary += a[i];
    }
    return summary;
}

int multiply(int a[], int b){
    int mult = 1;
    for (int i = 0; i < b; i++){
        mult *= a[i];
    }
    return mult;
}

bool isPrime(int a){
    if (a < 2){
        return false;
    }
    if (a == 2){
        return true;
    }
    for (int i = 2; i < pow(a, 0.5) + 1; i++){
        if (a % i == 0){
            return false;
        }
    }
    return true;
}

int amountPrime(int a[], int b){
    int amount = 0;
    for (int i = 0; i < b; i++){
        if (isPrime(a[i])){
            amount += 1;
        }
    }
    return amount;
}

int menu(){
    int choice;
    int mass_size = 0;
    cout << endl << "Задайте размер массива: ";
    cin >> mass_size;
    cout << endl;
    int mass[mass_size];
    while (true){
        cout << endl << "МЕНЮ" << endl;
        cout << "1. Ввести массив" << endl;
        cout << "2. Вывести массив" << endl;
        cout << "3. Найти максимум" << endl;
        cout << "4. Найти минимум" << endl;
        cout << "5. Сортировка по возрастанию" << endl;
        cout << "6. Вывести элементы больше заданного" << endl;        
        cout << "7. Замена отрицательных" << endl;
        cout << "8. Вычислить сумму элементов массива" << endl;
        cout << "9. Вычислить произведение элементов массива" << endl;
        cout << "10. Посчитать количество простых чисел" << endl;
        cout << "0. Выход" << endl << endl;

        cout << "Выберите пункт: ";
        cin >> choice;
        cout << endl;

        switch (choice){
            case 1:
                cout << "Введите числа массива: ";
                input(mass, mass_size);
                break;
            case 2:
                cout << "Получившийся массив: ";
                output(mass, mass_size);
                break;
            case 3:
                cout << "Максимум: " << max_search(mass, mass_size) << endl;
                break;
            case 4:
                cout << "Минимум: " << min_search(mass, mass_size) << endl;
                break;
            case 5:
                bubble_sort(mass, mass_size);
                cout << "Массив отсортирован, выберите пункт 2 для вывода" << endl;
                break;
            case 6: {
                int num = 0;
                cout << "Введите число: ";
                cin >> num;
                cout << endl;
                cout << "Элементы больше заданного: " << endl;
                biggerThan(mass, mass_size, num);
                break;
            }
            case 7:
                negative_replace(mass, mass_size);
                cout << "Элементы заменены, выберите пункт 2 для вывода" << endl;
                break;
            case 8:
                cout << "Сумма элементов массива: " << sum(mass, mass_size) << endl;
                break;
            case 9:
                cout << "Произведение элементов массива: " << multiply(mass, mass_size) << endl;
                break;
            case 10:
                cout << "Количество простых чисел: " << amountPrime(mass, mass_size) << endl;
                break;
            case 0:
                return 0;
            default:
                cout << "Неверное значение, попробуйте ещё раз" << endl;
        }
    }
}