#include "../../headers/shapes/CTriangle.h"

CTriangle::CTriangle(const CPoint& firstVertex,
	const CPoint& secondVertex, const CPoint& thirdVertex,
	const uint32_t outlineColor, const uint32_t fillColor)
	: ISolidShape({ 0, 0 }, outlineColor, fillColor)
	, m_v1(firstVertex)
	, m_v2(secondVertex)
	, m_v3(thirdVertex)
{
}

double CTriangle::GetArea() const
{
	double halfPerimeter = GetPerimeter() * 0.5;
	return std::sqrt(halfPerimeter *
		(halfPerimeter - m_v1.Distance(m_v2)) *
		(halfPerimeter - m_v2.Distance(m_v3)) *
		(halfPerimeter - m_v1.Distance(m_v3)));
}

double CTriangle::GetPerimeter() const
{
	double a = m_v1.Distance(m_v2);
	double b = m_v2.Distance(m_v3);
	double c = m_v1.Distance(m_v3);

	return a + b + c;
}

std::string CTriangle::ToString() const
{
	std::ostringstream oss;

	oss << std::hex;
	oss << "Triangle" << std::endl
		<< "--vertex 1: " << m_v1.ToString()
		<< "--vertex 2: " << m_v2.ToString()
		<< "--vertex 3: " << m_v3.ToString()
		<< "--area: " << GetArea() << std::endl
		<< "--perimeter: " << GetPerimeter() << std::endl
		<< "--outline color: " << m_outlineColor << std::endl
		<< "--fill color: " << m_fillColor << std::endl;

	return oss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_v1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_v2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_v3;
}
