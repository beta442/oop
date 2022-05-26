#include "../pch.h"

#include "../../../../labs/lab4/shapes/headers/shapes/Point.h"

TEST_CASE("Point workflow")
{
	const Point p1{ 1, 0 }, p2{ 4, 0 }, p3{ -16, 0 };

	WHEN("Trying to recieve distance between two points")
	{
		THEN("Distance() gives result")
		{
			REQUIRE(p1.Distance(p1) == 0);
			REQUIRE(p2.Distance(p2) == 0);
			REQUIRE(p1.Distance(p2) == 3);
			REQUIRE(p2.Distance(p1) == 3);
			REQUIRE(p2.Distance(p3) == 20);
			REQUIRE(p3.Distance(p2) == 20);
		}
	}
}