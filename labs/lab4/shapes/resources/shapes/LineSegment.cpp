#include "../../headers/shapes/LineSegment.h"

LineSegment::LineSegment(const Point& start, const Point& end, const Color& outlineColor)
	: MyBase(start, outlineColor, s_type)
	, m_endPoint(end)
{
}

inline double LineSegment::GetArea() const
{
	return 0.0;
}

inline double LineSegment::GetPerimeter() const
{
	return GetBasePoint().Distance(m_endPoint);
}

inline double LineSegment::CalculateArea() const
{
	return GetArea();
}

inline double LineSegment::CalculatePerimeter() const
{
	return GetPerimeter();
}

inline std::string LineSegment::ToStringAdditional() const
{
	return "End point: " + m_endPoint.ToString() + '\n';
}

inline Point LineSegment::GetStartPoint() const
{
	return GetBasePoint();
}

inline Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}
