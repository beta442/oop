#pragma once

#include "../canvas/ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

protected:
	ICanvasDrawable() = default;
	~ICanvasDrawable() = default;
};
