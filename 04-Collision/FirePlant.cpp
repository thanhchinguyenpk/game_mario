#include "FirePlant.h"


void FirePlant::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void FirePlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIRE_PLANT_BBOX_WIDTH;
	b = y + FIRE_PLANT_BBOX_HEIGHT;
}