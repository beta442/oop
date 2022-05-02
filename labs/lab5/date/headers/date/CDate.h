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

	Date(unsigned timestamp = 0); // timestamp is how many days passed after 01.01.1970

	unsigned GetDay() const; // result is between 1-31

	Month GetMonth() const;

	unsigned GetYear() const; // result is between 

	WeekDay GetWeekDay() const;

	// возвращает информацию о корректности хранимой даты.
	// Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
	// или после:
	//	CDate date(1, January, 1970); --date;
	// метод date.IsValid() должен вернуть false;
	bool IsValid() const;

private:
	struct DateInfo
	{
		unsigned day;
		Month month;
		unsigned year;
	};

	bool IsYearLeap(const unsigned year) const;
	void SetInvalidState();
	void CalculateDate() const;
	/*DateInfo ConvertTimeStampToDateInfo(unsigned timestamp) const;
	unsigned ConvertDateInfoToTimeStamp(const DateInfo& info) const;*/

	inline static const long m_lowerCounterBound = 0; // 01.01.1970
	inline static const unsigned m_startYear = 1970;
	inline static const long m_upperCounterBound = 2932896; // 31.12.9999
	inline static const std::vector<long> m_daysToMonth365 = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	inline static const std::vector<long> m_daysToMonth366 = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

	std::optional<long> m_dayCounter;
	mutable std::optional<unsigned> m_year;
	mutable std::optional<unsigned> m_monthDay;
	mutable std::optional<Month> m_month;

	bool m_validStateStatus;
};
