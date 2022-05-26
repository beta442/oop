#pragma once

#include <string>

class Point
{
public:
	std::string ToString() const;
	double Distance(const Point& other) const;

	inline bool operator==(const Point& other) const;

	double x, y;
};
