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

#include <iostream>
#include "CovidPatient.h"
using namespace std;
namespace sdds
{
	int nextCovidTicket = 1;
	CovidPatient::CovidPatient():Patient(nextCovidTicket){
		nextCovidTicket++;
	}

	char CovidPatient::type() const {
		return 'C';
	}

	ostream& CovidPatient::csvWrite(ostream& ostr) const {
		Patient::csvWrite(ostr);
		return ostr;
	}

	istream& CovidPatient::csvRead(istream& istr) {
		Patient::csvRead(istr);
		nextCovidTicket = Patient::number() + 1;
		return istr;
	}

	ostream& CovidPatient::write(ostream& ostr) const {
		if (Patient::fileIO()) {
			csvWrite(ostr);
		}
		else {
			ostr << "COVID TEST" << endl;
			Patient::write(ostr) << endl;
		}
		return ostr;
	}

	istream& CovidPatient::read(istream& istr) {
		if (Patient::fileIO()) {
			csvRead(istr);
		}
		else {
			Patient::read(istr);
		}
		return istr;
	}
}
