// LineManager.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"

using namespace std;

namespace seneca
{
	LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
	{
		ifstream ifstr(file);

		Utilities ut;
		ut.setDelimiter('|');

		if (ifstr)
		{
			string rec = "";

			while (getline(ifstr, rec))
			{
				string tempFirst = ""; // token for first station
				string tempSec = "";   // token for second station
				bool more = false;
				trim(rec);
				size_t pos = 0;
				tempFirst = ut.extractToken(rec, pos, more);

				if (more)
				{
					tempSec = ut.extractToken(rec, pos, more);
				}
				

				auto match = [&](Workstation *ws, const std::string &name)
				{
					return ws->getItemName() == name;
				};

				for_each(stations.begin(), stations.end(), [&](Workstation *ws)
						 {
                             if (match(ws, tempFirst))
                             {
								 for_each(stations.begin(), stations.end(), [&](Workstation *re) {
									 if (match(re, tempSec))
									 {
										 ws->setNextStation(re);
									 }
								 });
					m_activeLine.push_back(ws);

                             } });
			}


			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws)
					 {
    bool check = any_of(stations.begin(), stations.end(), [=](Workstation* other)
    {
        return ws == other->getNextStation();
    });

    if (!check)
    {
        m_firstStation = ws;
    } });

			m_cntCustomerOrder = g_pending.size();

			ifstr.close(); // Close the file stream
		}
		else
		{
			throw "File cannot be opened!";
		}
	}


	void LineManager::reorderStations()
	{

		vector<Workstation *> reorder;
		Workstation *next = m_firstStation;

		while (next)
		{
			reorder.push_back(next);
			next = next->getNextStation();
		}

		m_activeLine = reorder;
	}
	bool LineManager::run(std::ostream &os)
	{
		static size_t count = 1; // Declaring count as static to retain its value between function calls
			os << "Line Manager Iteration: " << count++ << endl;

		if (!g_pending.empty())
		{

			*m_activeLine.front() += std::move(g_pending.front());
			g_pending.pop_front();
		}

		// for each station on the line, executes one fill operation
		auto fill = [&](Workstation *ws)
		{
			ws->fill(os);
		};
		for_each(m_activeLine.begin(), m_activeLine.end(), fill);

		// for each station on the line, attempts to move an order down the line
		auto move = [&](Workstation *ws)
		{
			ws->attemptToMoveOrder();
		};
		for_each(m_activeLine.begin(), m_activeLine.end(), move);

		return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
	}

	void LineManager::display(std::ostream &os) const
	{
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws)
				 { ws->display(os); });
	}
	
	
	
} 