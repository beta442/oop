#pragma once

#include "../canvas/ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(const ICanvas& canvas) const = 0;

protected:
	~ICanvasDrawable() = default;
};
