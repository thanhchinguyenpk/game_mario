#include "Flatform.h"

void Flatform::Render()
{
	//RenderBoundingBox();
}

void Flatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
