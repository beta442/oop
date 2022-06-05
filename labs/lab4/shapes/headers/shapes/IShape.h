#pragma once

#include "ICanvasDrawable.h"
#include "Types.h"

class IShape : public ICanvasDrawable
{
public:
	IShape(const IShape&) = default;
	IShape(const IShape&&) noexcept = delete;
	IShape& operator=(const IShape&) = delete;
	IShape& operator=(const IShape&&) noexcept = delete;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual Color GetOutlineColor() const = 0;
	virtual Point GetBasePoint() const = 0;

protected:
	IShape() = default;
	~IShape() = default;
};
