#pragma once

#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& basePoint,
		const double radius, const uint32_t outlineColor, const uint32_t fillColor);

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
