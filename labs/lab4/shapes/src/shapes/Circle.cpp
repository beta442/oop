#define _USE_MATH_DEFINES
#include <cmath>

#include "../../headers/shapes/Circle.h"

Circle::Circle(const Point& basePoint,
	const double radius, const Color& outlineColor, const Color& fillColor)
	: MyBase(basePoint, outlineColor, fillColor, s_type)
	, m_radius(radius)
{
}

double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

Point Circle::GetCenter() const
{
	return GetBasePoint();
}

double Circle::GetRadius() const
{
	return m_radius;
}

std::string Circle::ToStringAdditional() const
{
	return "Radius: " + std::to_string(m_radius) + '\n';
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(GetBasePoint(), m_radius, GetOutlineColor());
	canvas.FillCircle(GetBasePoint(), m_radius, GetFillColor());
}
