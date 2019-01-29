#pragma once
#include <Source/Common.h>
#include <Source/Helper/NoCopy.h>
#include <Source/Engine/Colour.h>
#include <Source/Engine/Render/Drawable.h>

namespace KidClone {

class RenderTarget : NoCopy {
public:
	virtual ~RenderTarget() = default;

	auto draw(const Drawable&)->void;

	virtual auto getSize() const->Vector2u = 0;
	virtual auto clear(Colour color = Colour(0, 0, 0, 255))->void = 0;
	virtual auto display()->void = 0;

protected:
	RenderTarget() = default;
};

}
