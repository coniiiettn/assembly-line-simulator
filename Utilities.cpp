// Utilites.cpp
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;
namespace seneca
{

	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	
	string Utilities::extractToken(const string &str, size_t &next_pos, bool &more)
	{
		string temp = str;
		string token = "";
		more = false;

		if (temp.find(m_delimiter, next_pos) == next_pos)
		{
			throw "   ERROR: No token.\n";
		}
		else
		{
			if (next_pos < str.length())
			{
				trim(temp);

				auto pos = temp.find(m_delimiter, next_pos);

				token = temp.substr(next_pos, pos - next_pos);

				trim(token);
				if (token.length() > m_widthField)
				{
					m_widthField = token.length();
				}
				
				if (temp.find(m_delimiter, next_pos) != string::npos)
				{
					more = true;
					next_pos = pos + 1;
				}

			}
		}

		return token;
	}
	
	void Utilities::setDelimiter(char newDelimiter)
	{
		Utilities::m_delimiter = newDelimiter;
	}
	
	char Utilities::getDelimiter()
	{
		return Utilities::m_delimiter;
	}

	/*Utility Function*/
	void trim(string &str)
	{
		size_t first = str.find_first_not_of(" \t");
		size_t last = str.find_last_not_of(" \t");

		if (first == string::npos)
		{
			str.clear();
		}

		str = str.substr(first, last - first + 1);
	}
}