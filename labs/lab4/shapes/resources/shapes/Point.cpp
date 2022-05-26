#include "../../headers/shapes/Point.h"

inline bool Point::operator==(const Point& other) const
{
	return x == other.x && y == other.y;
}

std::string Point::ToString() const
{
	return "X: " + std::to_string(x) + ", Y: " + std::to_string(y) + '\n';
}

double Point::Distance(const Point& other) const
{
	return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
}
