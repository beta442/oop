#pragma once

#include "IRectangle.h"
#include "SolidShapeImpl.hpp"

class Rectangle : public SolidShapeImpl<IRectangle>
{
public:
	using MyBase = SolidShapeImpl<IRectangle>;

	static inline const std::string s_type = "Rectangle";

public:
	Rectangle(const Point& basePoint,
		const double width, const double height, const Color& outlineColor, const Color& fillColor);

	inline double GetArea() const override final;
	inline double GetPerimeter() const override final;

	inline Point GetLeftTop() const override final;
	inline Point GetRightBottom() const override final;
	inline double GetWidth() const override final;
	inline double GetHeight() const override final;

private:
	inline std::string ToStringAdditional() const override;

	double m_width, m_height;
};
