#include "../../headers/shapes/CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor)
	: IShape(start, outlineColor)
	, m_endPoint(end)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return m_basePoint.Distance(m_endPoint);
}

std::string CLineSegment::ToString() const
{
	std::ostringstream oss;

	oss << std::hex;
	oss << "Line segment" << std::endl
		<< "--start point: " << m_basePoint.ToString()
		<< "--end point: " << m_endPoint.ToString()
		<< "--length: " << GetPerimeter() << std::endl
		<< "--outline color: " << m_outlineColor << std::endl;

	return oss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint()
{
	return m_basePoint;
}

CPoint CLineSegment::GetEndPoint()
{
	return m_endPoint;
}
