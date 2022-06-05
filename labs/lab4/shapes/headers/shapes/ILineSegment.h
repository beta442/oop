#pragma once

#include "IShape.h"

class ILineSegment : public IShape
{
public:
	ILineSegment(const ILineSegment&) = default;
	ILineSegment(const ILineSegment&&) noexcept = delete;
	ILineSegment& operator=(const ILineSegment&) = delete;
	ILineSegment& operator=(const ILineSegment&&) noexcept = delete;

	inline virtual Point GetStartPoint() const = 0;
	inline virtual Point GetEndPoint() const = 0;

protected:
	ILineSegment() = default;
	~ILineSegment() = default;
};
