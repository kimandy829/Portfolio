/* Citation and Sources...
Final Project Milestone 4
Module: Menu
Filename: Menu.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/22  Preliminary release
2020/11/22  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "TriagePatient.h"
using namespace std;
namespace sdds
{
	int nextTriageTicket = 1;
	TriagePatient::TriagePatient():Patient(nextTriageTicket) {
		m_symptoms = nullptr;
		nextTriageTicket++;
	}

	char TriagePatient::type() const {
		return 'T';
	}

	ostream& TriagePatient::csvWrite(ostream& ostr) const {
		Patient::csvWrite(ostr);
		ostr << ',' << m_symptoms;
		return ostr;
	}

	istream& TriagePatient::csvRead(istream& istr) {
		char symptoms[511];
		delete[] m_symptoms;
		Patient::csvRead(istr);
		istr.ignore(256, ',');
		istr.get(symptoms, 511, '\n');
		m_symptoms = new char[strlen(symptoms) + 1];
		strcpy(m_symptoms, symptoms);
		nextTriageTicket = Patient::number() + 1;
		return istr;
	}

	ostream& TriagePatient::write(ostream& ostr) const {
		if (Patient::fileIO()) {
			csvWrite(ostr);
		}
		else {
			ostr << "TRIAGE" << endl;
			Patient::write(ostr) << endl;
			ostr << "Symptoms: " << m_symptoms << endl;
		}
		return ostr;
	}

	istream& TriagePatient::read(istream& istr) {
		if (Patient::fileIO()) {
			csvRead(istr);
		}
		else {
			char symptoms[511];
			delete[] m_symptoms;
			Patient::read(istr);
			cout << "Symptoms: ";
			//istr.ignore(256, '\n');
			istr.get(symptoms, 511, '\n');
			istr.ignore(256, '\n');
			m_symptoms = new char[strlen(symptoms) + 1];
			strcpy(m_symptoms, symptoms);
		}
		return istr;
	}

	TriagePatient::~TriagePatient() {
		if (m_symptoms) {
			delete[] m_symptoms;
			m_symptoms = nullptr;
		}
	}
}
