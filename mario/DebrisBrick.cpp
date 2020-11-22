#include "DebrisBrick.h"

void DebrisBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);

	vy += DEBRIS_BRICK_GRAVITY * dt;

	x += dx;
	y += dy;
}

void DebrisBrick::Render()
{
	int direction = 1;
	int ny = 1;
	animations[0]->Render(x, y, 0, 255, direction, ny);
}

void DebrisBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

DebrisBrick::DebrisBrick(float brick_pos_x, float brick_pos_y, int nx, float height)
{
	vx = DEBRIS_BRICK_SPEED_X * nx;
	vy = -DEBRIS_BRICK_SPEED_Y * height;
	x = brick_pos_x;
	y = brick_pos_y;
	
}
