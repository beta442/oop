#pragma once

#include "../canvas/ICanvas.h"

class ICanvasDrawable
{
public:
	~ICanvasDrawable() = default;

	virtual void Draw(const ICanvas& canvas) const = 0;
};
