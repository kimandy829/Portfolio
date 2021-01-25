/* Citation and Sources...
Final Project Milestone 3
Module: Menu
Filename: Menu.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/17  Preliminary release
2020/11/17  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"
using namespace std;
namespace sdds
{
	Patient::Patient(int ticketNum, bool fileFlag):m_patientLine(ticketNum) {
		m_fileIOflag = fileFlag;
	}

	Patient::~Patient() {
		if (m_name) {
			delete[] m_name;
			m_name = nullptr;
		}
	}

	bool Patient::fileIO() const {
		return m_fileIOflag;
	}

	void Patient::fileIO(bool fileFlag) {
		m_fileIOflag = fileFlag;
	}

	bool Patient::operator==(char ch) const {
		return this->type() == ch;
	}

	bool Patient::operator==(const Patient& P) const {
		return this->type() == P.type();
	}

	void Patient::setArrivalTime() {
		m_patientLine.resetTime();
	}
	
	Patient::operator Time() const {
		return (Time)m_patientLine;
	}

	int Patient::number() const {
		return m_patientLine.number();
	}

	ostream& Patient::csvWrite(ostream& ostr) const {
		ostr << type() << "," << m_name << "," << m_ohip << ",";
		m_patientLine.csvWrite(ostr);
		return ostr;
	}

	istream& Patient::csvRead(istream& istr) {
		char name[51];
		istr.get(name, 51, ',');
		
		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		
		istr.ignore(256, ',');
		istr >> m_ohip;
		istr.ignore(256, ',');
		m_patientLine.csvRead(istr);
		return istr;
	}

	ostream& Patient::write(ostream& ostr) const {
		m_patientLine.write(ostr) << endl;
		ostr << m_name << ", OHIP: " << m_ohip;
		return ostr;
	}

	istream& Patient::read(istream& istr) {
		cout << "Name: ";
		char name[51];
		istr.get(name, 51, '\n');

		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);

		istr.ignore(256, '\n');
		cout << "OHIP: ";
		int ohip;
		bool invalid;
		do {
			invalid = false;
			istr >> ohip;
			istr.ignore(256, '\n');
			if (istr.fail()) {
				cout << "Bad integer value, try again: ";
				istr.clear();
				istr.ignore(3000, '\n');
				invalid = true;
			}
			else if (ohip < 100000000 || ohip > 999999999) {
				cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
				istr.ignore(3000, '\n');
				invalid = true;
			}
		} while (invalid);
		m_ohip = ohip;
		return istr;
	}
}