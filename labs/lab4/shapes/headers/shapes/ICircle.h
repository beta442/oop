#pragma once

#include "ISolidShape.h"

class ICircle : public ISolidShape
{
public:
	ICircle(const ICircle&) = default;
	ICircle(const ICircle&&) noexcept = delete;
	ICircle& operator=(const ICircle&) = delete;
	ICircle& operator=(const ICircle&&) noexcept = delete;

	virtual Point GetCenter() const = 0;
	virtual double GetRadius() const = 0;

protected:
	ICircle() = default;
	~ICircle() = default;
};
