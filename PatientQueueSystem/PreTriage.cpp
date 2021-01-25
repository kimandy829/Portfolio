/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2020/11/29  Preliminary release
2020/11/29  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "utils.h"
using namespace std;
namespace sdds
{
	PreTriage::PreTriage(const char* dataFilename):m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2){
		delete[] m_dataFilename;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage() {
		ofstream csvfile(m_dataFilename, ios::out | ios::trunc);
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		csvfile << m_averCovidWait << ',' << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;
		for (int i = 0; i < m_lineupSize; i++) {
			m_lineup[i]->csvWrite(csvfile);
			csvfile << '\n';
			cout << i + 1 << "- ";
			m_lineup[i]->csvWrite(cout);
			cout << endl;
			delete m_lineup[i];
			m_lineup[i] = nullptr;
		}
		csvfile.close();
		if (m_dataFilename) {
			delete[] m_dataFilename;
			m_dataFilename = nullptr;
		}
		cout << "done!" << endl;
	}

	const Time PreTriage::getWaitTime(const Patient& P) const {
		int numPatients = 0;
		for (int i = 0; i < m_lineupSize; i++) {
			if (P == m_lineup[i]->type()) {
				numPatients++;
			}
		}

		Time averTime;
		if (P == 'C') {
			averTime = m_averCovidWait;
		}
		else {
			averTime = m_averTriageWait;
		}
		averTime *= numPatients;
		return averTime;
	}

	void PreTriage::setAverageWaitTime(const Patient& P) {
		int ct = getTime();
		int ptt = (Time)P;
		int ptn = P.number();
		if (P == 'C') {
			m_averCovidWait = ((ct - ptt) + (m_averCovidWait *= (ptn - 1))) / ptn;
		}
		else {
			m_averTriageWait = ((ct - ptt) + (m_averTriageWait *= (ptn - 1))) / ptn;
		}
	}
	
	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		int result = -1;
		bool valid = true;
		for (int i = 0; i < m_lineupSize && valid; i++) {
			if (m_lineup[i]->type() == type) {
				result = i;
				valid = false;
			}
		}
		return result;
	}

	void PreTriage::load() {
		ifstream csvfile(m_dataFilename);
		cout << "Loading data..." << endl;
		csvfile >> m_averCovidWait;
		csvfile.ignore(1000, ',');
		csvfile >> m_averTriageWait;
		csvfile.ignore(1000, '\n');
		Patient* P = nullptr;
		int i;
		bool valid = true;
		for (i = 0; i < maxNoOfPatients; i++) {
			if (csvfile) {
				char c = 'x';
				csvfile >> c;
				csvfile.ignore(1000, ',');
				if (c == 'C') {
					P = new CovidPatient();
				}
				else if (c == 'T') {
					P = new TriagePatient();
				}
				else {
					break;
				}
				if (P != nullptr) {
					P->fileIO(true);
					P->csvRead(csvfile);
					csvfile.ignore(1000, '\n');
					P->fileIO(false);
					m_lineup[m_lineupSize] = P;
					m_lineupSize++;
				}
			}
			else {
				break;
			}
		}
		if (csvfile) {
			cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
		}

		if (i == 0) {
			cout << "No data or bad data file!" << endl << endl;
		}
		else {
			cout << i << " Records imported..." << endl << endl;
		}
		csvfile.close();
	}

	void PreTriage::reg() {
		if (m_lineupSize >= maxNoOfPatients) {
			cout << "Line up full!" << endl;
			return;
		}
		else {
			int selection;
			m_pMenu >> selection;
			if (selection == 1) {
				m_lineup[m_lineupSize] = new CovidPatient();
			}
			else if (selection == 2) {
				m_lineup[m_lineupSize] = new TriagePatient();
			}
			else {
				return;
			}
		}
		m_lineup[m_lineupSize]->setArrivalTime();
		cout << "Please enter patient information: " << endl;
		m_lineup[m_lineupSize]->fileIO(false);
		m_lineup[m_lineupSize]->read(cin);
		cout << endl << "******************************************" << endl;
		m_lineup[m_lineupSize]->write(cout);
		cout << "Estimated Wait Time: ";
		cout << getWaitTime(*m_lineup[m_lineupSize]) << endl;
		cout << "******************************************" << endl << endl;
		m_lineupSize++;
	}

	void PreTriage::admit() {
		int selection;
		char type = 'x'; 
		m_pMenu >> selection;
		if (selection == 1) {
			type = 'C';
		}
		else if (selection == 2) {
			type = 'T';
		}
		else {
			return;
		}
		int nextPatient = indexOfFirstInLine(type);
		if (nextPatient == -1) {
			return;
		}
		cout << endl << "******************************************" << endl;
		m_lineup[nextPatient]->fileIO(false);
		cout << "Calling for ";
		m_lineup[nextPatient]->write(cout);
		cout << "******************************************" << endl << endl;
		setAverageWaitTime(*m_lineup[nextPatient]);
		removeDynamicElement(m_lineup, nextPatient, m_lineupSize);
	}

	void PreTriage::run() {
		bool valid = true;
		int selection;
		do
		{
			m_appMenu >> selection;
			if (selection == 1) {
				reg();
			}
			else if (selection == 2) {
				admit();
			}
			else {
				valid = false;
			}
		} while (valid);
	}
}