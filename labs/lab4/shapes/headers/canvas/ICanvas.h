#pragma once

#include <vector>

#include "../shapes/Types.h"

class ICanvas
{
public:
	ICanvas(const ICanvas&) = default;
	ICanvas(const ICanvas&&) noexcept = delete;
	ICanvas& operator=(const ICanvas&) = delete;
	ICanvas& operator=(const ICanvas&&) noexcept = delete;

	virtual void DrawCircle(const Point& center, const double radius, const Color lineColor) = 0;
	virtual void DrawLine(const Point& from, const Point& to, const Color lineColor) = 0;
	virtual void FillCircle(const Point& center, const double radius, const Color fillColor) = 0;
	virtual void FillPolygon(const std::vector<Point>& points, const Color fillColor) = 0;

protected:
	ICanvas() = default;
	~ICanvas() = default;
};
