#include "../pch.h"

#include "../../../../labs/lab4/shapes/headers/shapes/Rectangle.h"

TEST_CASE("Rectangle at creation state")
{
	const Point basePoint{ 10.10, 20.20 };
	const double width = 100, height = 50;
	const Point rightBottomPoint{ basePoint.x + width, basePoint.y + height };
	const uint32_t outlineColor = 16711680, fillColor = 65280;
	const Rectangle rect{ basePoint, width, height, outlineColor, fillColor };

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
