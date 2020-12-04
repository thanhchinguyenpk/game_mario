#include "Plant.h"
#include "Mario.h"
#include "debug.h"

extern CMario* mario;
extern vector<LPGAMEOBJECT> objects;

void Plant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x- PLANT_BBOX_WIDTH/2;
	top = y- PLANT_BBOX_HEIGHT/2;
	right = x + PLANT_BBOX_WIDTH/2;
	bottom = y + PLANT_BBOX_HEIGHT/2;
}

void Plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state==PLANT_STATE_GOING_UP)
	{
		y += dy;

		if (GetTickCount64() - time_going_up > PLANT_TIME_GOING_UP)
			SetState(PLANT_STATE_SEEING);

	}
	else if(state==PLANT_STATE_SEEING|| state == PLANT_STATE_SHOOTING_UP|| state == PLANT_STATE_SHOOTING_DOWN) {
		
		if(mario->y< PLANT_HEIGHT_RAISE_HEAD)
			SetState(PLANT_STATE_SHOOTING_UP);
		else if (mario->y >= PLANT_HEIGHT_RAISE_HEAD)
			SetState(PLANT_STATE_SHOOTING_DOWN);

		if (GetTickCount64() - time_seeing > PLANT_TIME_SHOOTING && is_shoot==true)
		{
			PlantBullet* plant_bullet;
			plant_bullet = new PlantBullet();
			plant_bullet->SetPosition(this->x, this->y - 40);
			plant_bullet->AddAnimation(14001);

			if(mario->y < PLANT_HEIGHT_RAISE_HEAD && mario->x < this->x)
				plant_bullet->SetState(PLANT_BULLET_STATE_FOUR);
			else if(mario->y >= PLANT_HEIGHT_RAISE_HEAD && mario->x < this->x)
				plant_bullet->SetState(PLANT_BULLET_STATE_THREE);
			else if(mario->y >= PLANT_HEIGHT_RAISE_HEAD && mario->x >= this->x)
				plant_bullet->SetState(PLANT_BULLET_STATE_TWO);
			else if(mario->y < PLANT_HEIGHT_RAISE_HEAD && mario->x >= this->x)
				plant_bullet->SetState(PLANT_BULLET_STATE_ONE);

			objects.push_back(plant_bullet);
			is_shoot = false;
		}

		if (GetTickCount64() - time_seeing > PLANT_TIME_SEEING)
		{
			SetState(PLANT_STATE_GOING_DOWN);
			DebugOut(L"[ERROR-------------s ddax troiq qua-------------] MARIOOOOO.");
		}
	}
	else if (state == PLANT_STATE_GOING_DOWN)
	{
		y += dy;
		if (GetTickCount64() - time_going_down > PLANT_TIME_GOING_UP)
			SetState(PLANT_STATE_STANDING_STILL);
	}
	else if (state == PLANT_STATE_STANDING_STILL)
	{
		if (GetTickCount64() - time_stading_still > PLANT_TIME_STANDING_STILL)
			SetState(PLANT_STATE_GOING_UP);
	}

}

void Plant::Render()
{
	int ani = PLANT_ANI_WALKING;
	int direction = 1;
	if (state == PLANT_STATE_SHOOTING_UP) {
		ani = PLANT_ANI_SHOOTING_UP;
	}
	else if (state == PLANT_STATE_SHOOTING_DOWN)
		ani= PLANT_ANI_SHOOTING_DOWN;


	if (mario->x > 1106)//vị trí chính giữa cây hoa bắn lửa
		direction = -1;

	animations[ani]->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

void Plant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_GOING_UP:
		vy = -PLANT_WALKING_SPEED;
		time_going_up = GetTickCount();
		is_up = true;
		break;
	case PLANT_STATE_GOING_DOWN:
		vy = PLANT_WALKING_SPEED;
		is_up = false;
		time_going_down = GetTickCount();
		break;
	case PLANT_STATE_SEEING:
		vy = 0;
		is_up = false;
		is_shoot = true;
		time_seeing= GetTickCount();
		break;
	case PLANT_STATE_SHOOTING_UP:
		vy = 0;
		break;
	case PLANT_STATE_SHOOTING_DOWN:
		vy = 0;
		break;
	case PLANT_STATE_STANDING_STILL:
		vy = 0;
		time_stading_still= GetTickCount();
		break;
	}
	//vy = PLANT_WALKING_SPEED;
}

Plant::Plant()
{
	
}

