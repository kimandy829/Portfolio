// Name: Andy Kim
// Email: akim83@myseneca.ca
// Student ID: 105945208
// Date: 2020-12-03

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

struct Employee
{
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportsTo[100];
	char jobTitle[50];
	char city[50];
};
struct Employee emp = { 0 };

int menu(void) {
	cout << "********************* HR Menu *********************" << endl;
	cout << "1) Find Employee" << endl;
	cout << "2) Employees Report" << endl;
	cout << "3) Add Employee" << endl;
	cout << "4) Update Employee" << endl;
	cout << "5) Remove Employee" << endl;
	cout << "6) Exit" << endl;
	cout << "Select Option: ";
	int select;
	bool invalid;
	do {
		invalid = false;
		cin >> select;
		if (cin.fail()) {
			cout << "Bad integer value, try again: ";
			cin.clear();
			cin.ignore(3000, '\n');
			invalid = true;
		}
		else if (select < 1 || select > 6) {
			cout << "Invalid value entered, retry[0 <= value <= 6]";
			cin.ignore(3000, '\n');
			invalid = true;
		}
	} while (invalid);
	return select;
}

int findEmployee(Connection *conn, int employeeNumber, struct Employee* emp) {
	int result;
	try
	{
		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT e.employeenumber, e.lastname, e.firstname, e.email, o.phone, e.extension, m.firstname || ' ' ||  m.lastname AS reportsto, e.jobtitle, o.city FROM employees e INNER JOIN employees m on e.reportsto = m.employeenumber(+) INNER JOIN offices o ON e.officecode = o.officecode WHERE e.employeenumber =" + to_string(employeeNumber));
		if (rs->next()) {
			emp->employeeNumber = rs->getInt(1);
			strcpy(emp->lastName, rs->getString(2).c_str());
			strcpy(emp->firstName, rs->getString(3).c_str());
			strcpy(emp->email, rs->getString(4).c_str());
			strcpy(emp->phone, rs->getString(5).c_str());
			strcpy(emp->extension, rs->getString(6).c_str());
			strcpy(emp->reportsTo, rs->getString(7).c_str());
			strcpy(emp->jobTitle, rs->getString(8).c_str());
			strcpy(emp->city, rs->getString(9).c_str());
			result = 1;
		}
		else {
			result = 0;
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return result;
}

void displayEmployee(Connection* conn, struct Employee emp) {
	cout << "employeeNumber = " << emp.employeeNumber << endl;
	cout << "lastName = " << emp.lastName << endl;
	cout << "firstName = " << emp.firstName << endl;
	cout << "email = " << emp.email << endl;
	cout << "phone = " << emp.phone << endl;
	cout << "extension = " << emp.extension << endl;
	cout << "reportsTo = " << emp.reportsTo << endl;
	cout << "jobTitle = " << emp.jobTitle << endl;
	cout << "city = " << emp.city << endl;

}

void displayAllEmployees(Connection* conn) {
	try {
		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT e.employeenumber, e.firstname || ' ' || e.lastname AS fullname, e.email, o.phone, e.extension, m.firstname || ' ' ||  m.lastname AS reportsto                                                                 FROM employees e INNER JOIN employees m ON e.reportsto = m.employeenumber(+) INNER JOIN offices o ON e.officecode = o.officecode");
		
		cout << "E         Employee Name         Email                              Phone\t\tExt\tManager" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		if (!rs->next()) {
			cout << "There is no employees' information to be displayed" << endl;
		}
		else {
			while (rs->next()) {
				int id = rs->getInt(1);
				string name = rs->getString(2);
				string email = rs->getString(3);
				string phone = rs->getString(4);
				string extension = rs->getString(5);
				string manager = rs->getString(6);
				cout << id << "\t  ";
				cout.width(20);
				cout.setf(ios::left);
				cout << name << "\t";
				cout.width(35);
				cout.setf(ios::left);
				cout << email << phone << "\t" << extension << "\t" << manager << endl;
			}
		}
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void insertEmployee(Connection* conn, struct Employee emp) {
	try {
		Statement* stmt = conn->createStatement();
		stmt->executeUpdate("INSERT INTO employees VALUES (" + to_string(emp.employeeNumber) + ", '" + emp.lastName + "', '" + emp.firstName + "', '" + emp.extension + "', '" + emp.email + "', 1, 1002, '" + emp.jobTitle + "')");
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void updateEmployee(Connection* conn, int employeeNumber) {
	try {
		char newExtension[10] = {0};
		cout << "New Extension: ";
		cin >> newExtension;
		cin.clear();
		cin.ignore(3000, '\n');
		Statement* stmt = conn->createStatement();
		stmt->executeUpdate("UPDATE employees SET extension = '" + string(newExtension) + "' WHERE employeenumber = " + to_string(employeeNumber));
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

void deleteEmployee(Connection* conn, int employeeNumber) {
	try {
		Statement* stmt = conn->createStatement();
		stmt->executeUpdate("DELETE FROM employees WHERE employeenumber = " +  to_string(employeeNumber));
		conn->terminateStatement(stmt);
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
}

int main() {
	Environment* env = nullptr;
	Connection* conn = nullptr;

	string user = "dbs211_203b15";
	string pass = "83042233";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, srv);
		bool valid = true;
		while (valid) {
			int empNum = -1;
			int find = -1;
			switch (menu())
			{
			case 1:
				cout << "Enter employee number: ";
				cin >> empNum;
				cin.clear();
				cin.ignore(3000, '\n');
				find = findEmployee(conn, empNum, &emp);
				if (find == 0) {
					cout << "Employee " << empNum << " does not exist." << endl;
				}
				else {
					displayEmployee(conn, emp);
				}
				break;
			case 2:
				displayAllEmployees(conn);
				break;
			case 3:
				cout << "Enter employee number: ";
				cin >> empNum;
				cin.clear();
				cin.ignore(3000, '\n');
				find = findEmployee(conn, empNum, &emp);
				if (find == 1) {
					cout << "An employee with the same employee number exists." << endl;
				}
				else {
					int id;
					char last[50];
					char first[50];
					char email[100];
					char extension[10];
					char jobtitle[50];
					cout << "Employee Number: ";
					cin >> id;
					cin.clear();
					cin.ignore(3000, '\n');
					cout << "Last Name: ";
					cin >> last;
					cin.clear();
					cin.ignore(3000, '\n');
					cout << "First Name: ";
					cin >> first;
					cin.clear();
					cin.ignore(3000, '\n');
					cout << "Email: ";
					cin >> email;
					cin.clear();
					cin.ignore(3000, '\n');
					cout << "extension: ";
					cin >> extension;
					cin.clear();
					cin.ignore(3000, '\n');
					cout << "Job Title: ";
					cin >> jobtitle;
					cin.clear();
					cin.ignore(3000, '\n');
					emp.employeeNumber = id;
					strcpy(emp.lastName, last);
					strcpy(emp.firstName, first);
					strcpy(emp.email, email);
					strcpy(emp.extension, extension);
					strcpy(emp.jobTitle, jobtitle);
					insertEmployee(conn, emp);
					cout << "The new employee is added successfully." << endl;
				}
				break;
			case 4:
				cout << "Enter employee number: ";
				cin >> empNum;
				cin.clear();
				cin.ignore(3000, '\n');
				find = findEmployee(conn, empNum, &emp);
				if (find == 0) {
					cout << "Employee " << empNum << " does not exist." << endl;
				}
				else {
					updateEmployee(conn, empNum);
					cout << "Updated extension for employee " << empNum << endl;
				}
				break;
			case 5:
				cout << "Enter employee number: ";
				cin >> empNum;
				cin.clear();
				cin.ignore(3000, '\n');
				find = findEmployee(conn, empNum, &emp);
				if (find == 0) {
					cout << "The employee does not exist." << endl;
				}
				else {
					deleteEmployee(conn, empNum);
					cout << "The employee is deleted." << endl;
				}
				break;
			default:
				valid = false;
				break;
			}
		}
	}
	catch (SQLException& sqlExcp) {
		cout << "error";
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}

	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);

	return 0;
}