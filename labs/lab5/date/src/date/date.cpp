#include "../../headers/stdafx.h"

#include "../../headers/date/CDate.h"

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
	else
	{
		m_dayCounter = ConvertDateInfoToTimeStamp(day, month, year);
	}
}

const long m_upperCounterBound = 2932896; // 31.12.9999

Date::Date(unsigned timestamp)
	: m_dayCounter(timestamp)
	, m_isValidState(true)
{
	if (timestamp > m_upperCounterBound)
	{
		SetInvalidState();
	}
}

bool Date::IsValid() const
{
	return m_isValidState;
}

bool Date::IsYearLeap(unsigned year)
{
	return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

const unsigned START_YEAR = 1970;
const unsigned END_YEAR = 9999;
const Date::Month START_MONTH = Date::Month(1);
const int START_MONTH_DAY = 1;

void Date::SetInvalidState()
{
	if (m_isValidState)
	{
		m_dayCounter.emplace(0);
		m_year.emplace(START_YEAR);
		m_month.emplace(START_MONTH);
		m_monthDay.emplace(START_MONTH_DAY);
		m_isValidState = false;
	}
}

unsigned Date::GetYear() const
{
	if (!IsValid())
	{
		return START_YEAR;
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
		return START_MONTH;
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
		return START_MONTH_DAY;
	}

	if (!m_monthDay.has_value())
	{
		CalculateDate();
	}

	return *m_monthDay;
}

const Date::WeekDay START_WEEK_DAY = Date::WeekDay(0);
Date::WeekDay DayOfWeek(unsigned day, Date::Month month, unsigned year);

Date::WeekDay Date::GetWeekDay() const
{
	if (!IsValid())
	{
		return START_WEEK_DAY;
	}

	if (!m_year.has_value() || !m_month.has_value() || !m_monthDay.has_value())
	{
		CalculateDate();
	}

	return DayOfWeek(m_monthDay.value(), m_month.value(), m_year.value());
}

const int START_MONTH_INDEX = 1;
const int END_MONTH_INDEX = 12;
const long LOWER_COUNTER_BOUND = 0; // 01.01.1970

const std::vector<unsigned> DAYS_TO_MONTH_365 = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const std::vector<unsigned> DAYS_TO_MONTH_366 = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

unsigned Date::ConvertDateInfoToTimeStamp(unsigned day, Month month, unsigned year)
{
	const int providedMonthIndex = static_cast<int>(month);
	if (year < START_YEAR || year > END_YEAR || providedMonthIndex < START_MONTH_INDEX || providedMonthIndex > END_MONTH_INDEX)
	{
		return 0;
	}

	unsigned counter = LOWER_COUNTER_BOUND;
	unsigned yearPassed = year;

	short monthIndex = END_MONTH_INDEX;
	const std::vector<unsigned>* daysToMonth = IsYearLeap(year) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;

	while (yearPassed >= START_YEAR)
	{
		daysToMonth = IsYearLeap(yearPassed) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;
		counter += (*daysToMonth)[monthIndex];
		if (yearPassed == START_YEAR)
		{
			counter -= (*daysToMonth)[monthIndex];
			counter += (*daysToMonth)[providedMonthIndex - 1];
			counter += day - 1;
		}
		--yearPassed;
	}

	return counter;
}

bool Date::DateIsValid(unsigned day, Month month, unsigned year)
{
	const int monthIndex = static_cast<int>(month);
	if (day == 0 || year < START_YEAR || year > END_YEAR || monthIndex < START_MONTH_INDEX || monthIndex > END_MONTH_INDEX)
	{
		return false;
	}

	const std::vector<unsigned>* daysToMonth = IsYearLeap(year) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;

	if (day > (*daysToMonth)[monthIndex] - (*daysToMonth)[monthIndex - 1])
	{
		return false;
	}
	return true;
}

const std::vector<int> SAKAMOTO_MONTH_TO_INT = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

Date::WeekDay DayOfWeek(unsigned day, Date::Month month, unsigned year)
{
	const int monthIndex = static_cast<int>(month);
	if (day == 0 || monthIndex < START_MONTH_INDEX || monthIndex > END_MONTH_INDEX || year < START_YEAR || year > END_YEAR)
	{
		return START_WEEK_DAY;
	}

	if (monthIndex < 3)
	{
		year -= 1;
	}

	return Date::WeekDay((year + year / 4 - year / 100 + year / 400 + SAKAMOTO_MONTH_TO_INT[monthIndex - 1] + day) % 7);
}

void Date::CalculateDate() const
{
	long count = LOWER_COUNTER_BOUND - 1;

	short monthIndex = END_MONTH_INDEX;
	unsigned year = START_YEAR - 1;
	unsigned mem, day;
	const std::vector<unsigned>* daysToMonth = &DAYS_TO_MONTH_365;
	while (count < m_dayCounter)
	{
		daysToMonth = IsYearLeap(year) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;
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
