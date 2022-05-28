#pragma once

#include "ITriangle.h"
#include "SolidShapeImpl.hpp"

class Triangle : public SolidShapeImpl<ITriangle>
{
public:
	using MyBase = SolidShapeImpl<ITriangle>;

	static inline const std::string s_type = "Triangle";

public:
	Triangle(const Point& firstVertex,
		const Point& secondVertex, const Point& thirdVertex,
		const Color& outlineColor, const Color& fillColor);

	inline double GetArea() const override final;
	inline double GetPerimeter() const override final;

	inline Point GetVertex1() const override final;
	inline Point GetVertex2() const override final;
	inline Point GetVertex3() const override final;

	inline void Draw(ICanvas& canvas) const override final;

private:
	inline std::string ToStringAdditional() const override;

	Point m_v1, m_v2, m_v3;
};
