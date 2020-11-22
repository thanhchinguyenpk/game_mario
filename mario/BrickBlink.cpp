#include "BrickBlink.h"

void BrickBlink::Render()
{
	int direction = 1;
	int ny = 1;
	animations[0]->Render(x, y, 0, 255, direction, ny);
	//RenderBoundingBox();
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BLINK_BBOX_WIDTH/2;
	t = y - BRICK_BLINK_BBOX_HEIGHT/2;
	r = x + BRICK_BLINK_BBOX_WIDTH/2;
	b = y + BRICK_BLINK_BBOX_HEIGHT/2;
}

void BrickBlink::SetState(int state)
{
}

BrickBlink::BrickBlink()
{
}
