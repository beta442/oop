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
			REQUIRE(date.GetWeekDay() == Date::WeekDay(4));
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
		Date date4{ 787 };
		const unsigned expectedDay4 = 27;
		const Date::Month expectedMonth4 = Date::Month(2);
		const unsigned expectedYear4 = 1972;
		const Date::WeekDay expectedDayOfWeek4 = Date::WeekDay(0);
		Date date5{ 789 };
		const unsigned expectedDay5 = 29;
		const Date::Month expectedMonth5 = Date::Month(2);
		const unsigned expectedYear5 = 1972;
		const Date::WeekDay expectedDayOfWeek5 = Date::WeekDay(2);

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

			REQUIRE(date4.GetDay() == expectedDay4);
			REQUIRE(date4.GetMonth() == expectedMonth4);
			REQUIRE(date4.GetYear() == expectedYear4);
			REQUIRE(date4.GetWeekDay() == expectedDayOfWeek4);

			REQUIRE(date5.GetDay() == expectedDay5);
			REQUIRE(date5.GetMonth() == expectedMonth5);
			REQUIRE(date5.GetYear() == expectedYear5);
			REQUIRE(date5.GetWeekDay() == expectedDayOfWeek5);
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
			const unsigned expectedDay = 1;
			const Date::Month expectedMonth = Date::Month(1);
			const unsigned expectedYear = 1970;
			const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);
			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
			REQUIRE(date3.GetDay() == expectedDay);
			REQUIRE(date3.GetMonth() == expectedMonth);
			REQUIRE(date3.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date3.GetYear() == expectedYear);
			REQUIRE(date10.GetDay() == expectedDay);
			REQUIRE(date10.GetMonth() == expectedMonth);
			REQUIRE(date10.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date10.GetYear() == expectedYear);
			REQUIRE(date15.GetDay() == expectedDay);
			REQUIRE(date15.GetMonth() == expectedMonth);
			REQUIRE(date15.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date15.GetYear() == expectedYear);
			REQUIRE(date17.GetDay() == expectedDay);
			REQUIRE(date17.GetMonth() == expectedMonth);
			REQUIRE(date17.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date17.GetYear() == expectedYear);
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
		const unsigned expectedDay4 = 27;
		const Date::Month expectedMonth4 = Date::Month(2);
		const unsigned expectedYear4 = 1972;
		const Date::WeekDay expectedDayOfWeek4 = Date::WeekDay(0);
		Date date4{ expectedDay4, expectedMonth4, expectedYear4 };
		const unsigned expectedDay5 = 29;
		const Date::Month expectedMonth5 = Date::Month(2);
		const unsigned expectedYear5 = 1972;
		const Date::WeekDay expectedDayOfWeek5 = Date::WeekDay(2);
		Date date5{ expectedDay5, expectedMonth5, expectedYear5 };

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

			REQUIRE(date4.GetDay() == expectedDay4);
			REQUIRE(date4.GetMonth() == expectedMonth4);
			REQUIRE(date4.GetYear() == expectedYear4);
			REQUIRE(date4.GetWeekDay() == expectedDayOfWeek4);

			REQUIRE(date5.GetDay() == expectedDay5);
			REQUIRE(date5.GetMonth() == expectedMonth5);
			REQUIRE(date5.GetYear() == expectedYear5);
			REQUIRE(date5.GetWeekDay() == expectedDayOfWeek5);
		}
	}
}

TEST_CASE("Date operator++. Date in correct state")
{
	Date date1{ 0 };
	Date date2{ 1, Date::Month(1), 1970 };

	WHEN("operator++ used")
	{
		const unsigned expectedDay = 18;
		const Date::Month expectedMonth = Date::Month(5);
		const unsigned expectedYear = 1997;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(0);

		for (size_t i = 0; i < 9999; ++i)
		{
			++date1;
			date2++;
		}

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	WHEN("operator++ used until 29th of Feb in leap year")
	{
		const unsigned expectedDay = 29;
		const Date::Month expectedMonth = Date::Month(2);
		const unsigned expectedYear = 1980;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(5);

		for (size_t i = 0; i < 3711; ++i)
		{
			++date1;
			date2++;
		}

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	Date date3{ 2932896 };
	Date date4{ 31, Date::Month(12), 9999 };

	WHEN("operator++ used && date in upperBound state")
	{
		++date3;
		date4++;

		THEN("Date state turns to invalid")
		{
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
		}
	}
}

TEST_CASE("Date operator++. Date in incorrect state")
{
	Date date1{ 2932900 };
	Date date2{ 101, Date::Month(1), 1970 };

	WHEN("operator++ used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		++date1;
		date2++;

		THEN("Getters shows default info")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}
}

TEST_CASE("Date operator--. Date in correct state")
{
	Date date1{ 794 };
	Date date2{ 5, Date::Month(3), 1972 };

	WHEN("operator-- used")
	{
		const unsigned expectedDay = 26;
		const Date::Month expectedMonth = Date::Month(11);
		const unsigned expectedYear = 1971;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(5);

		for (size_t i = 0; i < 100; ++i)
		{
			--date1;
			date2--;
		}

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	WHEN("operator-- used until 29th of Feb in leap year")
	{
		const unsigned expectedDay = 29;
		const Date::Month expectedMonth = Date::Month(2);
		const unsigned expectedYear = 1972;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(2);

		for (size_t i = 0; i < 5; ++i)
		{
			--date1;
			date2--;
		}

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	Date date3{ 0 };
	Date date4{ 1, Date::Month(1), 1970 };

	WHEN("operator-- used && date in lowerBound state")
	{
		--date3;
		date4--;

		THEN("Date state turns to invalid")
		{
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
		}
	}
}

TEST_CASE("Date operator--. Date in incorrect state")
{
	Date date1{ 2932900 };
	Date date2{ 101, Date::Month(1), 1970 };

	WHEN("operator-- used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		--date1;
		date2--;

		THEN("Getters shows default info")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}
}

TEST_CASE("Date operator+. Date in correct state")
{
	Date date1{ 0 };
	Date date2{ 1, Date::Month(1), 1970 };

	WHEN("operator+ used")
	{
		const unsigned expectedDay = 19;
		const Date::Month expectedMonth = Date::Month(6);
		const unsigned expectedYear = 1972;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(1);

		date1 = date1 + 900;
		date2 = 900 + date2;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	WHEN("operator+ used until 29th of Feb in leap year")
	{
		const unsigned expectedDay = 29;
		const Date::Month expectedMonth = Date::Month(2);
		const unsigned expectedYear = 1972;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(2);

		date1 = date1 + 789;
		date2 = 789 + date2;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	Date date3{ 2932896 };
	Date date4{ 31, Date::Month(12), 9999 };

	WHEN("operator+ used && date in upperBound state")
	{
		date3 = date3 + 1;
		date4 = 1 + date4;

		THEN("Date state turns to invalid")
		{
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
		}
	}
}

TEST_CASE("Date operator+. Date in incorrect state")
{
	Date date1{ 2932900 };
	Date date2{ 101, Date::Month(1), 1970 };

	WHEN("operator+ used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 = date1 + 9999;
		date2 = 9999 + date2;

		THEN("Getters shows default info")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}
}

TEST_CASE("Date operator-. Date in correct state")
{
	Date date1{ 2931498 };
	Date date2{ 3, Date::Month(3), 9996 };

	WHEN("operator- used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 = date1 - 2931498;
		date2 = date2 - 2931498;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	WHEN("operator- used until 29th of Feb in leap year")
	{
		const unsigned expectedDay = 29;
		const Date::Month expectedMonth = Date::Month(2);
		const unsigned expectedYear = 9996;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 = date1 - 3;
		date2 = date2 - 3;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	Date date3{ 0 };
	Date date4{ 1, Date::Month(1), 1970 };

	WHEN("operator- used && date in lowerBound state")
	{
		date3 = date3 - 1;
		date4 = date4 - 1;

		THEN("Date state turns to invalid")
		{
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
		}
	}

	WHEN("operator- used as distance between two dates in valid state")
	{
		THEN("It works correctly")
		{
			REQUIRE((date1 - date3) == 2931498);
			REQUIRE((date3 - date1) == -2931498);
			REQUIRE((date2 - date4) == 2931498);
			REQUIRE((date4 - date2) == -2931498);
		}
	}
}

TEST_CASE("Date operator-. Date in incorrect state")
{
	Date date1{ 2932900 };
	Date date2{ 101, Date::Month(1), 1970 };

	WHEN("operator- used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 = date1 - 900;
		date2 = date2 - 900;

		THEN("Getters shows default info")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}
}

TEST_CASE("Date operator+=. Date in correct state")
{
	Date date1{ 0 };
	Date date2{ 1, Date::Month(1), 1970 };

	WHEN("operator+= used")
	{
		const unsigned expectedDay = 19;
		const Date::Month expectedMonth = Date::Month(6);
		const unsigned expectedYear = 1972;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(1);

		date1 += 900;
		date2 += 900;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	WHEN("operator+= used until 29th of Feb in leap year")
	{
		const unsigned expectedDay = 29;
		const Date::Month expectedMonth = Date::Month(2);
		const unsigned expectedYear = 1972;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(2);

		date1 += 789;
		date2 += 789;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	Date date3{ 2932896 };
	Date date4{ 31, Date::Month(12), 9999 };

	WHEN("operator+= used && date in upperBound state")
	{
		date3 += 1;
		date4 += 1;

		THEN("Date state turns to invalid")
		{
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
		}
	}
}

TEST_CASE("Date operator+=. Date in incorrect state")
{
	Date date1{ 2932900 };
	Date date2{ 101, Date::Month(1), 1970 };

	WHEN("operator+= used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 += 9999;
		date2 += 9999;

		THEN("Getters shows default info")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}
}

TEST_CASE("Date operator-=. Date in correct state")
{
	Date date1{ 2931498 };
	Date date2{ 3, Date::Month(3), 9996 };

	WHEN("operator-= used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 -= 2931498;
		date2 -= 2931498;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	WHEN("operator-= used until 29th of Feb in leap year")
	{
		const unsigned expectedDay = 29;
		const Date::Month expectedMonth = Date::Month(2);
		const unsigned expectedYear = 9996;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 -= 3;
		date2 -= 3;

		THEN("Date is correct")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}

	Date date3{ 0 };
	Date date4{ 1, Date::Month(1), 1970 };

	WHEN("operator-= used && date in lowerBound state")
	{
		date3 -= 1;
		date4 -= 1;

		THEN("Date state turns to invalid")
		{
			REQUIRE_FALSE(date3.IsValid());
			REQUIRE_FALSE(date4.IsValid());
		}
	}

	WHEN("operator-= used as distance between two dates in valid state")
	{
		THEN("It works correctly")
		{
			REQUIRE((date1 - date3) == 2931498);
			REQUIRE((date3 - date1) == -2931498);
			REQUIRE((date2 - date4) == 2931498);
			REQUIRE((date4 - date2) == -2931498);
		}
	}
}

TEST_CASE("Date operator-=. Date in incorrect state")
{
	Date date1{ 2932900 };
	Date date2{ 101, Date::Month(1), 1970 };

	WHEN("operator-= used")
	{
		const unsigned expectedDay = 1;
		const Date::Month expectedMonth = Date::Month(1);
		const unsigned expectedYear = 1970;
		const Date::WeekDay expectedDayOfWeek = Date::WeekDay(4);

		date1 -= 900;
		date2 -= 900;

		THEN("Getters shows default info")
		{
			REQUIRE_FALSE(date1.IsValid());
			REQUIRE_FALSE(date2.IsValid());

			REQUIRE(date1.GetDay() == expectedDay);
			REQUIRE(date1.GetMonth() == expectedMonth);
			REQUIRE(date1.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date1.GetYear() == expectedYear);

			REQUIRE(date2.GetDay() == expectedDay);
			REQUIRE(date2.GetMonth() == expectedMonth);
			REQUIRE(date2.GetWeekDay() == expectedDayOfWeek);
			REQUIRE(date2.GetYear() == expectedYear);
		}
	}
}
