#pragma once

#include "ITriangle.h"
#include "SolidShapeImpl.hpp"

class Triangle : public SolidShapeImpl<ITriangle>
{
public:
	using MyBase = SolidShapeImpl<ITriangle>;

public:
	Triangle(const Point& firstVertex,
		const Point& secondVertex, const Point& thirdVertex,
		const Color& outlineColor, const Color& fillColor);

	double GetArea() const final;
	double GetPerimeter() const final;

	Point GetVertex1() const final;
	Point GetVertex2() const final;
	Point GetVertex3() const final;

	void Draw(ICanvas& canvas) const final;

private:
	static inline const std::string s_type = "Triangle";

	std::string ToStringAdditional() const override;

	Point m_v1, m_v2, m_v3;
};
