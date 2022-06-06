#pragma once

#include <iomanip>
#include <sstream>

#include "IShape.h"

template <typename Base = IShape>
class ShapeImpl : public Base
{
public:
	std::string ToString() const override
	{
		return "Type: " + m_type + '\n' 
			+ "Base point: " + m_basePoint.ToString()
			+ "Outline color: " + ColorToString(GetOutlineColor()) + '\n'
			+ "Area: " + std::to_string(GetArea()) + '\n'
			+ "Perimeter: " + std::to_string(GetPerimeter()) + '\n'
			+ ToStringAdditional();
	}

	double GetArea() const override
	{
		return 0;
	}

	double GetPerimeter() const override
	{
		return 0;
	}

	Color GetOutlineColor() const final
	{
		return m_outlineColor;
	}

	Point GetBasePoint() const final
	{
		return m_basePoint;
	}

protected:
	ShapeImpl(const Point& basePoint, const Color& outlineColor, std::string type = s_defaultType)
		: m_basePoint(basePoint)
		, m_outlineColor(outlineColor)
		, m_type(std::move(type))
	{
	}
	~ShapeImpl() = default;

	virtual std::string ToStringAdditional() const = 0;

	std::string ColorToString(const Color& color) const
	{
		std::stringstream ss;
		ss << std::setfill('0') << std::setw(8) << std::hex << color << std::dec;
		return ss.str();
	}

private:
	inline static const std::string s_defaultType = "Shape";

	Point m_basePoint;
	Color m_outlineColor;
	std::string m_type;
};
