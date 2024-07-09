// Workstation.cpp
#include <iostream>
#include "Workstation.h"

using namespace std;

namespace seneca
{
	deque<CustomerOrder> g_pending;
	deque<CustomerOrder> g_completed;
	deque<CustomerOrder> g_incomplete;

	void Workstation::fill(std::ostream &os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)
			{

				if (!m_pNextStation)
				{
					if (m_orders.front().isOrderFilled())
					{
						g_completed.push_back(std::move(m_orders.front()));
					}
					else
					{
						g_incomplete.push_back(std::move(m_orders.front()));
					}
					m_orders.pop_front();
					return true;
				}
				else
				{
					*m_pNextStation += std::move(m_orders.front());
					m_orders.pop_front();
					return true;
				}
			}
		}

		return false;
	}

	void Workstation::setNextStation(Workstation *station)
	{
		m_pNextStation = station;
	}

	Workstation *Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream &os) const
	{
		if(m_pNextStation)
		{
			os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
		}
		else
		{
			os << getItemName() << " --> End of Line" << endl;
		}
		
	}

	Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
	{
		m_orders.push_back(std::move(newOrder));

		return *this;
	}
}