#include "../../../../catch2/catch.hpp"

#include "../../../../labs/lab5/date/headers/date/CDate.h"

TEST_CASE("Date at create state")
{
	WHEN("Wrong timestamp provided")
	{
		Date date{ 2932897 };
		THEN("Date is in invalid state")
		{
			REQUIRE_FALSE(date.IsValid());
		}
		THEN("Getters shows default info")
		{
			REQUIRE(date.GetDay() == 1);
			REQUIRE(date.GetMonth() == Date::Month(1));
			REQUIRE(date.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date.GetYear() == 1970);
		}
	}

	WHEN("Correct timestamp provided")
	{
		Date date1{ 0 };
		Date date2{ 2932896 };
		THEN("Date is in valid state")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());
		}
	}

	WHEN("Correct timestamp provided")
	{
		Date date1{ 0 };
		const unsigned expectedDay1 = 1;
		const Date::Month expectedMonth1 = Date::Month(1);
		const unsigned expectedYear1 = 1970;
		const Date::WeekDay expectedDayOfWeek1 = Date::WeekDay(4);
		Date date2{ 2932896 };
		const unsigned expectedDay2 = 31;
		const Date::Month expectedMonth2 = Date::Month(12);
		const unsigned expectedYear2 = 9999;
		const Date::WeekDay expectedDayOfWeek2 = Date::WeekDay(5);
		Date date3{ 1436428 };
		const unsigned expectedDay3 = 23;
		const Date::Month expectedMonth3 = Date::Month(10);
		const unsigned expectedYear3 = 5902;
		const Date::WeekDay expectedDayOfWeek3 = Date::WeekDay(4);

		THEN("Getters are working correctly")
		{
			REQUIRE(date1.GetDay() == expectedDay1);
			REQUIRE(date1.GetMonth() == expectedMonth1);
			REQUIRE(date1.GetYear() == expectedYear1);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek1);

			REQUIRE(date2.GetDay() == expectedDay2);
			REQUIRE(date2.GetMonth() == expectedMonth2);
			REQUIRE(date2.GetYear() == expectedYear2);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek2);

			REQUIRE(date3.GetDay() == expectedDay3);
			REQUIRE(date3.GetMonth() == expectedMonth3);
			REQUIRE(date3.GetYear() == expectedYear3);
			REQUIRE(date3.GetWeekDay() == expectedDayOfWeek3);
		}
	}

	WHEN("Wrong date provided")
	{
		Date date1{ 0, Date::Month(0), 1970 };
		Date date2{ 1, Date::Month(1), 10000 };
		Date date3{ 32, Date::Month(1), 1972 };
		Date date4{ 30, Date::Month(2), 1972 };
		Date date5{ 29, Date::Month(2), 1971 };
		Date date6{ 32, Date::Month(3), 1972 };
		Date date7{ 31, Date::Month(4), 1972 };
		Date date8{ 32, Date::Month(5), 1972 };
		Date date9{ 31, Date::Month(6), 1972 };
		Date date10{ 32, Date::Month(7), 1972 };
		Date date11{ 32, Date::Month(8), 1972 };
		Date date12{ 31, Date::Month(9), 1972 };
		Date date13{ 32, Date::Month(10), 1972 };
		Date date14{ 31, Date::Month(11), 1972 };
		Date date15{ 32, Date::Month(12), 1972 };
		Date date16{ 15, Date::Month(-1), 1972 };
		Date date17{ 15, Date::Month(13), 1972 };
		THEN("Dates are in invalid state")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
			REQUIRE_FALSE(date5.IsValid());
			REQUIRE_FALSE(date6.IsValid());
			REQUIRE_FALSE(date7.IsValid());
			REQUIRE_FALSE(date8.IsValid());
			REQUIRE_FALSE(date9.IsValid());
			REQUIRE_FALSE(date10.IsValid());
			REQUIRE_FALSE(date11.IsValid());
			REQUIRE_FALSE(date12.IsValid());
			REQUIRE_FALSE(date13.IsValid());
			REQUIRE_FALSE(date14.IsValid());
			REQUIRE_FALSE(date15.IsValid());
			REQUIRE_FALSE(date16.IsValid());
			REQUIRE_FALSE(date17.IsValid());
		}
		THEN("Getters shows default info")
		{
			REQUIRE(date1.GetDay() == 1);
			REQUIRE(date1.GetMonth() == Date::Month(1));
			REQUIRE(date1.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date1.GetYear() == 1970);
			REQUIRE(date2.GetDay() == 1);
			REQUIRE(date2.GetMonth() == Date::Month(1));
			REQUIRE(date2.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date2.GetYear() == 1970);
			REQUIRE(date3.GetDay() == 1);
			REQUIRE(date3.GetMonth() == Date::Month(1));
			REQUIRE(date3.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date3.GetYear() == 1970);
			REQUIRE(date10.GetDay() == 1);
			REQUIRE(date10.GetMonth() == Date::Month(1));
			REQUIRE(date10.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date10.GetYear() == 1970);
			REQUIRE(date15.GetDay() == 1);
			REQUIRE(date15.GetMonth() == Date::Month(1));
			REQUIRE(date15.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date15.GetYear() == 1970);
			REQUIRE(date17.GetDay() == 1);
			REQUIRE(date17.GetMonth() == Date::Month(1));
			REQUIRE(date17.GetWeekDay() == Date::WeekDay(0));
			REQUIRE(date17.GetYear() == 1970);
		}
	}

	WHEN("Correct dates provided")
	{
		Date date1{ 30, Date::Month(6), 9876 };
		Date date2{ 1, Date::Month(1), 1970 };
		Date date3{ 31, Date::Month(12), 9999 };
		THEN("Dates in valid state")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());
			REQUIRE(date3.IsValid());
		}
	}

	WHEN("Correct dates provided")
	{
		const unsigned expectedDay1 = 30;
		const Date::Month expectedMonth1 = Date::Month(6);
		const unsigned expectedYear1 = 9876;
		const Date::WeekDay expectedDayOfWeek1 = Date::WeekDay(5);
		Date date1{ expectedDay1, expectedMonth1, expectedYear1 };
		const unsigned expectedDay2 = 1;
		const Date::Month expectedMonth2 = Date::Month(1);
		const unsigned expectedYear2 = 1970;
		const Date::WeekDay expectedDayOfWeek2 = Date::WeekDay(4);
		Date date2{ expectedDay2, expectedMonth2, expectedYear2 };
		const unsigned expectedDay3 = 31;
		const Date::Month expectedMonth3 = Date::Month(12);
		const unsigned expectedYear3 = 9999;
		const Date::WeekDay expectedDayOfWeek3 = Date::WeekDay(5);
		Date date3{ expectedDay3, expectedMonth3, expectedYear3 };

		THEN("Getters are working correctly")
		{
			REQUIRE(date1.GetDay() == expectedDay1);
			REQUIRE(date1.GetMonth() == expectedMonth1);
			REQUIRE(date1.GetYear() == expectedYear1);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek1);

			REQUIRE(date2.GetDay() == expectedDay2);
			REQUIRE(date2.GetMonth() == expectedMonth2);
			REQUIRE(date2.GetYear() == expectedYear2);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek2);

			REQUIRE(date3.GetDay() == expectedDay3);
			REQUIRE(date3.GetMonth() == expectedMonth3);
			REQUIRE(date3.GetYear() == expectedYear3);
			REQUIRE(date3.GetWeekDay() == expectedDayOfWeek3);
		}
	}
}
