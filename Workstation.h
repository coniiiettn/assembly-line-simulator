// Workstation.h
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <iostream>
#include <deque>
#include <string>
#include "CustomerOrder.h"

namespace seneca
{

	// Each queue is accessible outside this module's translation unit.
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation *m_pNextStation = nullptr;
		// A pointer to the next Workstation on the assembly line

	public:
		Workstation(const std::string &str) : Station(str){};
		void fill(std::ostream &os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation *station);
		Workstation *getNextStation() const;
		void display(std::ostream &os) const;
		Workstation &operator+=(CustomerOrder &&newOrder);

		Workstation(const Workstation &src) = delete;
		Workstation(Workstation &&src) = delete;
		Workstation &operator=(const Workstation &src) = delete;
		Workstation &operator=(Workstation &&src) = delete;
	};
}
#endif