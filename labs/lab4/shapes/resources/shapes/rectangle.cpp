#include "../../headers/shapes/CRectangle.h"

CRectangle::CRectangle(CPoint basePoint,
	double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_width(width)
	, m_height(height)
{
	m_basePoint = basePoint;
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

std::string CRectangle::ToString() const
{
	std::stringstream ss;
	ss << "Width: " << GetWidth() << std::endl
	   << "Height: " << GetHeight() << std::endl;
	return ss.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_basePoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint{m_basePoint.x + m_width, m_basePoint.y + m_height};
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
