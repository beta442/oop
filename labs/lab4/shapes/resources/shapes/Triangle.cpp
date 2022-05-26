#include "../../headers/shapes/Triangle.h"

Triangle::Triangle(const Point& firstVertex,
	const Point& secondVertex, const Point& thirdVertex,
	const Color& outlineColor, const Color& fillColor)
	: MyBase({ 0, 0 }, outlineColor, fillColor, s_type)
	, m_v1(firstVertex)
	, m_v2(secondVertex)
	, m_v3(thirdVertex)
{
}

inline double Triangle::GetArea() const
{
	double halfPerimeter = GetPerimeter() * 0.5;
	return std::sqrt(halfPerimeter * (halfPerimeter - m_v1.Distance(m_v2)) * (halfPerimeter - m_v2.Distance(m_v3)) * (halfPerimeter - m_v1.Distance(m_v3)));
}

inline double Triangle::GetPerimeter() const
{
	double a = m_v1.Distance(m_v2);
	double b = m_v2.Distance(m_v3);
	double c = m_v1.Distance(m_v3);

	return a + b + c;
}

inline double Triangle::CalculateArea() const
{
	return GetArea();
}

inline double Triangle::CalculatePerimeter() const
{
	return GetPerimeter();
}

inline Point Triangle::GetVertex1() const
{
	return m_v1;
}

inline Point Triangle::GetVertex2() const
{
	return m_v2;
}

inline Point Triangle::GetVertex3() const
{
	return m_v3;
}

inline std::string Triangle::ToStringAdditional() const
{
	return "Vertex1: " + m_v1.ToString()
		+ "Vertex2: " + m_v2.ToString()
		+ "Vertex3: " + m_v3.ToString();
}
