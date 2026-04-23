#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const char FILE_NAME[] = "products.dat";

struct Product {
    char name[80];
    long article;
    int quantity;
    double price;
    char discount;
};

Product* db = nullptr;
int dbSize = 0;
bool dbLoaded = false;

void clearDB() {
    delete[] db;
    db = nullptr;
    dbSize = 0;
    dbLoaded = true;
}

void inputString(const char* msg, char* dest, int size) {
    do {
        cout << msg;
        cin.ignore();
        cin.getline(dest, size);
    } while (strlen(dest) == 0);
}

Product inputProduct() {
    Product p;

    inputString("Наименование: ", p.name, 80);

    do {
        cout << "Артикул: ";
        cin >> p.article;
    } while (p.article <= 0);

    do {
        cout << "Количество: ";
        cin >> p.quantity;
    } while (p.quantity < 0);

    do {
        cout << "Цена: ";
        cin >> p.price;
    } while (p.price <= 0);

    do {
        cout << "Скидка (0-100): ";
        cin >> p.discount;
    } while (p.discount < 0 || p.discount > 100);

    return p;
}


void saveDB() {
    FILE* f = fopen(FILE_NAME, "wb");
    if (!f) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    fwrite(&dbSize, sizeof(int), 1, f);
    fwrite(db, sizeof(Product), dbSize, f);
    fclose(f);

    cout << "База данных сохранена\n";
}

void loadDB() {
    FILE* f = fopen(FILE_NAME, "rb");
    if (!f) {
        cout << "Файл не найден\n";
        return;
    }

    clearDB();
    fread(&dbSize, sizeof(int), 1, f);
    db = new Product[dbSize];
    fread(db, sizeof(Product), dbSize, f);
    fclose(f);

    dbLoaded = true;
    cout << "База данных загружена\n";
}


void addProduct() {
    Product p = inputProduct();

    Product* temp = new Product[dbSize + 1];
    for (int i = 0; i < dbSize; i++)
        temp[i] = db[i];

    temp[dbSize] = p;

    delete[] db;
    db = temp;
    dbSize++;
}

void printAll() {
    cout << "\nАртикул  Наименование  Цена  Кол-во  Скидка\n";
    for (int i = 0; i < dbSize; i++) {
        cout << db[i].article << "  "
             << db[i].name << "  "
             << db[i].price << "  "
             << db[i].quantity << "  "
             << (int)db[i].discount << "%\n";
    }
}

int findByArticle(long art) {
    for (int i = 0; i < dbSize; i++)
        if (db[i].article == art)
            return i;
    return -1;
}

void deleteProduct(int index) {
    for (int i = index; i < dbSize - 1; i++)
        db[i] = db[i + 1];
    dbSize--;
}

void printDiscounted() {
    for (int i = 0; i < dbSize; i++)
        if (db[i].discount > 0)
            cout << db[i].name << "\n";
}

void printOutOfStock() {
    for (int i = 0; i < dbSize; i++)
        if (db[i].quantity == 0)
            cout << db[i].name << "\n";
}


int cmpName(const void* a, const void* b) {
    return strcmp(((Product*)a)->name, ((Product*)b)->name);
}
int cmpArticle(const void* a, const void* b) {
    return ((Product*)a)->article - ((Product*)b)->article;
}
int cmpQuantity(const void* a, const void* b) {
    return ((Product*)a)->quantity - ((Product*)b)->quantity;
}
int cmpPrice(const void* a, const void* b) {
    double diff = ((Product*)a)->price - ((Product*)b)->price;
    return (diff > 0) - (diff < 0);
}

void sortMenu() {
    int c;
    cout << "1-Наименование 2-Артикул 3-Количество 4-Цена: ";
    cin >> c;

    switch (c) {
        case 1: qsort(db, dbSize, sizeof(Product), cmpName); break;
        case 2: qsort(db, dbSize, sizeof(Product), cmpArticle); break;
        case 3: qsort(db, dbSize, sizeof(Product), cmpQuantity); break;
        case 4: qsort(db, dbSize, sizeof(Product), cmpPrice); break;
    }
}


int main() {
    int cmd;

    do {
        cout << "\n1.Создать БД\n2.Загрузить БД\n";
        if (dbLoaded) {
            cout << "3.Сохранить\n4.Добавить\n5.Показать все\n";
            cout << "6.Поиск по артикулу\n7.Товары со скидкой\n";
            cout << "8.Товары без наличия\n9.Сортировка\n";
        }
        cout << "0.Выход\n> ";
        cin >> cmd;

        switch (cmd) {
            case 1: clearDB(); break;
            case 2: loadDB(); break;
            case 3: if (dbLoaded) saveDB(); break;
            case 4: if (dbLoaded) addProduct(); break;
            case 5: if (dbLoaded) printAll(); break;
            case 6: {
                long a;
                cout << "Артикул: ";
                cin >> a;
                int i = findByArticle(a);
                if (i >= 0) {
                    cout << "1-Изменить 2-Удалить: ";
                    int x; cin >> x;
                    if (x == 1) db[i] = inputProduct();
                    if (x == 2) deleteProduct(i);
                }
                break;
            }
            case 7: if (dbLoaded) printDiscounted(); break;
            case 8: if (dbLoaded) printOutOfStock(); break;
            case 9: if (dbLoaded) sortMenu(); break;
        }
    } while (cmd != 0);

    delete[] db;
    return 0;
}
