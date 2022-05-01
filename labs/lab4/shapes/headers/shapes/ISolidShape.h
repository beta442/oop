#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;

protected:
	virtual ~ISolidShape() = default;

	uint32_t m_fillColor;
};
