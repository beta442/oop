#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "shapes/IShape.h"

class ShapesContainer
{
public:
	using ShapePtr = std::shared_ptr<IShape>;
	using ShapeCmpType = const std::function<bool(const ShapePtr&, const ShapePtr&)>&;

	enum class ShapeType
	{
		Line,
		Triangle,
		Circle,
		Rectangle,
	};

public:
	static inline auto s_maxAreaShapePred = [](const ShapePtr& lhs, const ShapePtr& rhs) {
		return lhs->GetArea() < rhs->GetArea();
	};

	static inline auto s_minPerimeterShapePred = [](const ShapePtr& lhs, const ShapePtr& rhs) {
		return lhs->GetPerimeter() > rhs->GetPerimeter();
	};

	void ReadShapes(std::istream& input);
	void PrintShapeInfo(std::ostream& output, ShapeCmpType pred) const;
	void DrawShapes(const unsigned width, const unsigned height, const std::string& windowTitle) const;

private:
	bool ReadLineSegment(std::istream& input);
	bool ReadTriangle(std::istream& input);
	bool ReadRectangle(std::istream& input);
	bool ReadCircle(std::istream& input);

	std::vector<ShapePtr> m_shapes;
};
