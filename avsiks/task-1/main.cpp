#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

const string COLORS[] = {"красный","оранжевый","желтый","зеленый","голубой","синий","фиолетовый"};
const int COLORS_COUNT = 7;
const int COORD_MIN = -100;
const int COORD_MAX = 100;
const int R_MIN = 1;
const int R_MAX = 50;
const int RECT_MIN_SIZE = 1;
const int RECT_MAX_SIZE = 100;

string random_color() {
    return COLORS[rand() % COLORS_COUNT];
}

string gen_circle() {
    int x = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
    int y = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
    int r = R_MIN + rand() % (R_MAX - R_MIN + 1);
    return "круг " + to_string(x) + " " + to_string(y) + " " + to_string(r) + " " + random_color();
}

string gen_rectangle() {
    int x1 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
    int y1 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
    int w = RECT_MIN_SIZE + rand() % (RECT_MAX_SIZE - RECT_MIN_SIZE + 1);
    int h = RECT_MIN_SIZE + rand() % (RECT_MAX_SIZE - RECT_MIN_SIZE + 1);
    int x2 = x1 + (rand()%2 ? w : -w);
    int y2 = y1 + (rand()%2 ? h : -h);
    return "прямоугольник " + to_string(x1)+" "+to_string(y1)+" "+to_string(x2)+" "+to_string(y2)+" "+random_color();
}

double triangle_area_raw(int x1,int y1,int x2,int y2,int x3,int y3) {
    return x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
}

string gen_triangle() {
    while (true) {
        int x1 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
        int y1 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
        int x2 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
        int y2 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
        int x3 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
        int y3 = COORD_MIN + rand() % (COORD_MAX - COORD_MIN + 1);
        if (triangle_area_raw(x1,y1,x2,y2,x3,y3) != 0)
            return "треугольник "+to_string(x1)+" "+to_string(y1)+" "+
                   to_string(x2)+" "+to_string(y2)+" "+
                   to_string(x3)+" "+to_string(y3)+" "+random_color();
    }
}

string gen_line() {
    int t = rand()%3;
    if (t==0) return gen_circle();
    if (t==1) return gen_rectangle();
    return gen_triangle();
}

void write_file(const string &filename, int n) {
    ofstream f(filename);
    for(int i=0;i<n;i++) f << gen_line() << "\n";
    cout << "Создан " << filename << " (" << n << " строк)\n";
}

class Figure {
public:
    string color;
    Figure(string c): color(c) {}
    virtual double perimeter() = 0;
    virtual double area() = 0;
    virtual string info() = 0;
    virtual ~Figure() {}
};

class Circle: public Figure {
public:
    int x,y,r;
    Circle(int X,int Y,int R,string c): Figure(c), x(X),y(Y),r(R) {}
    double perimeter() { return 2 * 3.1415926535 * r; }
    double area() { return 3.1415926535 * r * r; }
    string info() { return "круг: центр=(" + to_string(x) + "," + to_string(y) + "), r=" + to_string(r) + ", цвет=" + color; }
};

class RectangleF: public Figure {
public:
    int x1,y1,x2,y2;
    RectangleF(int X1,int Y1,int X2,int Y2,string c):
        Figure(c), x1(X1),y1(Y1),x2(X2),y2(Y2) {}

    double perimeter() { return 2 * (abs(x2-x1) + abs(y2-y1)); }
    double area() { return abs(x2-x1) * abs(y2-y1); }
    string info() { return "прямоугольник: (" + to_string(x1)+","+to_string(y1)+")–("+to_string(x2)+","+to_string(y2)+"), цвет=" + color; }
};

class TriangleF: public Figure {
public:
    int x1,y1,x2,y2,x3,y3;
    TriangleF(int X1,int Y1,int X2,int Y2,int X3,int Y3,string c):
        Figure(c), x1(X1),y1(Y1),x2(X2),y2(Y2),x3(X3),y3(Y3) {}

    double dist(int X1,int Y1,int X2,int Y2) {
        return sqrt((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1));
    }

    double perimeter() {
        return dist(x1,y1,x2,y2) + dist(x2,y2,x3,y3) + dist(x1,y1,x3,y3);
    }

    double area() {
        double a = dist(x1,y1,x2,y2);
        double b = dist(x2,y2,x3,y3);
        double c = dist(x1,y1,x3,y3);
        double p = (a + b + c) / 2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }

    string info() { 
        return "треугольник: ("+to_string(x1)+","+to_string(y1)+"),("+to_string(x2)+","+to_string(y2)+"),("+to_string(x3)+","+to_string(y3)+"), цвет=" + color;
    }
};

Figure* parse_figure(const string &line) {
    vector<string> parts;
    string t;
    for(char c : line) {
        if (c == ' ') {
            if (!t.empty()) parts.push_back(t);
            t = "";
        } else t += c;
    }
    if (!t.empty()) parts.push_back(t);

    string type = parts[0];
    string color = parts.back();

    if (type == "круг")
        return new Circle(stoi(parts[1]), stoi(parts[2]), stoi(parts[3]), color);
    if (type == "прямоугольник")
        return new RectangleF(stoi(parts[1]), stoi(parts[2]),
                              stoi(parts[3]), stoi(parts[4]), color);
    if (type == "треугольник")
        return new TriangleF(stoi(parts[1]), stoi(parts[2]),
                             stoi(parts[3]), stoi(parts[4]),
                             stoi(parts[5]), stoi(parts[6]), color);

    return nullptr;
}

double get_perimeter(Figure* f) { return f->perimeter(); }

void shell_sort_figures(vector<Figure*>& arr) {
    int n = arr.size();
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            Figure* temp = arr[i];
            int j = i;
            while (j >= gap && get_perimeter(arr[j-gap]) > get_perimeter(temp)) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}

void count_file(const string &filename, int &lines, int &chars) {
    ifstream f(filename);
    lines = 0;
    chars = 0;
    string s;
    while (getline(f, s)) {
        lines++;
        chars += s.size() + 1;
    }
}

void process_file(const string &input_file, const string &output_file) {
    auto start = high_resolution_clock::now();

    ifstream fin(input_file);
    vector<string> lines;
    string line;
    while (getline(fin, line))
        lines.push_back(line);

    vector<Figure*> figs;
    for (auto &s : lines)
        figs.push_back(parse_figure(s));

    shell_sort_figures(figs);

    auto end = high_resolution_clock::now();
    double duration_ms = duration<double, milli>(end - start).count();

    int main_lines, main_chars;
    count_file("main.cpp", main_lines, main_chars);

    ofstream out(output_file);
    out << "Исходные строки:\n";
    for (auto &s : lines) out << s << "\n";

    out << "\nВсего фигур: " << figs.size() << "\n";
    out << "Время обработки файла: " << duration_ms << " мс\n";
    out << "Файл main.cpp: строк=" << main_lines << ", символов=" << main_chars << "\n";

    out << "\nОтсортированные фигуры:\n";
    for (auto f : figs)
        out << f->info() << ", периметр=" << f->perimeter() << "\n";

    for (auto f : figs) delete f;
}

int main() {
    srand(time(0));

    int sizes[] = {10, 100, 250, 500};
    for (int i = 0; i < 4; i++)
        write_file("input_" + to_string(sizes[i]) + ".txt", sizes[i]);

    string files[] = {"input_10.txt", "input_100.txt", "input_250.txt", "input_500.txt"};

    for (int i = 0; i < 4; i++) {
        string outfile = "output_" + files[i].substr(6);
        process_file(files[i], outfile);
        cout << "Создан " << outfile << "\n";
    }

    return 0;
}