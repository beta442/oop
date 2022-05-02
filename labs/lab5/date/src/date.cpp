#include "../headers/stdafx.h"

#include "../headers/date/CDate.h"

//Date::Date(unsigned day, Month month, unsigned year)
//	: m_monthDay(day)
//	, m_month(month)
//	, m_year(year)
//{
//	if ()
//	{
//	}
//}

Date::Date(unsigned timestamp)
	: m_dayCounter(timestamp)
	, m_validStateStatus(true)
{
	if (timestamp > m_upperCounterBound)
	{
		SetInvalidState();
	}
}

bool Date::IsValid() const
{
	return m_validStateStatus;
}

bool Date::IsYearLeap(const unsigned year) const
{
	return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

void Date::SetInvalidState()
{
	if (m_validStateStatus)
	{
		m_dayCounter.reset();
		m_year.reset();
		m_month.reset();
		m_monthDay.reset();
		m_validStateStatus = false;
	}
}

void Date::CalculateDate() const
{
	if (m_dayCounter > m_upperCounterBound)
	{
		return;
	}

	long count = m_lowerCounterBound - 1;

	short monthIndex = 12;
	unsigned year = m_startYear - 1;
	unsigned mem, day;
	const std::vector<long>* daysToMonth = &m_daysToMonth365;
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
		return Month(1);
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
		return 1;
	}

	if (!m_monthDay.has_value())
	{
		CalculateDate();
	}

	return *m_monthDay;
}
