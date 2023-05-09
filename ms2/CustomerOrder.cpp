#include<iostream>
#include<iomanip>
#include "CustomerOrder.h"
#include"Utilities.h"
namespace sdds
{
	size_t CustomerOrder::m_widthField;
	CustomerOrder::CustomerOrder()
	{
		CustomerOrder::m_widthField = 0;
		m_lstItem = nullptr;
	}
	CustomerOrder::CustomerOrder(std::string str)
	{
		Utilities utils;
		size_t next_pos = 0;
		bool more = true;
		m_name = utils.extractToken(str, next_pos, more); // extract name
		m_product = utils.extractToken(str, next_pos, more);
		// item is a string used to extract different items in the order
		std::string item;
		while (more) {
			item = utils.extractToken(str, next_pos, more);
			add(item);
		}
		if (m_widthField < utils.getFieldWidth()) {
			m_widthField = utils.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& order)
	{
		throw "Called Copy constructor";
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept
	{
		if (this != &order)
		{
			freeMemory();
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;
			m_name = order.m_name;
			m_product = order.m_product;
			order.m_lstItem = nullptr;
			order.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept
	{
		operator=(std::move(order));
	}
	
	void CustomerOrder::freeMemory()
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_cntItem = 0;
	}
	CustomerOrder::~CustomerOrder()
	{
		freeMemory();
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool ret = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
			{
				ret = false;
			}
		}
		return ret;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		// incomplete function
		bool ret = true;
		Utilities utils;
		size_t next_pos = 0;
		bool more = true;
		std::string temp;
		while (more) {
			temp = utils.extractToken(itemName, next_pos, more);
			bool found = false;
			bool found_filled = false;
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (temp == m_lstItem[i]->m_itemName)
				{
					found = true;
					if (m_lstItem[i]->m_isFilled == true)
					{
						found_filled = true;
					}
					
				}
			}
			if (found == true && found_filled == false)
			{
				ret = false;
			}
		}
		return ret;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		int index = -1;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (station.getItemName() == m_lstItem[i]->m_itemName)
			{
				index = i;
				break;
			}
		}
		if (index != -1 && station.getQuantity() > 0 && m_lstItem[index]->m_isFilled == false)
		{
			station.updateQuantity();
			m_lstItem[index]->m_isFilled = true;
			m_lstItem[index]->m_serialNumber = station.getNextSerialNumber();
			os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
		}
		else if (index != -1 && station.getQuantity() == 0 && m_lstItem[index]->m_isFilled == false) {
			os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name;
		os << " - ";
		os << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[";
			
			os <<std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os<<std::setfill(' ') << std::left << std::setw(m_widthField+2) << m_lstItem[i]->m_itemName;
			os << " - ";
			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << std::endl;
		}

	}
	void CustomerOrder::add(std::string& str)
	{
		Item* item = new Item(str);
		if (m_cntItem > 0)
		{
			Item** temp = m_lstItem;
			m_lstItem = new Item * [m_cntItem + 1];
			for (size_t i = 0; i < m_cntItem; i++)
			{
				m_lstItem[i] = temp[i];
			}
			m_lstItem[m_cntItem] = item;
			m_cntItem++;
		}
		else {
			m_lstItem = new Item * [1];
			m_lstItem[0] = item;
			m_cntItem = 1;
		}
	}
}
