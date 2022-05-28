#define _USE_MATH_DEFINES
#include <cmath>

#include "../../headers/shapes/Circle.h"

Circle::Circle(const Point& basePoint,
	const double radius, const Color& outlineColor, const Color& fillColor)
	: MyBase(basePoint, outlineColor, fillColor, s_type)
	, m_radius(radius)
{
}

inline double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

inline double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

inline Point Circle::GetCenter() const
{
	return GetBasePoint();
}

inline double Circle::GetRadius() const
{
	return m_radius;
}

inline std::string Circle::ToStringAdditional() const
{
	return "Radius: " + std::to_string(m_radius) + '\n';
}

inline void Circle::Draw(const ICanvas& canvas) const
{
}
