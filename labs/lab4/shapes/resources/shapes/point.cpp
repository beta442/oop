#include "../../headers/shapes/CPoint.h"
#include "sstream"

bool CPoint::operator==(const CPoint& other) const
{
	return x == other.x && y == other.y;
}

std::string CPoint::ToString() const
{
	std::ostringstream oss;
	oss << "X: " << x << ", Y: " << y << std::endl;

	return oss.str();
}
