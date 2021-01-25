/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/14  Preliminary release
2020/11/14  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#include <iostream>
#include "IOAble.h"
using namespace std;
namespace sdds
{
	ostream& operator<<(ostream& ostr, const IOAble& I) {
		I.write(ostr);
		return ostr;
	}

	istream& operator>>(istream& istr, IOAble& I) {
		I.read(istr);
		return istr;
	}
}