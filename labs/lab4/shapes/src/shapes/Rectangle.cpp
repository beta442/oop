#include "../../headers/shapes/Rectangle.h"

Rectangle::Rectangle(const Point& basePoint,
	const double width, const double height, const Color& outlineColor, const Color& fillColor)
	: MyBase(basePoint, outlineColor, fillColor, s_type)
	, m_width(width)
	, m_height(height)
{
}

double Rectangle::GetArea() const
{
	return m_width * m_height;
}

double Rectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

Point Rectangle::GetLeftTop() const
{
	return GetBasePoint();
}

Point Rectangle::GetRightBottom() const
{
	const auto basePoint = GetBasePoint();
	return Point{ basePoint.x + m_width, basePoint.y + m_height };
}

double Rectangle::GetWidth() const
{
	return m_width;
}

double Rectangle::GetHeight() const
{
	return m_height;
}

std::string Rectangle::ToStringAdditional() const
{
	return "Right bottom: " + GetRightBottom().ToString()
		+ "Width: " + std::to_string(GetWidth()) + '\n'
		+ "Height: " + std::to_string(GetHeight()) + '\n';
}

inline void Rectangle::Draw(ICanvas& canvas) const
{
	const Point rightTop = { GetBasePoint().x + m_width, GetBasePoint().y },
				leftBottom = { GetRightBottom().x - m_width, GetRightBottom().y };

	canvas.DrawLine(GetBasePoint(), rightTop, GetOutlineColor());
	canvas.DrawLine(rightTop, GetRightBottom(), GetOutlineColor());
	canvas.DrawLine(GetRightBottom(), leftBottom, GetOutlineColor());
	canvas.DrawLine(leftBottom, GetBasePoint(), GetOutlineColor());
	canvas.FillPolygon({ GetBasePoint(), rightTop, GetRightBottom(), leftBottom }, GetFillColor());
}
