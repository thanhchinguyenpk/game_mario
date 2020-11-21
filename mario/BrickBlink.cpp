#include "BrickBlink.h"

void BrickBlink::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x- BRICK_BBOX_WIDTH/2;
	t = y- BRICK_BBOX_HEIGHT/2;
	r = x + BRICK_BBOX_WIDTH/2;
	b = y + BRICK_BBOX_HEIGHT/2;
}
