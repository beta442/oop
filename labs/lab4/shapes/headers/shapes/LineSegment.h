#pragma once

#include "ILineSegment.h"
#include "ShapeImpl.hpp"

class LineSegment : public ShapeImpl<ILineSegment>
{
public:
	using MyBase = ShapeImpl<ILineSegment>;

public:
	LineSegment(const Point& start, const Point& end, const Color& outlineColor);

	inline double GetArea() const override final;
	inline double GetPerimeter() const override final;

	inline Point GetStartPoint() const override final;
	inline Point GetEndPoint() const override final;

	inline void Draw(ICanvas& canvas) const override final;

private:
	inline std::string ToStringAdditional() const override;

	inline static const std::string s_type = "LineSegment";

	Point m_endPoint;
};
