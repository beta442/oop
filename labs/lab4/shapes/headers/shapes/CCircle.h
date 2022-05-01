#pragma once

#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint basePoint,
		double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	double m_radius;
};
