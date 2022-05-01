#include "../../../../catch2/catch.hpp"

#include "../../../../labs/lab4/shapes/headers/shapes/CLineSegment.h"

TEST_CASE("Testing line at created state")
{
	const CPoint basePoint{ 10.10, 20.20 };
	const uint32_t outlineColor = 16711680;
	const CPoint endPoint{ 0, 0 };
	const CLineSegment line{ basePoint, endPoint, outlineColor };

	WHEN("Line created")
	{
		THEN("Getters are working correctly")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == basePoint.Distance(endPoint));
			REQUIRE(line.GetOutlineColor() == outlineColor);
		}
	}
}
