#include <optional>

#include "../headers/ShapesContainer.h"

#include "../headers/shapes/Circle.h"
#include "../headers/shapes/LineSegment.h"
#include "../headers/shapes/Point.h"
#include "../headers/shapes/Rectangle.h"
#include "../headers/shapes/Triangle.h"

using ShapeType = ShapesContainer::ShapeType;

inline static const std::map<std::string, ShapeType> STRING_TO_SHAPE_MAP = {
	{ "line", ShapeType::Line },
	{ "triangle", ShapeType::Triangle },
	{ "circle", ShapeType::Circle },
	{ "rectangle", ShapeType::Rectangle },
};

bool ShapesContainer::ReadShape(std::istream& input)
{
	std::string inputStr, shapeTypeStr;
	std::stringstream iss;
	std::optional<ShapeType> shapeType;

	while (std::getline(input, inputStr))
	{
		iss.clear();
		iss << inputStr;
		iss >> shapeTypeStr;
		shapeType.reset();

		for (const auto& [_shapeTypeStr, _shapeType] : STRING_TO_SHAPE_MAP)
		{
			if (shapeTypeStr == _shapeTypeStr)
			{
				shapeType = _shapeType;
				break;
			}
		}

		if (!shapeType.has_value())
		{
			return false;
		}

		switch (*shapeType)
		{
		case ShapeType::Line:
			if (!ReadLineSegment(iss))
			{
				return false;
			}
			break;

		case ShapeType::Triangle:
			if (!ReadTriangle(iss))
			{
				return false;
			}
			break;

		case ShapeType::Rectangle:
			if (!ReadRectangle(iss))
			{
				return false;
			}
			break;

		case ShapeType::Circle:
			if (!ReadCircle(iss))
			{
				return false;
			}
			break;

		default:
			return false;
		}
	}

	return true;
}

using Color = IShape::Color;

bool ShapesContainer::ReadLineSegment(std::istream& input)
{
	double startX, startY, endX, endY;
	Color outlineColor;

	if (input >> startX >> startY >> endX >> endY >> std::hex >> outlineColor)
	{
		m_shapes.emplace_back(std::make_shared<LineSegment>(Point{ startX, startY }, Point{ endX, endY }, outlineColor));
		return true;
	}

	return false;
}

bool ShapesContainer::ReadTriangle(std::istream& input)
{
	double v1X, v1Y, v2X, v2Y, v3X, v3Y;
	Color outlineColor, fillColor;

	if (input >> v1X >> v1Y >> v2X >> v2Y >> v3X >> v3Y >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.emplace_back(std::make_shared<Triangle>(Point{ v1X, v2X }, Point{ v2X, v2Y }, Point{ v3X, v3Y }, outlineColor, fillColor));
		return true;
	}

	return false;
}

bool ShapesContainer::ReadRectangle(std::istream& input)
{
	double leftTopX, leftTopY, width, height;
	Color outlineColor, fillColor;

	if (input >> leftTopX >> leftTopY >> width >> height >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.emplace_back(std::make_shared<Rectangle>(Point{ leftTopX, leftTopY }, width, height, outlineColor, fillColor));
		return true;
	}

	return false;
}

bool ShapesContainer::ReadCircle(std::istream& input)
{
	double centerX, centerY, radius;
	Color outlineColor, fillColor;

	if (input >> centerX >> centerY >> radius >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.emplace_back(std::make_shared<Circle>(Point{ centerX, centerY }, radius, outlineColor, fillColor));
		return true;
	}

	return false;
}

void ShapesContainer::PrintShapeInfoWithMaxArea(std::ostream& output) const
{
	if (auto shapePtr = FindMaxAreaShape())
	{
		// std::() найти подходящий алгоритм для поиска мин/макс элементов
		output << shapePtr->ToString();
	}
	else
	{
		output << "Didn't find a shape with max area" << std::endl;
	}
}

void ShapesContainer::PrintShapeInfoWithMinPerimeter(std::ostream& output) const
{
	if (auto shapePtr = FindMinPerimeterShape())
	{
		output << shapePtr->ToString();
	}
	else
	{
		output << "Didn't find a shape with min perimeter" << std::endl;
	}
}

std::shared_ptr<IShape> ShapesContainer::FindMaxAreaShape() const
{
	if (m_shapes.empty())
	{
		return {};
	}

	std::shared_ptr<IShape> result = m_shapes[0];
	double maxArea = m_shapes[0]->GetArea();
	double temp;
	for (auto it = std::begin(m_shapes), end = std::end(m_shapes); it != end; ++it)
	{
		if ((temp = (*it)->GetArea()) > maxArea)
		{
			maxArea = temp;
			result = *it;
		}
	}
	return result;
}

std::shared_ptr<IShape> ShapesContainer::FindMinPerimeterShape() const
{
	if (m_shapes.empty())
	{
		return {};
	}

	std::shared_ptr<IShape> result = m_shapes[0];
	double minPerimeter = m_shapes[0]->GetPerimeter();
	double temp;
	for (auto it = std::begin(m_shapes), end = std::end(m_shapes); it != end; ++it)
	{
		if ((temp = (*it)->GetPerimeter()) < minPerimeter)
		{
			minPerimeter = temp;
			result = *it;
		}
	}

	return result;
}

template <typename Pred>
std::optional<std::shared_ptr<IShape>> GetShapeWith(const std::vector<std::shared_ptr<IShape>>& shapes, const Pred& pred)
{
}
