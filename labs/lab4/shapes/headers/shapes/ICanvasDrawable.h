#pragma once

#include "../canvas/ICanvas.h"

class ICanvasDrawable
{
public:
	ICanvasDrawable(const ICanvasDrawable&) = default;
	ICanvasDrawable(const ICanvasDrawable&&) noexcept = delete;
	ICanvasDrawable& operator=(const ICanvasDrawable&) = delete;
	ICanvasDrawable& operator=(const ICanvasDrawable&&) noexcept = delete;

	virtual void Draw(ICanvas& canvas) const = 0;

protected:
	ICanvasDrawable() = default;
	~ICanvasDrawable() = default;
};
