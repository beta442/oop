#include "../../../../catch2/catch.hpp"

#include "../../../../labs/lab4/shapes/headers/shapes/CTriangle.h"

TEST_CASE("Triangle at creation state")
{
	const CPoint v1{ 0, 0 }, v2{ 5, 5 }, v3{ 0, 7 };
	const uint32_t outlineColor = 16711680, fillColor = 65280;
	const CTriangle triangle{ v1, v2, v3, outlineColor, fillColor };

	WHEN("Triangle created")
	{
		THEN("Getters are working correctly")
		{
			//todo: perimeter and area check
			REQUIRE(triangle.GetFillColor() == fillColor);
			REQUIRE(triangle.GetOutlineColor() == outlineColor);
			REQUIRE(triangle.GetVertex1() == v1);
			REQUIRE(triangle.GetVertex2() == v2);
			REQUIRE(triangle.GetVertex3() == v3);
		}
	}
}
