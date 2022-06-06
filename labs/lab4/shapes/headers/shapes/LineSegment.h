#pragma once

#include "ILineSegment.h"
#include "ShapeImpl.hpp"

class LineSegment : public ShapeImpl<ILineSegment>
{
public:
	using MyBase = ShapeImpl<ILineSegment>;

public:
	LineSegment(const Point& start, const Point& end, const Color& outlineColor);

	double GetArea() const final;
	double GetPerimeter() const final;

	Point GetStartPoint() const final;
	Point GetEndPoint() const final;

	void Draw(ICanvas& canvas) const final;

private:
	std::string ToStringAdditional() const override;

	inline static const std::string s_type = "LineSegment";

	Point m_endPoint;
};
