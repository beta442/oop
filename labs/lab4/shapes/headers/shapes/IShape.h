#pragma once

#include "Types.h"

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual Color GetOutlineColor() const = 0;
	virtual Point GetBasePoint() const = 0;

protected:
	~IShape() = default;
};
