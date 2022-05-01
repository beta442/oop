#include "headers/pch.h"

#include "headers/CShapesContainer.h"

int main()
{
	 CShapesContainer shapeContainer;

	if (!shapeContainer.ReadShape(std::cin))
	{
		std::cout << "Something went wrong. Exiting..." << std::endl;
		return 1;
	}

	std::cout << "Shape with max area info:" << std::endl;
	shapeContainer.PrintShapeInfoWithMaxArea(std::cout);
	std::cout << std::endl;
	std::cout << "Shape's with min perimeter info:" << std::endl;
	shapeContainer.PrintShapeInfoWithMinPerimeter(std::cout);

	return 0;
}
