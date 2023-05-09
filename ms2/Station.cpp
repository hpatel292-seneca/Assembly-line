#include<iostream>
#include "Station.h"
#include"Utilities.h"
namespace sdds
{
	int sdds::Station::m_widthField = 0; 
	int sdds::Station::id_generator = 0;
	Station::Station(const std::string& str)
	{
		std::string temp;
		size_t next_pos = 0;
		bool more = true;
		sdds::Utilities utils;
		id_generator++;
		m_id = id_generator;
		
		m_itemName = utils.extractToken(str, next_pos, more); // extract name

		temp = utils.extractToken(str, next_pos, more); // extract serial number but it is in string
		m_nextSerial = std::stoi(temp);

		temp = utils.extractToken(str, next_pos, more); // extract quantity
		m_stock = std::stoi(temp);

		Station::m_widthField = Station::m_widthField > utils.getFieldWidth() ? Station::m_widthField : utils.getFieldWidth();

		m_desc = utils.extractToken(str, next_pos, more);



	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		m_nextSerial++;
		return m_nextSerial-1;

		// or use postfix
		// return m_nextSerial++;
	}

	size_t Station::getQuantity() const
	{
		return m_stock;
	}

	void Station::updateQuantity()
	{
		if (m_stock != 0)
		{
			m_stock--;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		
		//os.fill('0');
		os.fill('0');
			os.width(3);
			os << m_id;
			os << " | ";
			os.fill(' ');
			os.width(Station::m_widthField+1);
			os.setf(std::ios::left);
			os.unsetf(std::ios::right);
			
			os << m_itemName;
			os.fill('0');
			os << " | ";
			os.width(6);
			os.setf(std::ios::right);
			os.unsetf(std::ios::left);
			os << m_nextSerial;
			os << " | ";
			os.fill(' ');
			if (full)
			{
			os.width(4);
			os << m_stock;
			os << " | ";
			os << m_desc;
			}
			os << std::endl;
	}

}