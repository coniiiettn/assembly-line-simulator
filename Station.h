// Station.h
#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <iostream>
#include "Utilities.h"
namespace seneca{

	class Station{
		int m_id;
		std::string m_name{}; //Item name
		std::string m_desc{};
		size_t m_serial = 0;
		size_t m_num = 0; //Quantity in stock

		static size_t m_widthField;
		static int id_generator;

	public:
		Station(){};
		Station(const std::string &str);
		const std::string &getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream &os, bool full) const;
		
	};
}
#endif