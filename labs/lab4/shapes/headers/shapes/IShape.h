#pragma once

#include "../std_lib.h"
#include "CPoint.h"

class IShape
{
public:
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

protected:
	CPoint m_basePoint;
	uint32_t m_outlineColor;
};
