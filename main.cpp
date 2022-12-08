#include <bits/stdc++.h>
#include "Employee.h"

#define endl "\n"
using namespace std;
#define DELETE_FLAG '$'


class Department {
private:
	char *dept_id = new char[30]; /// primary key
	char *dept_name = new char[50]; ///secondary key
	char *dept_man = new char[50];
	char delim = '|';
	int idSize{};
	int nameSize{};
	int manSize{};
	int RecordSize{};
public:
	Department() = default;

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
Department *departments[6];

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

void fillDepartments(fstream &file) { ///fills Departments Array
	for (int i = 1; i <= 5; i++) {
		departments[i] = new Department(to_string(i).c_str(), deps[i - 1].c_str(), depsMangers[i - 1].c_str());
		departments[i]->writeDepartment(file);
		departments[i]->print();
		cout << endl;
	}
}

void Menu() {

	cout << "1-Add a New Employee." << endl;
	cout << "2-search for an Employee by ID." << endl;
	cout << "3-search for an Employee by Department ID." << endl;
	cout << "4-Exit." << endl;
	int choice;
	cin >> choice;
	while (choice != 4) {
		switch (choice) {
			case 1: {
				addNewEmployee();
				break;
			}
			case 2: {
				cout << "Enter Employee ID: ";
				int ID;
				cin >> ID;
				getEmployeeByID(ID);
				break;
			}
            case 3: {
                cout << "Enter Department ID: ";
                int ID;
                cin >> ID;
                getEmployeeByDep(ID);
                break;
            }
			default:
				break;
		}
		cout << "1-Add a New Employee." << endl;
		cout << "2-search for an Employee by ID." << endl;
        cout << "3-search for an Employee by Department ID." << endl;
        cout << "4-Exit." << endl;
		cin >> choice;
	}
}

int main() {
//	Menu(); ///generate 10 Employees and 5 departments
	map<int, vector<int>> mp;
	Menu();
	readSecondaryEmployee(mp);
	return 0;
}
