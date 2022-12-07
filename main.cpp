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
    char delim = '|';
    int empidSize;
    int depidSize;
    int nameSize;
    int posSize;
    int RecordSize;

public:
    Employee() {}

    Employee(const char *emp_id, const char *dept_id, const char *emp_name, const char *emp_pos) {
        strcpy(this->emp_id, emp_id);
        strcpy(this->dept_id, dept_id);
        strcpy(this->emp_name, emp_name);
        strcpy(this->emp_pos, emp_pos);
        empidSize = arrsize(this->get_emp_id());
        depidSize = arrsize(this->get_dept_id());
        nameSize = arrsize(this->get_emp_name());
        posSize = arrsize(this->get_emp_pos());
        RecordSize = empidSize + depidSize + nameSize + posSize + 5;

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

    int get_record_size() {
        return this->RecordSize;
    }

    void print() {
        cout << "Employee ID: " << this->get_emp_id() << endl;
        cout << "Department ID: " << this->get_dept_id() << endl;
        cout << "Employee name: " << this->get_emp_name() << endl;
        cout << "Employee Position: " << this->get_emp_pos() << endl;
        cout << "-------------------------------------------------\n";
    }

    void writeEmployee(fstream &file) {

        file << (RecordSize);

        file << delim;

        file.write(this->get_emp_id(), empidSize);

        file << delim;

        file.write(this->get_dept_id(), depidSize);

        file << delim;

        file.write(this->get_emp_name(), nameSize);

        file << delim;

        file.write(this->get_emp_pos(), posSize);

        file << delim;
    }

    void readEmployee(fstream &file, int offset) {
        string x;
        char c;
        int nextDel = -1;

        if (c == DELETE_FLAG) {
            cout << "deleted record" << endl;
            return;
        }
        file.seekg(offset, ios::beg);
        getline(file, x, '|');
        this->RecordSize = stoi(x);
        getline(file, x, '|');
        this->set_emp_id(x.c_str());
        getline(file, x, '|');
        this->set_dept_id(x.c_str());
        getline(file, x, '|');
        this->set_emp_name(x.c_str());
        getline(file, x, '|');
        this->set_emp_pos(x.c_str());
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

        file << (RecordSize + 4);

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

/*
void fillEmployees(fstream &file) { ///fills Employees Array
    string x = "Software Engineer";
    int numberOfEmployees;
    cout << "Enter Number of employees: ";
    cin >> numberOfEmployees;
    for (int i = 0; i < numberOfEmployees; i++) {
        employees[i] = new Employee(to_string(i + 1).c_str(), to_string((i % 5) + 1).c_str(),
                                    (names[i % 10]).c_str(), x.c_str());
        employees[i]->writeEmployee(file);
        employees[i]->print();
        cout << endl;
    }
}
 */

Employee *takeEmployeeInfo() {
    cout << "Enter Employee ID: ";
    string ID;
    cin >> ID;
    cout << "Enter Department ID: ";
    string deptID;
    cin >> deptID;
    cout << "Enter Employee Name: ";
    string name;
    cin.ignore();
    getline(cin, name, '\n');

    cout << "Enter Employee Position: ";
    string position;
    getline(cin, position, '\n');
    return new Employee(ID.c_str(), deptID.c_str(),
                        name.c_str(), position.c_str());
}

Employee *employee;
Department *departments[5];

void writePrimaryEmployee(map<int, int> pri) {
    fstream Index;
    Index.open("EmployeePrimaryIndex.txt", ios::out);
    for (auto it: pri) {
        Index << it.first << '|' << it.second << '|';
    }
    Index.close();
}

void readPrimaryEmployee(map<int, int> &pri) {
    fstream Index;
    string read1, read2;

    Index.open("EmployeePrimaryIndex.txt", ios::in);
    while (!Index.eof()) {
        int ID;
        int offset;
        getline(Index, read1, '|');
        if (read1.empty())
            break;
        ID = stoi(read1);
        getline(Index, read2, '|');
        offset = stoi(read2);
        pri.insert(make_pair(ID, offset));
    }
    Index.close();
}

int getLastOffset(fstream &empFile, map<int, int> &priIndex) {
    if (!priIndex.empty()) {
        Employee lastEmp;
        int offset = std::max_element(priIndex.begin(), priIndex.end(),
                                      [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
                                          return a.second < b.second;
                                      })->second;
        lastEmp.readEmployee(empFile, offset);
        return offset + lastEmp.get_record_size() + to_string(lastEmp.get_record_size()).size();
    } else
        return 0;
}

void writeSecondaryEmployee(map<int, vector<int>> secIndex) {
    fstream IndexKey, IndexList;
    IndexKey.open("EmployeeSecondaryIndexKey.txt", ios::out);
    IndexList.open("EmployeeSecondaryIndexList.txt", ios::out);
    int offset = 0, inBetween = 0;
    for (auto it: secIndex) {
        IndexKey << it.first << '|';
        int firstSize = 0, lastSize = 0;
        for (int i = 0; i < it.second.size(); i++) {
            string str = to_string(it.second[i]);

            if (i == 0) {
                IndexList << it.second[i] << '|' << i - 1 << '|';
                firstSize = to_string(it.second[i]).size() + 4;
            } else if (i + 1 == it.second.size()) {
                IndexList << it.second[i] << '|' << offset << '|';
                lastSize = to_string(it.second[i]).size() + to_string(i).size() + 2;
            } else {
                IndexList << it.second[i] << '|' << offset << '|';
                offset += to_string(it.second[i]).size() + to_string(i).size() + 2;
            }
        }
        offset += firstSize;
        IndexKey << offset << '|';
        offset += lastSize;
    }
    IndexKey.close();
    IndexList.close();
}

/*
void readSecondaryEmployee(  map<int, vector<int>> secIndex) {
    fstream Index;
    string read1, read2;

    Index.open("EmployeePrimaryIndex.txt", ios::in);
    while (!Index.eof()) {
        int ID;
        int offset;
        getline(Index, read1, '|');
        if (read1.empty())
            break;
        ID = stoi(read1);
        getline(Index, read2, '|');
        offset = stoi(read2);
        pri.insert(make_pair(ID, offset));
    }
    Index.close();
}
 */
void addNewEmployee() {
    fstream empFile;
    empFile.open("Employees.txt", ios::in | ios::out | ios::app);
    int numberOfEmployees;
    cout << "Enter Number of employees: ";
    cin >> numberOfEmployees;
    map<int, int> priIndex;
    readPrimaryEmployee(priIndex);

    map<int, vector<int>> secIndex;

    int offset = getLastOffset(empFile, priIndex);

    for (int i = 0; i < numberOfEmployees; i++) {

        employee = takeEmployeeInfo();

        priIndex[stoi((string) employee->get_emp_id())] = offset;

        secIndex[stoi((string) employee->get_dept_id())].push_back(stoi((string) employee->get_emp_id()));

        employee->writeEmployee(empFile);

        employee->print();

        offset += employee->get_record_size() + to_string(employee->get_record_size()).size();

        cout << endl;
        // delete employee from memory
        delete employee;

    }
    writePrimaryEmployee(priIndex);
    writeSecondaryEmployee(secIndex);
    empFile.close();
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
    fstream depFile;

    // depFile.open("Departments.txt", ios::out | ios::app);
    addNewEmployee();
/*
    //fillEmployees(empFile);
    fillDepartments(depFile);
    depFile.close();
    ifstream depInFile;
    depInFile.open("Departments.txt");
    Department dep1;
    dep1.readDepartment(depInFile);
    dep1.print();
    */
}

int main() {
    testCase(); ///generate 10 Employees and 5 departments
    return 0;
}
