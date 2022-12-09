
#include<bits/stdc++.h>
#include "Employee.h"

#define endl "\n"
using namespace std;


int arrsize(char *arr) {
	int number = 0;
	while (*arr++) {
		number++;
	}
	return number;
}

Employee::Employee(const char *emp_id, const char *dept_id, const char *emp_name, const char *emp_pos) {
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

void Employee::print() {
	cout << "Employee ID: " << this->get_emp_id() << endl;
	cout << "Department ID: " << this->get_dept_id() << endl;
	cout << "Employee name: " << this->get_emp_name() << endl;
	cout << "Employee Position: " << this->get_emp_pos() << endl;
	cout << "-------------------------------------------------\n";
}

void Employee::writeEmployee(fstream &file) {

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

void Employee::readEmployee(fstream &file, int offset) {
	string x;

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

void Employee::set_emp_id(const char *emp_id) {
	strcpy(this->emp_id, emp_id);
}

void Employee::set_dept_id(const char *dept_id) {
	strcpy(this->dept_id, dept_id);
}

void Employee::set_emp_name(const char *emp_name) {
	strcpy(this->emp_name, emp_name);
}

void Employee::set_emp_pos(const char *emp_pos) {
	strcpy(this->emp_pos, emp_pos);
}

char *Employee::get_emp_id() {
	return this->emp_id;
}

char *Employee::get_dept_id() {
	return this->dept_id;
}

char *Employee::get_emp_name() {
	return this->emp_name;
}

char *Employee::get_emp_pos() {
	return this->emp_pos;
}

int Employee::get_record_size() {
	return this->RecordSize;
}

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
	return new Employee(ID.c_str(), deptID.c_str(), name.c_str(), position.c_str());
}


void writePrimaryEmployee(map<int, int> &pri) {
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
		return offset + (int) lastEmp.get_record_size() + (int) to_string(lastEmp.get_record_size()).size();
	} else
		return 0;
}

void writeSecondaryEmployee(map<int, vector<int>> &secIndex) {
	fstream IndexKey, IndexList;
	IndexKey.open("EmployeeSecondaryIndexKey.txt", ios::out);
	IndexList.open("EmployeeSecondaryIndexList.txt", ios::out);
	int lastOffset = 0;
	for (auto it: secIndex) {
		IndexKey << it.first << '|';
		int currPos = (int) IndexList.tellp();
		bool f = false;
		if (it.second.size() == 1) {
			//lastOffset = (int) IndexList.tellp();
			IndexList << it.second[0] << '|' << -1 << '|';
			f = true;
		}
		if (!f) {
			for (int i = 0; i < it.second.size(); i++) {
				//string str = to_string(it.second[i]);

				if (i == 0) {
					IndexList << it.second[0] << '|' << -1 << '|';
					lastOffset = -1;
				} else {
					currPos = (int) IndexList.tellp();
					int prevSize = (int) to_string(it.second[i - 1]).size() + (int) to_string(lastOffset).size() + 2;
					lastOffset = currPos - prevSize;
					IndexList << it.second[i] << '|' << lastOffset << '|';
				}
			}
		}
		IndexKey << currPos << '|';
	}
	IndexKey.close();
	IndexList.close();
}

void readSecondaryEmployee(map<int, vector<int>> &sec) {
	fstream IndexKey, IndexList;
	string read1, read2;

	IndexKey.open("EmployeeSecondaryIndexKey.txt", ios::in);
	IndexList.open("EmployeeSecondaryIndexList.txt", ios::in);
	while (!IndexKey.eof()) {
		int depID;
		int offset;
		getline(IndexKey, read1, '|');
		if (read1.empty())break;
		depID = stoi(read1);
		getline(IndexKey, read1, '|');
		offset = stoi(read1);
		vector<int> empIDS;
		IndexList.seekg(offset, ios::beg);
		while (true) {
			int empID, prev;
			getline(IndexList, read2, '|');
			if (read2.empty())break;
			empID = stoi(read2);
			empIDS.emplace_back(empID);
			getline(IndexList, read2, '|');
			prev = stoi(read2);
			if (prev == -1)break;
			IndexList.seekg(prev, ios::beg);
		}
		sec.insert(make_pair(depID, empIDS));
	}
	IndexKey.close();
	IndexList.close();
}


void addNewEmployee() {
	fstream empFile;
	Employee *employee;
	empFile.open("Employees.txt", ios::in | ios::out | ios::app);
	int numberOfEmployees;
	cout << "Enter Number of employees: ";
	cin >> numberOfEmployees;
	map<int, int> priIndex;
	readPrimaryEmployee(priIndex);

	map<int, vector<int>> secIndex;
	readSecondaryEmployee(secIndex);
	int offset = getLastOffset(empFile, priIndex);

	for (int i = 0; i < numberOfEmployees; i++) {

		employee = takeEmployeeInfo();

		priIndex[stoi((string) employee->get_emp_id())] = offset;

		secIndex[stoi((string) employee->get_dept_id())].push_back(stoi((string) employee->get_emp_id()));

		employee->writeEmployee(empFile);

		employee->print();

		offset += (int) employee->get_record_size() + (int) to_string(employee->get_record_size()).size();

		cout << endl;
		// delete employee from memory
		delete employee;

	}
	writePrimaryEmployee(priIndex);
	writeSecondaryEmployee(secIndex);
	empFile.close();
}

Employee getEmployeeByID(int ID) {
	map<int, int> primaryIndex;
	fstream employeeFile;
	employeeFile.open("Employees.txt", ios::in);
	readPrimaryEmployee(primaryIndex);
	Employee employee1;
	if (primaryIndex.find(ID) != primaryIndex.end()) {
		employee1.readEmployee(employeeFile, primaryIndex[ID]);
	}
	return employee1;
}

vector<Employee> getEmployeeByDep(int ID) {
	map<int, vector<int>> secondaryIndex;
	readSecondaryEmployee(secondaryIndex);
	vector<Employee> employees;
	if (secondaryIndex.find(ID) != secondaryIndex.end()) {
		for (auto employee: secondaryIndex[ID]) {
			Employee Semployee = getEmployeeByID(employee);
			if (Semployee.get_record_size() != -1)
				employees.emplace_back(Semployee);
		}
	}
	return employees;
}

void queryEmployee(string selected, string attribute, string condition) {

	vector<Employee> selectedQuery;
	if (attribute == "employeeid") {
		int ID = stoi(condition);
		Employee Semployee = getEmployeeByID(ID);
		if (Semployee.get_record_size() != -1)
			selectedQuery.emplace_back(Semployee);
	} else {
		int deptID = stoi(condition);
		selectedQuery = getEmployeeByDep(deptID);
	}


	if (selectedQuery.empty()) {
		cout << "Nothing to show.." << endl;
		return;
	}

	if (selected == "all") {
		for (auto &i: selectedQuery) {
			i.print();
		}
	} else {
		//employee id, department id, employee name, employee position
		if (selected == "employeeid") {
			for (auto &i: selectedQuery) {
				cout << "Employee ID: " << i.get_emp_id() << "\n";
			}
		} else if (selected == "departmentid") {
			for (auto &i: selectedQuery) {
				cout << "Department ID: " << i.get_dept_id() << "\n";
			}
		} else if (selected == "employeename") {
			for (auto &i: selectedQuery) {
				cout << "Employee Name: " << i.get_emp_name() << "\n";
			}
		} else if (selected == "employeeposition") {
			for (auto &i: selectedQuery) {
				cout << "Employee Position: " << i.get_emp_pos() << "\n";
			}
		}
	}

}