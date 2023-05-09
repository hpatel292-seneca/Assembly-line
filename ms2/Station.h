#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include<string>
#include"Utilities.h"
namespace sdds
{
	class Station
	{
		int m_id{};
		std::string m_itemName{};
		std::string m_desc{};
		unsigned int m_nextSerial{};
		unsigned int m_stock{};

		static int m_widthField; // set initially to zero
		static int id_generator;

	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif

