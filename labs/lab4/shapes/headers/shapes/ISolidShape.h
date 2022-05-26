#pragma once

#include "IShape.h"
#include "Point.h"

class ISolidShape : public IShape
{
public:
	~ISolidShape() = default;

	virtual Color GetFillColor() const = 0;
};
