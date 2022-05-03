#pragma once

#include <optional>
#include <vector>

class Date
{
public:
	enum class Month
	{
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER,
	};

	enum class WeekDay
	{
		SUNDAY = 0,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
	};

	Date(unsigned day, Month month, unsigned year);
	Date(unsigned timestamp = 0); // timestamp is how many days passed after m_startYear

	unsigned GetDay() const; // result is between 1-31
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;

	bool IsValid() const; // if date is out of valid range

	void operator++();
	void operator--();
	void operator+(unsigned day);
	void operator-(unsigned day);
	long operator-(const Date& other);
	void operator+=(unsigned day);
	void operator-=(unsigned day);
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator>=(const Date& other) const;
	friend std::ostream& operator<<(std::ostream& os, Date& date)
	{
		if (!date.IsValid())
		{
			os << "INVALID";
			return os;
		}

		unsigned day = date.GetDay();
		unsigned month = static_cast<unsigned>(date.GetMonth());
		os << (day >= 10 ? "" : "0") << day << ':' << (month >= 10 ? "" : "0") << month << ":" << date.GetYear();
		return os;
	}

private:
	static bool DateIsValid(unsigned day, Month month, unsigned year);
	static bool IsYearLeap(unsigned year);
	static unsigned ConvertDateInfoToTimeStamp(unsigned day, Month month, unsigned year);

	void CalculateDate() const;
	void SetInvalidState();

	long m_dayCounter;
	mutable std::optional<unsigned> m_year;
	mutable std::optional<unsigned> m_monthDay;
	mutable std::optional<Month> m_month;
	bool m_isValidState;
};
