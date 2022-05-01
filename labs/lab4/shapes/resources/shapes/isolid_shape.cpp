#include "../../headers/shapes/ISolidShape.h"

ISolidShape::ISolidShape(const CPoint basePoint,
	const uint32_t outlineColor, const uint32_t fillColor)
	: IShape(basePoint, outlineColor)
	, m_fillColor(fillColor)
{
}
