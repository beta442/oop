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


	// возвращает информацию о корректности хранимой даты.
	// Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	//	CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const;

	void operator++();
	void operator--();
	void operator+(unsigned day);
	void operator-(unsigned day);
	long operator-(const Date date);
	void operator+=(unsigned day);
	void operator-=(unsigned day);

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
