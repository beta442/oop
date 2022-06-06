#pragma once

#include "ISolidShape.h"

class IRectangle : public ISolidShape
{
public:
	virtual Point GetLeftTop() const = 0;
	virtual Point GetRightBottom() const = 0;
	virtual double GetWidth() const = 0;
	virtual double GetHeight() const = 0;

protected:
	~IRectangle() = default;
};
