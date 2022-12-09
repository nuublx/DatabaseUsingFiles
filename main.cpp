#include <bits/stdc++.h>
#include "Employee.h"
#include "Department.h"

#define endl "\n"
using namespace std;

string lowercase(const string &query) {
	string temp;
	for (char x: query) {
		if (isalpha(x))
			temp += (char) tolower(x);
		else if (isdigit(x))
			temp += x;
	}
	return temp;
}

void query() {
	cout << "Enter Query: ";
	string query[8];
	for (auto &i: query) {
		cin >> i;
	}
	//cout<<lowercase(query[5])<<endl;
	if (lowercase(query[3]) == "employee") {
		queryEmployee(lowercase(query[1]), lowercase(query[5]), lowercase(query[7]));
	} else if (lowercase(query[3]) == "department") {
		queryDepartment(lowercase(query[1]), lowercase(query[5]), lowercase(query[7]));
	}
}

void Menu() {

	cout << "1-Add a New Employee." << endl;
	cout << "2-search for an Employee by ID." << endl;
	cout << "3-search for an Employee by Department ID." << endl;
	cout << "4-Add a New Department." << endl;
	cout << "5-search for a Department by ID." << endl;
	cout << "6-search for a Department by Name." << endl;
	cout << "7-Query." << endl;
	cout << "8-Exit." << endl;
	int choice;
	cin >> choice;
	while (choice != 8) {
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
			case 7: {
				query();
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
		cout << "7-Query." << endl;
		cout << "8-Exit." << endl;
		cin >> choice;
	}
}

int main() {
//	Menu(); ///generate 10 Employees and 5 departments
	map<string, vector<int>> mp;
	Menu();
	//readSecondaryEmployee(mp);
	readSecondaryDepartment(mp);
	return 0;
}
