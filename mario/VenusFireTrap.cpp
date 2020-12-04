#include "VenusFireTrap.h"

void VenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_BBOX_WIDTH / 2;
	top = y - PLANT_BBOX_HEIGHT / 2;
	right = x + PLANT_BBOX_WIDTH / 2;
	bottom = y + PLANT_BBOX_HEIGHT / 2;
}

void VenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += dy;
	if (y < 340)
		vy = 0;
}

void VenusFireTrap::Render()
{

	int ani = PLANT_ANI_WALKING;


	animations[ani]->Render(x, y, 0, 255, 1, ny);

	//RenderBoundingBox();
}

void VenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_GOING_UP:
		vy = -PLANT_WALKING_SPEED;
		//time_going_up = GetTickCount();
		//is_up = true;
		break;
	}
}

VenusFireTrap::VenusFireTrap()
{
}
