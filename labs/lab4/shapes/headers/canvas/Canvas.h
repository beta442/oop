#pragma once

#include <SFML\Graphics.hpp>

#include "ICanvas.h"

class Canvas : public ICanvas
{
public:
	Canvas(unsigned width, unsigned height, const std::string& windowTitle);

	void DrawCircle(const Point& center, const double radius, const Color lineColor) override final;
	void DrawLine(const Point& from, const Point& to, const Color lineColor) override final;
	void FillCircle(const Point& center, const double radius, const Color fillColor) override final;
	void FillPolygon(const std::vector<Point>& points, const Color fillColor) override final;

	sf::RenderWindow& GetRenderWindow();

private:
	sf::RenderWindow m_renderWindow;
};
