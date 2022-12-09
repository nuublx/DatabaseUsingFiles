#include <bits/stdc++.h>

#define endl "\n"
using namespace std;




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

	Employee(const char *emp_id, const char *dept_id, const char *emp_name, const char *emp_pos);

	void set_emp_id(const char *emp_id);

	void set_dept_id(const char *dept_id);

	void set_emp_name(const char *emp_name);

	void set_emp_pos(const char *emp_pos);

	char *get_emp_id();

	char *get_dept_id();

	char *get_emp_name();

	char *get_emp_pos();

	int get_record_size();

	void print();

	void writeEmployee(fstream &file);

	void readEmployee(fstream &file, int offset);
};

Employee *takeEmployeeInfo();

void writePrimaryEmployee(map<int, int> &pri);

void readPrimaryEmployee(map<int, int> &pri);

int getLastOffset(fstream &empFile, map<int, int> &priIndex);

void writeSecondaryEmployee(map<int, vector<int>> &secIndex);

void addNewEmployee();

int arrsize(char *arr);

void getEmployeeByID(int ID);

void getEmployeeByDep(int ID);

void readSecondaryEmployee(map<int, vector<int>> &sec);

void queryEmployee(string selected ,string attribute, string condition);

