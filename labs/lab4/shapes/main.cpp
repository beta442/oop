#include "headers/pch.h"

#include "headers/shapes/CRectangle.h"

int main()
{
	const CPoint basePoint{ 10.10, 20.20 };
	const double width = 100, height = 50;
	const uint32_t outlineColor = 16711680, fillColor = 65280;
	const CRectangle rect{ basePoint, width, height, outlineColor, fillColor };

	std::cout << rect.ToString() << std::endl;

	return 0;
}
