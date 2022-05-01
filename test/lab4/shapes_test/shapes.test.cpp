#define _USE_MATH_DEFINES
#include <cmath>

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../labs/lab4/shapes/headers/shapes/CRectangle.h"

TEST_CASE("Rectangle at creation state")
{
	const CPoint basePoint{ 10.10, 20.20 };
	const double width = 100, height = 50;
	const CPoint rightBottomPoint{ basePoint.x + width, basePoint.y + height };
	const uint32_t outlineColor = 16711680, fillColor = 65280;
	const CRectangle rect{ basePoint, width, height, outlineColor, fillColor };

	WHEN("Rectangle created")
	{
		THEN("Getters works correctly")
		{
			REQUIRE(rect.GetWidth() == width);
			REQUIRE(rect.GetHeight() == height);
			REQUIRE(rect.GetArea() == width * height);
			REQUIRE(rect.GetPerimeter() == (width + height) * 2);
			REQUIRE(rect.GetFillColor() == fillColor);
			REQUIRE(rect.GetOutlineColor() == outlineColor);
			REQUIRE(rect.GetLeftTop() == basePoint);
			REQUIRE(rect.GetRightBottom() == rightBottomPoint);
		}
	}
}

#include "../../../labs/lab4/shapes/headers/shapes/CCircle.h"

TEST_CASE("Circle at creation state")
{
	const CPoint basePoint{ 10.10, 20.20 };
	const double radius = 100;
	const uint32_t outlineColor = 16711680, fillColor = 65280;
	const CCircle circle{ basePoint, radius, outlineColor, fillColor };

	WHEN("Circle created")
	{
		THEN("Getters are working correctly")
		{
			REQUIRE(circle.GetRadius() == radius);
			REQUIRE(circle.GetCenter() == basePoint);
			REQUIRE(circle.GetArea() == M_PI * radius * radius);
			REQUIRE(circle.GetPerimeter() == 2 * M_PI * radius);
			REQUIRE(circle.GetFillColor() == fillColor);
			REQUIRE(circle.GetOutlineColor() == outlineColor);
		}
	}
}
