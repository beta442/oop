#pragma once

#include "ISolidShape.h"

class IRectangle : public ISolidShape
{
public:
	~IRectangle() = default;

	inline virtual Point GetLeftTop() const = 0;
	inline virtual Point GetRightBottom() const = 0;
	inline virtual double GetWidth() const = 0;
	inline virtual double GetHeight() const = 0;
};
