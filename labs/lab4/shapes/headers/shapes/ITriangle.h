#pragma once

#include "ISolidShape.h"

class ITriangle : public ISolidShape
{
public:
	inline virtual Point GetVertex1() const = 0;
	inline virtual Point GetVertex2() const = 0;
	inline virtual Point GetVertex3() const = 0;

protected:
	~ITriangle() = default;
};
