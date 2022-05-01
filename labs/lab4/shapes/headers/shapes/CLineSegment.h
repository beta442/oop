#pragma once

#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	CPoint m_endPoint;
};
