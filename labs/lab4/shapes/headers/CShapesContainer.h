#pragma once

#include "pch.h"

#include "shapes/IShape.h"

class CShapesContainer
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
	inline static const std::map<std::string, ShapeType> m_stringToShapeTypeMap = {
		{ "line", ShapeType::Line },
		{ "triangle", ShapeType::Triangle },
		{ "circle", ShapeType::Circle },
		{ "rectangle", ShapeType::Rectangle },
	};
};
