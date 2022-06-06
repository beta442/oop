#pragma once

#include "IRectangle.h"
#include "SolidShapeImpl.hpp"

class Rectangle : public SolidShapeImpl<IRectangle>
{
public:
	using MyBase = SolidShapeImpl<IRectangle>;

public:
	Rectangle(const Point& basePoint,
		const double width, const double height, const Color& outlineColor, const Color& fillColor);

	double GetArea() const final;
	double GetPerimeter() const final;

	Point GetLeftTop() const final;
	Point GetRightBottom() const final;
	double GetWidth() const final;
	double GetHeight() const final;

	void Draw(ICanvas& canvas) const final;

private:
	static inline const std::string s_type = "Rectangle";

	std::string ToStringAdditional() const override;

	double m_width, m_height;
};
