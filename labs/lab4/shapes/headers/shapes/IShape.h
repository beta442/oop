#pragma once

#include "../pch.h"
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
	IShape(const CPoint basePoint, const uint32_t outlineColor);

	CPoint m_basePoint;
	uint32_t m_outlineColor;
};
