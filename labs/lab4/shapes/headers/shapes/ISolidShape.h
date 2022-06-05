#pragma once

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	ISolidShape(const ISolidShape&) = default;
	ISolidShape(const ISolidShape&&) noexcept = delete;
	ISolidShape& operator=(const ISolidShape&) = delete;
	ISolidShape& operator=(const ISolidShape&&) noexcept = delete;

	virtual Color GetFillColor() const = 0;

protected:
	ISolidShape() = default;
	~ISolidShape() = default;
};
