#include "../headers/CShapesContainer.h"

#include "../headers/shapes/CTriangle.h"
#include "../headers/shapes/CRectangle.h"
#include "../headers/shapes/CPoint.h"
#include "../headers/shapes/CLineSegment.h"
#include "../headers/shapes/CCircle.h"

bool CShapesContainer::ReadShape(std::istream& input)
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

		for (const auto& [_shapeTypeStr, _shapeType] : m_stringToShapeTypeMap)
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

bool CShapesContainer::ReadLineSegment(std::istream& input)
{
	double startX, startY, endX, endY;
	uint32_t outlineColor;

	if (input >> startX >> startY >> endX >> endY >> std::hex >> outlineColor)
	{
		m_shapes.push_back(std::shared_ptr<CLineSegment>(new CLineSegment{ CPoint{ startX, startY }, CPoint{ endX, endY }, outlineColor }));
		return true;
	}

	return false;
}

bool CShapesContainer::ReadTriangle(std::istream& input)
{
	double v1X, v1Y, v2X, v2Y, v3X, v3Y;
	uint32_t outlineColor, fillColor;

	if (input >> v1X >> v1Y >> v2X >> v2Y >> v3X >> v3Y >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.push_back(std::shared_ptr<CTriangle>(new CTriangle{ CPoint{ v1X, v2X }, CPoint{ v2X, v2Y }, CPoint{ v3X, v3Y }, outlineColor, fillColor }));
		return true;
	}

	return false;
}

bool CShapesContainer::ReadRectangle(std::istream& input)
{
	double leftTopX, leftTopY, width, height;
	uint32_t outlineColor, fillColor;

	if (input >> leftTopX >> leftTopY >> width >> height >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.push_back(std::shared_ptr<CRectangle>(new CRectangle{ CPoint{ leftTopX, leftTopY }, width, height, outlineColor, fillColor }));
		return true;
	}

	return false;
}

bool CShapesContainer::ReadCircle(std::istream& input)
{
	double centerX, centerY, radius;
	uint32_t outlineColor, fillColor;

	if (input >> centerX >> centerY >> radius >> std::hex >> outlineColor >> std::hex >> fillColor)
	{
		m_shapes.push_back(std::shared_ptr<CCircle>(new CCircle{ CPoint{ centerX, centerY }, radius, outlineColor, fillColor }));
		return true;
	}

	return false;
}

void CShapesContainer::PrintShapeInfoWithMaxArea(std::ostream& output) const
{
	if (auto shapePtr = FindMaxAreaShape())
	{
		output << shapePtr->ToString();
	}
	else
	{
		output << "Didn't find a shape with max area" << std::endl;
	}
}

void CShapesContainer::PrintShapeInfoWithMinPerimeter(std::ostream& output) const
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

std::shared_ptr<IShape> CShapesContainer::FindMaxAreaShape() const
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

std::shared_ptr<IShape> CShapesContainer::FindMinPerimeterShape() const
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
