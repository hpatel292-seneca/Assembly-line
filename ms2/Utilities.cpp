#include<iostream>
#include "Utilities.h"
namespace sdds
{
	char Utilities::m_delimiter;
	void sdds::Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t sdds::Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string sdds::Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		int start_index;
		int end_index;
		int index_delimiter;
		if (str[next_pos] == sdds::Utilities::m_delimiter)
		{
			more = false;
			throw "delemiter found at next_pos";
		}
		std::string temp = str.substr(next_pos);
		if (more)
		{
			index_delimiter = temp.find(sdds::Utilities::m_delimiter);
			if (index_delimiter == -1)
			{
				index_delimiter = temp.size();
				more = false;
			}
			
			temp = str.substr(next_pos, index_delimiter);
			start_index = temp.find_first_not_of(' ');
			end_index = temp.find_last_not_of(' ');
			temp = temp.substr(start_index, end_index - start_index + 1);
			if (m_widthField < temp.size())
			{
				m_widthField = temp.size();
			}
			next_pos = next_pos+index_delimiter + 1;
		}
		return temp;
	}

	void sdds::Utilities::setDelimiter(char newDelimiter)
	{
		sdds::Utilities::m_delimiter = newDelimiter;
	}

	char sdds::Utilities::getDelimiter()
	{
		return sdds::Utilities::m_delimiter;
	}
}