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

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "utils.h"
#include "Menu.h"
using namespace std;
namespace sdds
{
	Menu::Menu(const char* text, int NoOfSelections) {
		m_text = new char[strlen(text) + 1];
		strcpy(m_text, text);
		m_noOfSel = NoOfSelections;
	}

	Menu::~Menu() {
		delete[] m_text;
		m_text = nullptr;
	}

	ostream& Menu::display(ostream& ostr) const {
		ostr << m_text << endl;
		ostr << "0- Exit" << endl;
		ostr << "> ";

		return ostr;
	}

	int& Menu::operator>>(int& Selection) {
		display();
		int select;
		bool invalid;
		do {
			invalid = false;
			cin >> select;
			cin.ignore(256, '\n');
			if (cin.fail()) {
				cout << "Bad integer value, try again: ";
				cin.clear();
				cin.ignore(3000, '\n');
				invalid = true;
			}
			else if (select < 0 || select > m_noOfSel) {
				cout << "Invalid value enterd, retry[0 <= value <= " << m_noOfSel << "]: ";
				cin.ignore(3000, '\n');
				invalid = true;
			}
		} while (invalid);
		Selection = select;

		return Selection;
	}
}