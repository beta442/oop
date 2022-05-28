#include <algorithm>
#include <optional>

#include "../headers/ShapesContainer.h"

#include "../headers/canvas/Canvas.h"

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

void ShapesContainer::ReadShapes(std::istream& input)
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
			throw std::domain_error("Wrong shape type at 1 argument");
		}

		switch (*shapeType)
		{
		case ShapeType::Line:
			if (!ReadLineSegment(iss))
			{
				throw std::domain_error("Failed to read line segment arguments");
			}
			break;

		case ShapeType::Triangle:
			if (!ReadTriangle(iss))
			{
				throw std::domain_error("Failed to read triangle arguments");
			}
			break;

		case ShapeType::Rectangle:
			if (!ReadRectangle(iss))
			{
				throw std::domain_error("Failed to read rectangle arguments");
			}
			break;

		case ShapeType::Circle:
			if (!ReadCircle(iss))
			{
				throw std::domain_error("Failed to read circle arguments");
			}
			break;

		default:
			throw std::domain_error("Failed to read arguments");
		}
	}
}

template <typename ShapeType, typename... Args>
decltype(auto) MakeShape(const Args&... args)
{
	return std::make_shared<ShapeType>(args...);
}

bool ShapesContainer::ReadLineSegment(std::istream& input)
{
	double startX, startY, endX, endY;
	Color outlineColor;

	if (input >> startX >> startY >> endX >> endY >> std::hex >> outlineColor)
	{
		m_shapes.emplace_back(MakeShape<LineSegment>(Point{ startX, startY }, Point{ endX, endY }, outlineColor));
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
		m_shapes.emplace_back(MakeShape<Triangle>(Point{ v1X, v2X }, Point{ v2X, v2Y }, Point{ v3X, v3Y }, outlineColor, fillColor));
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
		m_shapes.emplace_back(MakeShape<Rectangle>(Point{ leftTopX, leftTopY }, width, height, outlineColor, fillColor));
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
		m_shapes.emplace_back(MakeShape<Circle>(Point{ centerX, centerY }, radius, outlineColor, fillColor));
		return true;
	}

	return false;
}

template <typename T, typename Less>
std::optional<T> GetMax(const std::vector<T>& shapes, const Less& pred)
{
	const auto itBeg = std::begin(shapes), itEnd = std::end(shapes);
	if (const auto it = std::max_element(itBeg, itEnd, pred);
		it != itEnd)
	{
		return *it;
	}
	return std::nullopt;
}

void ShapesContainer::PrintCertainShapeInfo(std::ostream& output, ShapeCmpType pred) const
{
	if (auto oShapePtr = GetMax(m_shapes, pred);
		oShapePtr.has_value())
	{
		output << (*oShapePtr)->ToString();
	}
	else
	{
		output << "Didn't find a shape" << std::endl;
	}
}

void ShapesContainer::DrawShapes(const unsigned width, const unsigned height, const std::string& windowTitle) const
{
	const auto backgroundColor = sf::Color(255, 255, 255);
	Canvas canvas(width, height, windowTitle);
	while (canvas.GetRenderWindow().isOpen())
	{
		sf::Event event;
		while (canvas.GetRenderWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				canvas.GetRenderWindow().close();
			}
		}

		canvas.GetRenderWindow().clear(backgroundColor);

		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}

		canvas.GetRenderWindow().display();
	}
}
