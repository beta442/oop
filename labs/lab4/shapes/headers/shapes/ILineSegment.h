#pragma once

#include "IShape.h"

class ILineSegment : public IShape
{
public:
	virtual Point GetStartPoint() const = 0;
	virtual Point GetEndPoint() const = 0;

protected:
	ILineSegment() = default;
	~ILineSegment() = default;
};
