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

#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
namespace sdds
{
	class Patient :public IOAble
	{
		char* m_name = nullptr;
		int m_ohip = -1;
		Ticket m_patientLine;
		bool m_fileIOflag;
	public:
		Patient(int ticketNum = 0, bool fileFlag = false);
		Patient(const Patient& P) = delete;
		Patient& operator=(const Patient& P) = delete;
		~Patient();
		virtual char type() const = 0;
		bool fileIO() const;
		void fileIO(bool fileFlag);
		//character comparison
		bool operator==(char ch) const;
		//comparing to another patient
		bool operator==(const Patient& P) const;
		void setArrivalTime();
		operator Time() const;
		int number() const;
		std::ostream& csvWrite(std::ostream& ostr) const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_PATIENT_H_
