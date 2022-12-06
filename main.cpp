#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
#define DELETE_FLAG '$'

int arrsize(char *arr) {
    int number = 0;
    while (*arr++) {
        number++;
    }
    return number;
}

class Employee {
private:
    char *emp_id = new char[13]; ///primary key
    char *dept_id = new char[30]; ///secondary key
    char *emp_name = new char[50];
    char *emp_pos = new char[50];

public:
    Employee() {}

    Employee(const char *emp_id, const char *dept_id, const char *emp_name, const char *emp_pos) {
        strcpy(this->emp_id, emp_id);
        strcpy(this->dept_id, dept_id);
        strcpy(this->emp_name, emp_name);
        strcpy(this->emp_pos, emp_pos);

    }

    void set_emp_id(const char *emp_id) {
        strcpy(this->emp_id, emp_id);
    }

    void set_dept_id(const char *dept_id) {
        strcpy(this->dept_id, dept_id);
    }

    void set_emp_name(const char *emp_name) {
        strcpy(this->emp_name, emp_name);
    }

    void set_emp_pos(const char *emp_pos) {
        strcpy(this->emp_pos, emp_pos);
    }

    char *get_emp_id() {
        return this->emp_id;
    }

    char *get_dept_id() {
        return this->dept_id;
    }

    char *get_emp_name() {
        return this->emp_name;
    }

    char *get_emp_pos() {
        return this->emp_pos;
    }

    void print() {
        cout << "Employee ID: " << this->get_emp_id() << endl;
        cout << "Department ID: " << this->get_dept_id() << endl;
        cout << "Employee name: " << this->get_emp_name() << endl;
        cout << "Employee Position: " << this->get_emp_pos() << endl;
        cout << "-------------------------------------------------\n";
    }
};

class Department {
private:
    char *dept_id = new char[30]; /// primary key
    char *dept_name = new char[50]; ///secondary key
    char *dept_man = new char[50];
    char delim = '|';
    int idSize;
    int nameSize;
    int manSize;
    int RecordSize;
public:
    Department() {}

    Department(const char *dept_id, const char *dept_name, const char *dept_man) {
        strcpy(this->dept_id, dept_id);
        strcpy(this->dept_name, dept_name);
        strcpy(this->dept_man, dept_man);
        idSize = arrsize(this->get_dept_id());
        nameSize = arrsize(this->get_dept_name());
        manSize = arrsize(this->get_dept_man());
        RecordSize = idSize + nameSize + manSize;
    }

    void set_dept_id(const char *dept_id) {
        strcpy(this->dept_id, dept_id);
    }

    void set_dept_name(const char *dept_name) {
        strcpy(this->dept_name, dept_name);
    }

    void set_dept_man(const char *dept_man) {
        strcpy(this->dept_man, dept_man);
    }

    char *get_dept_id() {
        return this->dept_id;
    }

    char *get_dept_name() {
        return this->dept_name;
    }

    char *get_dept_man() {
        return this->dept_man;
    }

    void print() {
        cout << "Department ID: " << this->get_dept_id() << endl;
        cout << "Department name: " << this->get_dept_name() << endl;
        cout << "Department Manager: " << this->get_dept_man() << endl;
        cout << "-------------------------------------------------\n";
    }

    void writeDepartment(fstream &file) {

        file << (RecordSize);

        file << delim;

        file.write(this->get_dept_id(), idSize);

        file << delim;

        file.write(this->get_dept_name(), nameSize);

        file << delim;

        file.write(this->get_dept_man(), manSize);

        file << delim;
    }

    void readDepartment(ifstream &file) {
        string x;
        char c;
        int nextDel = -1;

        if (c == DELETE_FLAG) {
            cout << "deleted record" << endl;
            return;
        }
        getline(file, x, '|');
        this->RecordSize = stoi(x);
        getline(file, x, '|');
        this->set_dept_id(x.c_str());
        getline(file, x, '|');
        this->set_dept_name(x.c_str());
        getline(file, x, '|');
        this->set_dept_man(x.c_str());
    }
};

///Some Random Names to make data look real
string names[] = {"Zeyad D.", "Youssef W.", "Yahia H.", "Yahia A.", "David M.", "Ahmed M.", "Ahmed N.", "Eyad R.",
                  "Michael E.", "A random dude"};
string deps[] = {"IS", "CS", "AI", "DS", "IT"};
string depsMangers[] = {"Ahmed", "Mohamed", "Sayed", "Mahmoud", "Mostafa"};

Employee *employees[10];
Department *departments[5];

void fillEmployees(fstream &file) { ///fills Employees Array
    string x = "Software Engineer";
    for (int i = 0; i < 10; i++) {
        employees[i] = new Employee(to_string(i + 1).c_str(), to_string((i % 5) + 1).c_str(),
                                    (names[i]).c_str(), x.c_str());
        employees[i]->print();
        cout << endl;
    }
}

void fillDepartments(fstream &file) { ///fills Departments Array
    for (int i = 1; i <= 5; i++) {
        departments[i] = new Department(to_string(i).c_str(), deps[i - 1].c_str(), depsMangers[i - 1].c_str());
        departments[i]->writeDepartment(file);
        departments[i]->print();
        cout << endl;
    }
}

void testCase() {
    fstream empFile, depFile;
    empFile.open("Employees.txt", ios::in | ios::out | ios::app);
    depFile.open("Departments.txt", ios::out | ios::app);

    fillEmployees(empFile);
    fillDepartments(depFile);
    depFile.close();
    ifstream depInFile;
    depInFile.open("Departments.txt");
    Department dep1;
    dep1.readDepartment(depInFile);
    dep1.print();
}

int main() {
    testCase(); ///generate 10 Employees and 5 departments
    return 0;
}
