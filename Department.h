#include <bits/stdc++.h>

#define endl "\n"
using namespace std;


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
	Department() {
		RecordSize = -1;
	}

	Department(const char *dept_id, const char *dept_name, const char *dept_man);

	void set_dept_id(const char *dept_id);

	void set_dept_name(const char *dept_name);

	void set_dept_man(const char *dept_man);

	char *get_dept_id();

	char *get_dept_name();

	char *get_dept_man();

	int get_record_size();

	void print();

	void writeDepartment(fstream &file);

	void readDepartment(fstream &file, int offset);
};

Department *takeDepartmentInfo();

void addNewDepartment();

void writePrimaryDepartment(map<int, int> &pri);

void readPrimaryDepartment(map<int, int> &pri);

int getLastOffsetDept(fstream &deptFile, map<int, int> &priIndex);

void writeSecondaryDepartment(map<string, vector<int>> &secIndex);

void readSecondaryDepartment(map<string, vector<int>> &sec);

Department getDepartmentByID(int ID);

vector<Department> getDepartmentByName(string deptName);

void queryDepartment(string selected, string attribute, string condition);
