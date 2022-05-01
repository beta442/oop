#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;

protected:
	ISolidShape(const CPoint basePoint,
		const uint32_t outlineColor, const uint32_t fillColor);

	virtual ~ISolidShape() = default;

	uint32_t m_fillColor;
};
