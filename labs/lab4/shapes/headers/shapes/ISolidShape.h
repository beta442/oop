#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;

protected:
	//todo: remove
	ISolidShape(const CPoint basePoint,
		const uint32_t outlineColor, const uint32_t fillColor);

	uint32_t m_fillColor;
};
