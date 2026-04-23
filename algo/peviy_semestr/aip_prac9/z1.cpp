#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Employee {
    string name;
    int age;
    string position;
    double salary;
};

struct Departament {
    string departmentName;
    vector <Employee> employees;
    void add_emp(Employee emp){
        employees.push_back(emp);
    };
    int index_emp(string emp_name){
        for (int i=0; i<employees.size(); i++){
            if (employees[i].name == emp_name) {
                return i;
            };
        }
        return -1;
    };
    
    bool del_emp(string emp_name){
        int ind = index_emp(emp_name);
        if (ind != -1) {
            employees.erase(employees.begin() + ind);
            return true;
        };
        return false;
    };

    bool info_emp(string emp_name){
        int ind = index_emp(emp_name);
        if (ind != -1){
            cout << "Информация о сотруднике:\n\n";
            cout << "Имя: " << employees[ind].name << endl;
            cout << "Возраст: " << employees[ind].age << endl;
            cout << "Отдел: " << employees[ind].position << endl;
            cout << "Зарплата: " << employees[ind].salary << endl;
            return true;
        };
        cout << "Сотрудник не найден" << endl;
        return false;
    };

    float general_salary(){
        float quantity = 0;
        for (int i=0; i < employees.size(); i++){
            quantity += employees[i].salary;
        };
        return quantity;
    };

};

int main(){

    Employee Petrov;
    Petrov.name = "Alex";
    Petrov.age = 21;
    Petrov.position = "junior_hr";
    Petrov.salary = 1337.52;

    Employee Sidorov;
    Sidorov.name = "Nikita";
    Sidorov.age = 22;
    Sidorov.position = "middle_hr";
    Sidorov.salary = 1488.42;

    Employee Smirnov;
    Smirnov.name = "Gleb";
    Smirnov.age = 44;
    Smirnov.position = "senior_hr";
    Smirnov.salary = 10000.52;

    Employee Syedina;
    Syedina.name = "Kira";
    Syedina.age = 18;
    Syedina.position = "junior_ds";
    Syedina.salary = 1000.07;

    Employee Polukhina;
    Polukhina.name = "Julia";
    Polukhina.age = 20;
    Polukhina.position = "middle_ds";
    Polukhina.salary = 1984.01;

    Employee Melnikova = {"Viktoria", 66, "senior_ds", 99999.99};
    Employee Sergeev = {"Nikita", 24, "programmer", 1999.99};
    Employee Navalny = {"Alexey", 49, "lawyer", 2018.00};
    Employee Batura = {"Yaroslav", 18, "admin", 2029.12};

    Departament hr;
    Departament ds;

    hr.departmentName = "human_resources";
    hr.add_emp(Petrov);
    hr.add_emp(Sidorov);
    hr.add_emp(Smirnov);
    ds.departmentName = "data_scientists";
    ds.add_emp(Syedina);
    ds.add_emp(Polukhina);
    ds.add_emp(Melnikova);

    cout << "Отдел: " << hr.departmentName << endl;
    cout << "Сотрудники: " << endl;
    for (int i=0; i < hr.employees.size(); i++){
        cout << hr.employees[i].name << endl;
    };
    cout << "Общая зарплата: " << hr.general_salary() << endl;

    cout << "Отдел: " << ds.departmentName << endl;
    cout << "Сотрудники: " << endl;
    for (int i=0; i < ds.employees.size(); i++){
        cout << ds.employees[i].name << endl;
    };
    cout << "Общая зарплата: " << ds.general_salary() << endl;

    hr.del_emp("Nikita");
    ds.add_emp(Sidorov);
    hr.add_emp(Navalny);

        cout << "Отдел: " << hr.departmentName << endl;
    cout << "Сотрудники: " << endl;
    for (int i=0; i < hr.employees.size(); i++){
        cout << hr.employees[i].name << endl;
    };
    cout << "Общая зарплата: " << hr.general_salary() << endl;

    cout << "Отдел: " << ds.departmentName << endl;
    cout << "Сотрудники: " << endl;
    for (int i=0; i < ds.employees.size(); i++){
        cout << ds.employees[i].name << endl;
    };
    cout << "Общая зарплата: " << ds.general_salary() << endl;

    hr.info_emp("Alexey");
    ds.info_emp("Anatoly");
};