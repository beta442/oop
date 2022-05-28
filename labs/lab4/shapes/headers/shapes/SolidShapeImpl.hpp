#pragma once

#include "ISolidShape.h"
#include "ShapeImpl.hpp"

template <typename Base = ISolidShape>
class SolidShapeImpl : public ShapeImpl<Base>
{
public:
	using MyBase = ShapeImpl<Base>;

public:
	SolidShapeImpl(const Point& basePoint, const Color& outlineColor, const Color& fillColor, const std::string& type = s_type)
		: MyBase(basePoint, outlineColor, type)
		, m_fillColor(fillColor)
	{
	}

	inline std::string ToString() const override
	{
		return MyBase::ToString()
			+ "Fill color: " + MyBase::ColorToString(GetFillColor()) + '\n';
	}

	inline Color GetFillColor() const override final
	{
		return m_fillColor;
	}

private:
	static inline const std::string& s_type = "SolidShape";

	Color m_fillColor;
};
