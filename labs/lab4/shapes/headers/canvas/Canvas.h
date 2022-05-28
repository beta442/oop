#pragma once

#include "ICanvas.h"

class Canvas : public ICanvas
{
public:
	Canvas();

	void DrawCircle(const Point& center, const double radius, const Color lineColor) const override final;
	void DrawLine(const Point& from, const Point& to, const Color lineColor) const override final;
	void FillCircle(const Point& center, const double radius, const Color fillColor) const override final;
	void FillPolygon(const std::vector<Point>& points, const Color fillColor) const override final;
};
