#include "PiranhaPlant.h"

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void PiranhaPlant::Render()
{
	int ani = 0;
	int direction = 1;
	int ny = 1;

	animations[ani]->Render(x, y, 0, 255, direction, ny);
}
