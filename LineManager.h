// LineManager.h
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "Workstation.h"

namespace seneca
{
	class LineManager
	{
		// The collection of workstations for the current assembly line
		std::vector<Workstation *> m_activeLine;
		// The total num of CustomerOrder objects
		size_t m_cntCustomerOrder{};
		// points to the first active station on the current line

		Workstation *m_firstStation{};

	public:
		LineManager(const std::string &file, const std::vector<Workstation *> &stations);

		void reorderStations();
		bool run(std::ostream &os);
		void display(std::ostream &os) const;
	};
}

#endif