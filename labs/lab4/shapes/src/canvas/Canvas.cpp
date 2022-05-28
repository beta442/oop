#include "../../headers/canvas/Canvas.h"

Canvas::Canvas(unsigned width, unsigned height, const std::string& windowTitle)
	: m_renderWindow(sf::VideoMode(width, height), windowTitle, sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 4))
{
	m_renderWindow.setFramerateLimit(30);
	m_renderWindow.setVerticalSyncEnabled(true);
}

static inline const auto OUTLINE_THICKNESS = 2;

void Canvas::DrawCircle(const Point& center, const double radius, const Color lineColor)
{
	sf::CircleShape circle;
	circle.setRadius(static_cast<float>(radius));
	circle.setPosition(static_cast<float>(center.x - radius), static_cast<float>(center.y + radius));

	circle.setFillColor(sf::Color::Transparent);
	sf::Color outlineColor(lineColor);
	circle.setOutlineColor(outlineColor);
	circle.setOutlineThickness(OUTLINE_THICKNESS);

	m_renderWindow.draw(circle);
}

void Canvas::DrawLine(const Point& from, const Point& to, const Color lineColor)
{
	sf::Color color(lineColor);
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(from.x, from.y), color),
		sf::Vertex(sf::Vector2f(to.x, to.y), color)
	};

	m_renderWindow.draw(line, OUTLINE_THICKNESS, sf::Lines);
}

void Canvas::FillCircle(const Point& center, const double radius, const Color fillColor)
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setPosition(center.x - radius, center.y + radius);

	sf::Color color(fillColor);
	circle.setFillColor(color);

	m_renderWindow.draw(circle);
}

void Canvas::FillPolygon(const std::vector<Point>& points, const Color fillColor)
{
	sf::ConvexShape convex;

	convex.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		convex.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	sf::Color color(fillColor);
	convex.setFillColor(color);

	m_renderWindow.draw(convex);
}

sf::RenderWindow& Canvas::GetRenderWindow()
{
	return m_renderWindow;
}
