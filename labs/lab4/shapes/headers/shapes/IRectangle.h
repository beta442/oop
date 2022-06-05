#pragma once

#include "ISolidShape.h"

class IRectangle : public ISolidShape
{
public:
	IRectangle(const IRectangle&) = default;
	IRectangle(const IRectangle&&) noexcept = delete;
	IRectangle& operator=(const IRectangle&) = delete;
	IRectangle& operator=(const IRectangle&&) noexcept = delete;

	inline virtual Point GetLeftTop() const = 0;
	inline virtual Point GetRightBottom() const = 0;
	inline virtual double GetWidth() const = 0;
	inline virtual double GetHeight() const = 0;

protected:
	IRectangle() = default;
	~IRectangle() = default;
};
