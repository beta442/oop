#pragma once

#include <string>

class CPoint
{
public:
	std::string ToString() const;

	bool operator==(const CPoint& other) const;

	double x, y;
};
