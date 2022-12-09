#include <bits/stdc++.h>
#include "Employee.h"
#include "Department.h"

#define endl "\n"
using namespace std;

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

Department *departments[6];


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


void fillDepartments(fstream &file) { ///fills Departments Array
	for (int i = 1; i <= 5; i++) {
		departments[i] = new Department(to_string(i).c_str(), deps[i - 1].c_str(), depsMangers[i - 1].c_str());
		departments[i]->writeDepartment(file);
		departments[i]->print();
		cout << endl;
	}
}
 */

void Menu() {

	cout << "1-Add a New Employee." << endl;
	cout << "2-search for an Employee by ID." << endl;
	cout << "3-search for an Employee by Department ID." << endl;
	cout << "4-Add a New Department." << endl;
	cout << "5-search for a Department by ID." << endl;
	cout << "6-search for a Department by Name." << endl;
	cout << "7-Exit." << endl;
	int choice;
	cin >> choice;
	while (choice != 7) {
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
            case 4: {
                addNewDepartment();
                break;
            }
            case 5: {
                cout << "Enter Department ID: ";
                int ID;
                cin >> ID;
                getDepartmentByID(ID);
                break;
            }
            case 6: {
                cout << "Enter Department Name: ";
                string deptName;
                cin >> deptName;
                getDepartmentByName(deptName);
                break;
            }
			default:
				break;
		}
		cout << "1-Add a New Employee." << endl;
		cout << "2-search for an Employee by ID." << endl;
        cout << "3-search for an Employee by Department ID." << endl;
        cout << "4-Add a New Department." << endl;
        cout << "5-search for a Department by ID." << endl;
        cout << "6-search for a Department by Name." << endl;
        cout << "7-Exit." << endl;
		cin >> choice;
	}
}

int main() {
//	Menu(); ///generate 10 Employees and 5 departments
	map<string , vector<int>> mp;
	Menu();
	//readSecondaryEmployee(mp);
    readSecondaryDepartment(mp);
	return 0;
}
