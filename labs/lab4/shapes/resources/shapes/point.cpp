#include "../../headers/shapes/CPoint.h"

bool CPoint::operator==(const CPoint& other) const
{
	return x == other.x && y == other.y;
}
