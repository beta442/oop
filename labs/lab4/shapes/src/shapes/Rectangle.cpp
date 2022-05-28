#include "../../headers/shapes/Rectangle.h"

Rectangle::Rectangle(const Point& basePoint,
	const double width, const double height, const Color& outlineColor, const Color& fillColor)
	: MyBase(basePoint, outlineColor, fillColor, s_type)
	, m_width(width)
	, m_height(height)
{
}

inline double Rectangle::GetArea() const
{
	return m_width * m_height;
}

inline double Rectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

inline Point Rectangle::GetLeftTop() const
{
	return GetBasePoint();
}

inline Point Rectangle::GetRightBottom() const
{
	const auto basePoint = GetBasePoint();
	return Point{ basePoint.x + m_width, basePoint.y + m_height };
}

inline double Rectangle::GetWidth() const
{
	return m_width;
}

inline double Rectangle::GetHeight() const
{
	return m_height;
}

inline std::string Rectangle::ToStringAdditional() const
{
	return "Right bottom: " + GetRightBottom().ToString()
		+ "Width: " + std::to_string(GetWidth()) + '\n'
		+ "Height: " + std::to_string(GetHeight()) + '\n';
}

inline void Rectangle::Draw(const ICanvas& canvas) const
{
}
