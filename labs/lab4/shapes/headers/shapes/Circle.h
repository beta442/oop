#pragma once

#include "ICircle.h"
#include "SolidShapeImpl.hpp"

class Circle : public SolidShapeImpl<ICircle>
{
public:
	using MyBase = SolidShapeImpl<ICircle>;

public:
	Circle(const Point& basePoint,
		const double radius, const Color& outlineColor, const Color& fillColor);

	double GetArea() const final;
	double GetPerimeter() const final;

	Point GetCenter() const final;
	double GetRadius() const final;

	void Draw(ICanvas& canvas) const final;

private:
	static inline const std::string s_type = "Circle";

	std::string ToStringAdditional() const override;

	double m_radius;
};
