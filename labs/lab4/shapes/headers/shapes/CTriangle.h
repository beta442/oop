#pragma once

#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& firstVertex,
		const CPoint& secondVertex, const CPoint& thirdVertex,
		const uint32_t outlineColor, const uint32_t fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;
	
	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_v1, m_v2, m_v3;
};
