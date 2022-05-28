#pragma once

#include <vector>

#include "../shapes/Types.h"

class ICanvas
{
public:
	virtual void DrawCircle(const Point& center, const double radius, const Color lineColor) const = 0;
	virtual void DrawLine(const Point& from, const Point& to, const Color lineColor) const = 0;
	virtual void FillCircle(const Point& center, const double radius, const Color fillColor) const = 0;
	virtual void FillPolygon(const std::vector<Point>& points, const Color fillColor) const = 0;

protected:
	~ICanvas() = default;
};
