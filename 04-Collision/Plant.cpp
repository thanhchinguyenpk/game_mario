#include "Plant.h"
#include "Mario.h"
#include "debug.h"

extern CMario* mario;


void Plant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PLANT_BBOX_WIDTH;
	bottom = y + PLANT_BBOX_HEIGHT;
}

void Plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	//x += dx;
	

	if (GetTickCount() - time_go_out_brick < 1600)
	{
		//vy = MUSHROOM_WALKING_SPEED;

		y -= dy;
	}
	else {
		DebugOut(L"[ERROR-------------BUG--------------] MARIOOOOO. Error: %f\n", mario->y);
		if(mario->y<70.0f)
			SetState(PLANT_STATE_SHOOTING_UP);
		else if (mario->y >= 70.0f)
			SetState(PLANT_STATE_SHOOTING_DOWN);
			
	}


}

void Plant::Render()
{
	int ani = PLANT_ANI_WALKING;
	if (state == PLANT_STATE_SHOOTING_UP) {
		ani = PLANT_ANI_SHOOTING_UP;
	}
	else if (state == PLANT_STATE_SHOOTING_DOWN)
		ani= PLANT_ANI_SHOOTING_DOWN;

	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void Plant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_WALKING:
		vy = PLANT_WALKING_SPEED;
		break;
	case PLANT_STATE_SHOOTING_UP:
		vy = 0;
		break;
	case PLANT_STATE_SHOOTING_DOWN:
		vy = 0;
		break;
	}
	//vy = PLANT_WALKING_SPEED;
}

Plant::Plant()
{
	this->time_go_out_brick = GetTickCount();
}

