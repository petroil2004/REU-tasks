#include <iostream>
using namespace std;

struct Product {
    string name;
    double price;
    int stock;
    string category;
};

int main() {
    cout << endl;
    int count = 0;
    const int n = 6;
    Product products[n];

    products[0].name = "nescafe";
    products[0].price = 1211.99;
    products[0].stock = 62;
    products[0].category = "coffee";

    products[1].name = "alpen_gold";
    products[1].price = 99.99;
    products[1].stock = 233;
    products[1].category = "chocolate";

    products[2].name = "lemon";
    products[2].price = 52.99;
    products[2].stock = 87;
    products[2].category = "fruit";

    products[3].name = "apple";
    products[3].price = 27.99;
    products[3].stock = 185;
    products[3].category = "fruit";

    products[4].name = "lipton";
    products[4].price = 1235.99;
    products[4].stock = 228;
    products[4].category = "tea";

    products[5].name = "shedraya_dusha";
    products[5].price = 2125.99;
    products[5].stock = 374;
    products[5].category = "chocolate";

    for (int i=0; i < n; i++) {
        if (products[i].price > 1000) {
            cout << products[i].name << " - " << products[i].price << " rub\n";
        }
        count += products[i].stock;
    }
    cout << endl << "Всего - " << count << " единиц на складе\n";
}