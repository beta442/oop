#pragma once

#include "ISolidShape.h"

class ICircle : public ISolidShape
{
public:
	~ICircle() = default;

	virtual Point GetCenter() const = 0;
	virtual double GetRadius() const = 0;
};
