#pragma once

#include "ISolidShape.h"

class ITriangle : public ISolidShape
{
public:
	ITriangle(const ITriangle&) = default;
	ITriangle(const ITriangle&&) noexcept = delete;
	ITriangle& operator=(const ITriangle&) = delete;
	ITriangle& operator=(const ITriangle&&) noexcept = delete;

	inline virtual Point GetVertex1() const = 0;
	inline virtual Point GetVertex2() const = 0;
	inline virtual Point GetVertex3() const = 0;

protected:
	ITriangle() = default;
	~ITriangle() = default;
};
