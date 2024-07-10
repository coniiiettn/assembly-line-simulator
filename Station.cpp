// Station.cpp
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace seneca
{

	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	Station::Station(const string &str)
	{
		Utilities ut;
		m_id = ++id_generator;
		bool more = false;
		size_t pos = 0;
		string temp = "";

		m_name = ut.extractToken(str, pos, more);
		temp = ut.extractToken(str, pos, more);
		m_serial = stoi(temp);

		temp = ut.extractToken(str, pos, more);
		m_num = stoi(temp);

		Station::m_widthField = std::max(ut.getFieldWidth(), Station::m_widthField);

		m_desc = ut.extractToken(str, pos, more);
		trim(m_desc);
	}

	const string &Station::getItemName() const
	{
		return m_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serial++;
	}

	size_t Station::getQuantity() const
	{
		return m_num;
	}

	void Station::updateQuantity()
	{
		if (m_num > 0)
		{
			m_num--;
		}
	}

	void Station::display(ostream &os, bool full) const
	{
		if (!full)
		{
			os << setw(3) << right << setfill('0') << m_id;
			os << " | " << setw(m_widthField) << setfill(' ') << left << getItemName();
			os << " | " << right << setw(6) << setfill('0') << m_serial;
			os << " | " << endl;
		}
		else
		{
			os << setw(3) << right << setfill('0') << m_id;
			os << " | " << setw(m_widthField) << setfill(' ') << left << getItemName();
			os << " | " << right << setw(6) << setfill('0') << m_serial;
			os << " | " << setw(4) << setfill(' ') << getQuantity();
			os << " | " << left << m_desc << endl;
		}
	}

}