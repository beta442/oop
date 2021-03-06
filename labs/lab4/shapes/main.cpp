#include "headers/pch.h"

#include "headers/ShapesContainer.h"

int main()
{
	ShapesContainer shapeContainer;

	try
	{
		shapeContainer.ReadShapes(std::cin);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	std::cout << "Shape with max area info:" << std::endl;
	shapeContainer.PrintCertainShapeInfo(std::cout, ShapesContainer::s_maxAreaShapePred);
	std::cout << std::endl;
	std::cout << "Shape's with min perimeter info:" << std::endl;
	shapeContainer.PrintCertainShapeInfo(std::cout, ShapesContainer::s_minPerimeterShapePred);

	shapeContainer.DrawShapes(1280, 720, "Shapes");

	return 0;
}
