#include "../headers/stdafx.h"

#include "../headers/date/CDate.h"

Date::Date(unsigned day, Month month, unsigned year)
	: m_monthDay(day)
	, m_month(month)
	, m_year(year)
	, m_isValidState(true)
{
	if (!DateIsValid(day, month, year))
	{
		SetInvalidState();
	}
}

Date::Date(unsigned timestamp)
	: m_dayCounter(timestamp)
	, m_isValidState(true)
{
	if (timestamp > m_upperCounterBound)
	{
		SetInvalidState();
	}
}

bool Date::DateIsValid(unsigned day, Month month, unsigned year)
{
	const int monthIndex = static_cast<int>(month);
	if (day == 0 || year < m_startYear || year > m_endYear || monthIndex < m_startMonthIndex || monthIndex > m_endMonthIndex)
	{
		return false;
	}

	const std::vector<unsigned>* daysToMonth = IsYearLeap(year) ? &m_daysToMonth366 : &m_daysToMonth365;

	if (day > (*daysToMonth)[monthIndex] - (*daysToMonth)[monthIndex - 1])
	{
		return false;
	}
	return true;
}

bool Date::IsValid() const
{
	return m_isValidState;
}

bool Date::IsYearLeap(const unsigned year) const
{
	return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

void Date::SetInvalidState() const
{
	if (m_isValidState)
	{
		m_dayCounter.emplace(0);
		m_year.emplace(m_startYear);
		m_month.emplace(m_startMonth);
		m_monthDay.emplace(m_startMonthDay);
		m_isValidState = false;
	}
}

void Date::CalculateDate() const
{
	long count = m_lowerCounterBound - 1;

	short monthIndex = 12;
	unsigned year = m_startYear - 1;
	unsigned mem, day;
	const std::vector<unsigned>* daysToMonth = &m_daysToMonth365;
	while (count < m_dayCounter)
	{
		daysToMonth = IsYearLeap(year) ? &m_daysToMonth366 : &m_daysToMonth365;
		++year;

		count += (*daysToMonth)[monthIndex];
		if (count == m_dayCounter)
		{
			day = 31;
		}
		while (count > m_dayCounter)
		{
			--monthIndex;
			count -= (*daysToMonth)[monthIndex + 1] - (*daysToMonth)[monthIndex];
			if (count < m_dayCounter)
			{
				mem = count;
			}
			while (count < m_dayCounter)
			{
				++count;
			}
			day = count - mem;
		}
	}
	if (monthIndex != 12)
	{
		++monthIndex;
	}

	m_year.emplace(year);
	m_month.emplace(Month(monthIndex));
	m_monthDay.emplace(day);
}

unsigned Date::GetYear() const
{
	if (!IsValid())
	{
		return m_startYear;
	}

	if (!m_year.has_value())
	{
		CalculateDate();
	}

	return *m_year;
}

Date::Month Date::GetMonth() const
{
	if (!IsValid())
	{
		return m_startMonth;
	}

	if (!m_month.has_value())
	{
		CalculateDate();
	}

	return *m_month;
}

unsigned Date::GetDay() const
{
	if (!IsValid())
	{
		return m_startMonthDay;
	}

	if (!m_monthDay.has_value())
	{
		CalculateDate();
	}

	return *m_monthDay;
}
