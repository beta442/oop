#include "../../headers/shapes/LineSegment.h"

LineSegment::LineSegment(const Point& start, const Point& end, const Color& outlineColor)
	: MyBase(start, outlineColor, s_type)
	, m_endPoint(end)
{
}

double LineSegment::GetArea() const
{
	return 0.0;
}

double LineSegment::GetPerimeter() const
{
	return GetBasePoint().Distance(m_endPoint);
}

std::string LineSegment::ToStringAdditional() const
{
	return "End point: " + m_endPoint.ToString() + '\n';
}

Point LineSegment::GetStartPoint() const
{
	return GetBasePoint();
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void LineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetBasePoint(), m_endPoint, GetOutlineColor());
}
