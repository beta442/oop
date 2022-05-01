#define _USE_MATH_DEFINES
#include <cmath>

#include "../../headers/shapes/CCircle.h"

CCircle::CCircle(CPoint basePoint,
	double radius, uint32_t outlineColor, uint32_t fillColor)
	: ISolidShape(basePoint, outlineColor, fillColor)
	, m_radius(radius)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream oss;

	oss << std::hex;
	oss << "Circle:" << std::endl
		<< "--center: " << m_basePoint.ToString()
		<< "--radius: " << m_radius << std::endl
		<< "--area: " << GetArea() << std::endl
		<< "--perimeter: " << GetPerimeter() << std::endl
		<< "--outline color: " << m_outlineColor << std::endl
		<< "--fill color: " << m_fillColor << std::endl;

	return oss.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}


CPoint CCircle::GetCenter() const
{
	return m_basePoint;
}

double CCircle::GetRadius()
{
	return m_radius;
}
