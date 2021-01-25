/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/13  Preliminary release
2020/11/13  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#include "Time.h"
#include "utils.h"

using namespace std;
namespace sdds
{
	Time& Time::reset() {
		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min) {
		m_min = min;
	}

	ostream& Time::write(ostream& ostr) const {
		int hour = 0;
		int min = 0;
		convert(m_min, hour, min);

		ostr.fill('0');
		ostr.width(2);
		ostr << hour;
		ostr << ":";
		ostr.fill('0');
		ostr.width(2);
		ostr << min;

		return ostr;
	}

	istream& Time::read(istream& istr) {
		int hour = 0;
		int min = 0;
		char c = 0;

		istr >> hour >> c >> min;
		if (c != ':') {
			istr.setstate(ios::failbit);
		}
		else {
			m_min = hour * 60 + min;
		}
		return istr;
	}

	Time::operator int() const {
		return m_min;
	}

	Time& Time::operator*=(int val) {
		m_min *= val;
		return *this;
	}

	Time& Time::operator-=(const Time& D) {
		
		int diff = this->m_min - D.m_min;
		if (diff < 0) {
			this->m_min = (this->m_min + 1440) - D.m_min;
		}
		else {
			this->m_min -= D.m_min;
		}
		return *this;
	}

	Time Time::operator-(const Time& ROperand) {
		Time LOperand = *this;
		LOperand -= ROperand;
		return LOperand;
	}

	ostream& operator<<(ostream& ostr, const Time& T) {
		T.write(ostr);
		return ostr;
	}

	istream& operator>>(istream& istr, Time& T) {
		T.read(istr);
		return istr;
	}
}