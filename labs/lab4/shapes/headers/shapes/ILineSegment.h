#pragma once

#include "IShape.h"

class ILineSegment : public IShape
{
public:
	inline virtual Point GetStartPoint() const = 0;
	inline virtual Point GetEndPoint() const = 0;

protected:
	~ILineSegment() = default;
};
