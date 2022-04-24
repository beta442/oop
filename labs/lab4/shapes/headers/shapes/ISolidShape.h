#pragma once

#include "IShape.h"
#include "CPoint.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
