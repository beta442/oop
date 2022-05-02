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
	}

	WHEN("Timestamp is correct")
	{
		Date date1{ 0 };
		Date date2{ 2932896 };
		THEN("Date is in valid state")
		{
			REQUIRE(date1.IsValid());
			REQUIRE(date2.IsValid());
		}
	}

	WHEN("Timestamp is correct")
	{
		Date date1{ 0 };
		const unsigned expectedDay1 = 1;
		const Date::Month expectedMonth1 = Date::Month(1);
		const unsigned expectedYear1 = 1970;
		Date date2{ 2932896 };
		const unsigned expectedDay2 = 31;
		const Date::Month expectedMonth2 = Date::Month(12);
		const unsigned expectedYear2 = 9999;
		Date date3{ 1436428 };
		const unsigned expectedDay3 = 23;
		const Date::Month expectedMonth3 = Date::Month(10);
		const unsigned expectedYear3 = 5902;

		THEN("Getters are working correctly")
		{
			REQUIRE(date1.GetDay() == expectedDay1);
			REQUIRE(date1.GetMonth() == expectedMonth1);
			REQUIRE(date1.GetYear() == expectedYear1);

			REQUIRE(date2.GetDay() == expectedDay2);
			REQUIRE(date2.GetMonth() == expectedMonth2);
			REQUIRE(date2.GetYear() == expectedYear2);

			REQUIRE(date3.GetDay() == expectedDay3);
			REQUIRE(date3.GetMonth() == expectedMonth3);
			REQUIRE(date3.GetYear() == expectedYear3);
		}
	}
}
