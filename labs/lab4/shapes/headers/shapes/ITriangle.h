#pragma once

#include "ISolidShape.h"

class ITriangle : public ISolidShape
{
public:
	virtual Point GetVertex1() const = 0;
	virtual Point GetVertex2() const = 0;
	virtual Point GetVertex3() const = 0;

protected:
	~ITriangle() = default;
};
