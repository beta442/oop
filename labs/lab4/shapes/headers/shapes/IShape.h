#pragma once

#include "Point.h"

class IShape
{
public:
	using Color = uint32_t;

public:
	~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual Color GetOutlineColor() const = 0;
	virtual Point GetBasePoint() const = 0;
};
