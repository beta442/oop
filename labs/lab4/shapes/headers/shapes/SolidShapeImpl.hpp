#pragma once

#include "ISolidShape.h"
#include "ShapeImpl.hpp"

template <typename Base = ISolidShape>
class SolidShapeImpl : public ShapeImpl<Base>
{
public:
	using MyBase = ShapeImpl<Base>;

public:
	std::string ToString() const override
	{
		return MyBase::ToString()
			+ "Fill color: " + MyBase::ColorToString(GetFillColor()) + '\n';
	}

	Color GetFillColor() const final
	{
		return m_fillColor;
	}

protected:
	SolidShapeImpl(const Point& basePoint, const Color& outlineColor, const Color& fillColor, std::string type = s_type)
		: MyBase(basePoint, outlineColor, std::move(type))
		, m_fillColor(fillColor)
	{
	}
	~SolidShapeImpl() = default;

private:
	static inline const std::string& s_type = "SolidShape";

	Color m_fillColor;
};
