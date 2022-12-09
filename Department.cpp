#include <bits/stdc++.h>
#include "Department.h"

#define endl "\n"
#define DELETE_FLAG '$'

using namespace std;

int arrsizeD(char *arr) {
	int number = 0;
	while (*arr++) {
		number++;
	}
	return number;
}

Department::Department(const char *dept_id, const char *dept_name, const char *dept_man) {
	strcpy(this->dept_id, dept_id);
	strcpy(this->dept_name, dept_name);
	strcpy(this->dept_man, dept_man);
	idSize = arrsizeD(this->get_dept_id());
	nameSize = arrsizeD(this->get_dept_name());
	manSize = arrsizeD(this->get_dept_man());
	RecordSize = idSize + nameSize + manSize + 4;
}

void Department::set_dept_id(const char *dept_id) {
	strcpy(this->dept_id, dept_id);
}

void Department::set_dept_name(const char *dept_name) {
	strcpy(this->dept_name, dept_name);
}

void Department::set_dept_man(const char *dept_man) {
	strcpy(this->dept_man, dept_man);
}

char *Department::get_dept_id() {
	return this->dept_id;
}

char *Department::get_dept_name() {
	return this->dept_name;
}

char *Department::get_dept_man() {
	return this->dept_man;
}

int Department::get_record_size() {
	return this->RecordSize;
}

void Department::print() {
	cout << "Department ID: " << this->get_dept_id() << endl;
	cout << "Department name: " << this->get_dept_name() << endl;
	cout << "Department Manager: " << this->get_dept_man() << endl;
	cout << "-------------------------------------------------\n";
}

void Department::writeDepartment(fstream &file) {

	file << (RecordSize);

	file << delim;

	file.write(this->get_dept_id(), idSize);

	file << delim;

	file.write(this->get_dept_name(), nameSize);

	file << delim;

	file.write(this->get_dept_man(), manSize);

	file << delim;
}

void Department::readDepartment(fstream &file, int offset) {
	string x;
	file.seekg(offset, ios::beg);

	getline(file, x, '|');
	this->RecordSize = stoi(x);
	getline(file, x, '|');
	this->set_dept_id(x.c_str());
	getline(file, x, '|');
	this->set_dept_name(x.c_str());
	getline(file, x, '|');
	this->set_dept_man(x.c_str());
}

Department *takeDepartmentInfo() {
	cout << "Enter Department ID: ";
	string ID;
	cin >> ID;
	cout << "Enter Department Name: ";
	string depName;
	cin >> depName;
	cout << "Enter Department Manager: ";
	string manager;
	cin.ignore();
	getline(cin, manager, '\n');

	return new Department(ID.c_str(), depName.c_str(), manager.c_str());
}

Department *department;

void addNewDepartment() {
	fstream deptFile;
	deptFile.open("Departments.txt", ios::in | ios::out | ios::app);
	int numberOfDepts;
	cout << "Enter Number of Departments: ";
	cin >> numberOfDepts;
	map<int, int> priIndex;
	readPrimaryDepartment(priIndex);

	map<string, vector<int>> secIndex;
	readSecondaryDepartment(secIndex);
	int offset = getLastOffsetDept(deptFile, priIndex);

	for (int i = 0; i < numberOfDepts; i++) {

		department = takeDepartmentInfo();

		priIndex[stoi((string) department->get_dept_id())] = offset;

		secIndex[(string) department->get_dept_name()].push_back(stoi((string) department->get_dept_id()));

		department->writeDepartment(deptFile);

		department->print();

		offset += department->get_record_size() + to_string(department->get_record_size()).size();

		cout << endl;
		// delete employee from memory
		delete department;

	}
	writePrimaryDepartment(priIndex);
	writeSecondaryDepartment(secIndex);
	deptFile.close();
}

void writePrimaryDepartment(map<int, int> &pri) {
	fstream Index;
	Index.open("DeptPrimaryIndex.txt", ios::out);
	for (auto it: pri) {
		Index << it.first << '|' << it.second << '|';
	}
	Index.close();
}

void readPrimaryDepartment(map<int, int> &pri) {
	fstream Index;
	string read1, read2;

	Index.open("DeptPrimaryIndex.txt", ios::in);
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

int getLastOffsetDept(fstream &deptFile, map<int, int> &priIndex) {
	if (!priIndex.empty()) {
		Department lastDept;
		int offset = std::max_element(priIndex.begin(), priIndex.end(),
		                              [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
			                              return a.second < b.second;
		                              })->second;
		lastDept.readDepartment(deptFile, offset);
		return offset + (int) lastDept.get_record_size() + (int) to_string(lastDept.get_record_size()).size();
	} else
		return 0;
}

void writeSecondaryDepartment(map<string, vector<int>> &secIndex) {
	fstream IndexKey, IndexList;
	IndexKey.open("DeptSecondaryIndexKey.txt", ios::out);
	IndexList.open("DeptSecondaryIndexList.txt", ios::out);
	int lastOffset = 0;
	for (auto it: secIndex) {
		IndexKey << it.first << '|';
        sort(it.second.begin(), it.second.end());
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

void readSecondaryDepartment(map<string, vector<int>> &sec) {
	fstream IndexKey, IndexList;
	string read1, read2;

	IndexKey.open("DeptSecondaryIndexKey.txt", ios::in);
	IndexList.open("DeptSecondaryIndexList.txt", ios::in);
	while (!IndexKey.eof()) {
		string deptName;
		int offset;
		getline(IndexKey, read1, '|');
		if (read1.empty())break;
		deptName = read1;
		getline(IndexKey, read1, '|');
		offset = stoi(read1);
		vector<int> deptIDS;
		IndexList.seekg(offset, ios::beg);
		while (true) {
			int deptID, prev;
			getline(IndexList, read2, '|');
			if (read2.empty())break;
			deptID = stoi(read2);
			deptIDS.emplace_back(deptID);
			getline(IndexList, read2, '|');
			prev = stoi(read2);
			if (prev == -1)break;
			IndexList.seekg(prev, ios::beg);
		}
		sec.insert(make_pair(deptName, deptIDS));
	}

	IndexKey.close();
	IndexList.close();
}

Department getDepartmentByID(int ID) {
	map<int, int> primaryIndex;
	fstream deptFile;
	deptFile.open("Departments.txt", ios::in);
	readPrimaryDepartment(primaryIndex);
	Department dep1;
	if (primaryIndex.find(ID) != primaryIndex.end()) {
		dep1.readDepartment(deptFile, primaryIndex[ID]);
	}
	return dep1;
}

vector<Department> getDepartmentByName(string deptName) {
	map<string, vector<int>> secondaryIndex;
	readSecondaryDepartment(secondaryIndex);
	vector<Department> Departments;
	if (secondaryIndex.find(deptName) != secondaryIndex.end()) {
		for (auto dep: secondaryIndex[deptName]) {
			Department Sdepartment = getDepartmentByID(dep);
			if (Sdepartment.get_record_size() != -1)
				Departments.emplace_back(Sdepartment);
		}
	}
	return Departments;

}

void queryDepartment(string selected, string attribute, string condition) {

	vector<Department> selectedQuery;

	if (attribute == "deptid") {
		int ID = stoi(condition);
		Department Sdepartment = getDepartmentByID(ID);
		if (Sdepartment.get_record_size() != -1)
			selectedQuery.emplace_back(Sdepartment);
	} else {
		selectedQuery = getDepartmentByName(condition);
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
		//departmentID departmentManger departmentName
		if (selected == "departmentid") {
			for (auto &i: selectedQuery) {
				cout << "Department ID: " << i.get_dept_id() << endl;
			}
		} else if (selected == "departmentmanager") {
			for (auto &i: selectedQuery) {
				cout << "Department Manager: " << i.get_dept_man() << endl;
			}
		} else if (selected == "departmentname") {
			for (auto &i: selectedQuery) {
				cout << "Department Name: " << i.get_dept_name() << endl;
			}
		}
	}
}

