#include "Flatform.h"

void Flatform::Render()
{
	RenderBoundingBox();
}

void Flatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	/*
		left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = x + MARIO_BIG_BBOX_WIDTH/2;
			bottom = y + MARIO_BIG_BBOX_HEIGHT/2;*/
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
