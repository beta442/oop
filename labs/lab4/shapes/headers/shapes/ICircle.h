#pragma once

#include "ISolidShape.h"

class ICircle : public ISolidShape
{
public:
	virtual Point GetCenter() const = 0;
	virtual double GetRadius() const = 0;

protected:
	~ICircle() = default;
};
