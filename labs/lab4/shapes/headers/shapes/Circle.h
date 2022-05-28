#pragma once

#include "ICircle.h"
#include "SolidShapeImpl.hpp"

class Circle : public SolidShapeImpl<ICircle>
{
public:
	using MyBase = SolidShapeImpl<ICircle>;

	static inline const std::string s_type = "Circle";

public:
	Circle(const Point& basePoint,
		const double radius, const Color& outlineColor, const Color& fillColor);

	inline double GetArea() const override final;
	inline double GetPerimeter() const override final;

	inline Point GetCenter() const override final;
	inline double GetRadius() const override final;

	inline void Draw(ICanvas& canvas) const override final;

private:
	inline std::string ToStringAdditional() const override;

	double m_radius;
};
