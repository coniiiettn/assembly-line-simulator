// CustomerOrder.cpp
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
namespace seneca
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const string &str)
	{
		Utilities ut;
		bool more = false;
		size_t pos = 0;
		string temp = "";
		vector<Item *> tmpItem;

		m_name = ut.extractToken(str, pos, more);
		trim(m_name);

		m_product = ut.extractToken(str, pos, more);
		trim(m_product);

		while (more)
		{

			temp = ut.extractToken(str, pos, more);
			// trim(temp);
			tmpItem.push_back(new Item(temp));
		}
		m_cntItem = tmpItem.size();

		m_lstItem = new Item *[m_cntItem];

		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = std::move(tmpItem[i]);
		}

		CustomerOrder::m_widthField = std::max(ut.getFieldWidth(), CustomerOrder::m_widthField);
	}

	CustomerOrder::CustomerOrder(const CustomerOrder &src)
	{
		throw runtime_error("Copy Constructor is called");
	}

	CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept
	{
		// 		m_name = src.m_name;
		// 		m_product = src.m_product;
		// 		m_cntItem = src.m_cntItem;
		// 		m_lstItem = src.m_lstItem;
		//
		// 		src.m_name = "";
		// 		src.m_product = "";
		// 		src.m_cntItem = 0;
		// 		src.m_lstItem = nullptr;
		*this = std::move(src);
	}

	CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
	{

		if (this != &src)
		{

			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;

			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}

		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool filled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled))
			{
				filled = false;
			}
		}

		return filled;
	}

	bool CustomerOrder::isItemFilled(const std::string &itemName) const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName && !(m_lstItem[i]->m_isFilled))
			{
				filled = false;
			}
		}

		return filled;
	}

	void CustomerOrder::fillItem(Station &station, std::ostream &os)
	{

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled) && m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					cout << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					return;
				}
				else
				{
					cout << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream &os) const
	{
		os << m_name << " - " << m_product << endl;

		for (size_t i = 0; i < m_cntItem; i++)
		{

			os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber;

			os << "] " << left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName << " - ";

			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED" << endl;
			}
			else
			{
				os << "TO BE FILLED" << endl;
			}
		}
	}
}