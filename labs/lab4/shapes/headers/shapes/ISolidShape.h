#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	~ISolidShape() = default;

	virtual Color GetFillColor() const = 0;
};
