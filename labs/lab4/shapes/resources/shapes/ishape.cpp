#include "../../headers/shapes/IShape.h"

IShape::IShape(const CPoint basePoint, const uint32_t outlineColor)
	: m_basePoint(basePoint)
	, m_outlineColor(outlineColor)
{
}
