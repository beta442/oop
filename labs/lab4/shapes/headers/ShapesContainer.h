#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "shapes/IShape.h"

class ShapesContainer
{
public:
	enum class ShapeType
	{
		Line,
		Triangle,
		Circle,
		Rectangle,
	};

	bool ReadShape(std::istream& input);

	void PrintShapeInfoWithMaxArea(std::ostream& output) const;
	void PrintShapeInfoWithMinPerimeter(std::ostream& output) const;

private:
	bool ReadLineSegment(std::istream& input);
	bool ReadTriangle(std::istream& input);
	bool ReadRectangle(std::istream& input);
	bool ReadCircle(std::istream& input);

	std::shared_ptr<IShape> FindMaxAreaShape() const;
	std::shared_ptr<IShape> FindMinPerimeterShape() const;

	std::vector<std::shared_ptr<IShape>> m_shapes;
};
