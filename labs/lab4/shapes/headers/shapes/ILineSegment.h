#pragma once

#include "IShape.h"

class ILineSegment : public IShape
{
public:
	~ILineSegment() = default;

	inline virtual Point GetStartPoint() const = 0;
	inline virtual Point GetEndPoint() const = 0;
};
