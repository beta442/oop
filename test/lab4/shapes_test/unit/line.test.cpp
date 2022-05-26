#include "../../../../catch2/catch.hpp"

#include "../../../../labs/lab4/shapes/headers/shapes/LineSegment.h"

TEST_CASE("Testing line at created state")
{
	const Point basePoint{ 10.10, 20.20 };
	const uint32_t outlineColor = 16711680;
	const Point endPoint{ 0, 0 };
	const LineSegment line{ basePoint, endPoint, outlineColor };

	WHEN("Line created")
	{
		THEN("Getters are working correctly")
		{
			REQUIRE(line.GetBasePoint() == basePoint);
			REQUIRE(line.GetEndPoint() == endPoint);
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == basePoint.Distance(endPoint));
			REQUIRE(line.GetOutlineColor() == outlineColor);
		}
	}
}
