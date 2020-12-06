﻿#include "VenusFireTrap.h"
#include "Mario.h"
#include "debug.h"

 extern CMario* mario;
 extern vector<LPGAMEOBJECT> objects;

void VenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = x + VENUS_BBOX_WIDTH / 2;
	bottom = y + VENUS_BBOX_HEIGHT / 2;
}

void VenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += dy;
	/*if (y < 340 && contemplation_time->startTime == 0)
	{
		vy = 0;
		contemplation_time->StartTime();
		SetState(VENUS_STATE_SEEING); 
	}
	else if (y > 440 && sleep_time->startTime == 0)
	{
		vy = 0;
		sleep_time->StartTime();
	}

	if (contemplation_time->IsTimeUp())
	{
		SetState(VENUS_STATE_GOING_DOWN);
		contemplation_time->startTime = 0;
	}
	else if (sleep_time->IsTimeUp())
	{
		SetState(VENUS_STATE_GOING_UP);
		sleep_time->startTime = 0;
	}*/


	if (y < pos_y_venus_max_top && seeing_time->startTime==false&& seeing_time_shoot_go_down->startTime==false)
	{
		vy = 0;
		SetState(VENUS_STATE_SEEING);
	}
	else if (y > pos_y_venus_max_bot && sleep_time->startTime == 0)
	{
		vy = 0;
		SetState(VENUS_STATE_SLEEPING);
	}


	if (seeing_time->IsTimeUp())
	{
		//shoot
		seeing_time->startTime = 0;

		PlantBullet* VENUS_bullet;
		VENUS_bullet = new PlantBullet();

		pos_x_fireball = this->x;
		pos_y_fireball = this->y;

		if (level == VENUS_RED_TRAP)
			pos_y_fireball -=35;
		else
			pos_y_fireball -= 20;
			
		VENUS_bullet->SetPosition(pos_x_fireball, pos_y_fireball);
		VENUS_bullet->AddAnimation(14001);

		if (mario->y < VENUS_HEIGHT_RAISE_HEAD && mario->x < this->x)
			VENUS_bullet->SetState(PLANT_BULLET_STATE_FOUR);
		else if (mario->y >= VENUS_HEIGHT_RAISE_HEAD && mario->x < this->x)
			VENUS_bullet->SetState(PLANT_BULLET_STATE_THREE);
		else if (mario->y >= VENUS_HEIGHT_RAISE_HEAD && mario->x >= this->x)
			VENUS_bullet->SetState(PLANT_BULLET_STATE_TWO);
		else if (mario->y < VENUS_HEIGHT_RAISE_HEAD && mario->x >= this->x)
			VENUS_bullet->SetState(PLANT_BULLET_STATE_ONE);

		objects.push_back(VENUS_bullet);
	}else if (seeing_time_shoot_go_down->IsTimeUp())
	{
		seeing_time_shoot_go_down->startTime = 0;
		SetState(VENUS_STATE_GOING_DOWN);
	}
	else if (sleep_time->IsTimeUp())
	{
		float l, t, r, b;
		mario->GetBoundingBox(l, t, r, b);
		if(CheckInArea(l,t,r,b)==false)
		{
			SetState(VENUS_STATE_GOING_UP);
			sleep_time->startTime = 0;
		}
		
	}


}

void VenusFireTrap::Render()
{

	int ani = VENUS_ANI_SCORPION_DOWN;
	int direction = 1;
	
	if (level == VENUS_RED_TRAP)
	{
		if (mario->y < 345)
			ani = VENUS_ANI_SHOOTING_UP;
		else
			ani = VENUS_ANI_SHOOTING_DOWN;

		if (state == VENUS_STATE_GOING_UP || state == VENUS_STATE_GOING_DOWN)
		{
			if (mario->y < 345)
				ani = VENUS_ANI_SCORPION_UP;
			else
				ani = VENUS_ANI_SCORPION_DOWN;
		}
		if (mario->x > 1105)
			direction = -1;
	}
	else if (level == VENUS_GREEN_TRAP)
	{
		if (mario->y < 345)
			ani = VENUS_GREEN_ANI_SHOOTING_UP;
		else
			ani = VENUS_GREEN_ANI_SHOOTING_DOWN;

		if (state == VENUS_STATE_GOING_UP || state == VENUS_STATE_GOING_DOWN)
		{
			if (mario->y < 345)
				ani = VENUS_GREEN_ANI_SCORPION_UP;
			else
				ani = VENUS_GREEN_ANI_SCORPION_DOWN;
		}
		if (mario->x > 5615)
			direction = -1;
	}
	
	//	if(state== VENUS_STATE_SEEING)
	//	ani = VENUS_ANI_SHOOTING_UP;
	animations[ani]->Render(x, y, 0, 255, direction, ny);

	//RenderBoundingBox();
}

void VenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_STATE_GOING_UP:
		vy = -VENUS_WALKING_SPEED;
		break;
	case VENUS_STATE_GOING_DOWN:
		vy = VENUS_WALKING_SPEED;
		break;
	case VENUS_STATE_SEEING:
		seeing_time->StartTime();
		seeing_time_shoot_go_down->StartTime();
		vx = 0;
		vy = 0;
		break;
	case VENUS_STATE_SLEEPING:
		sleep_time->StartTime();
		vx = 0;
		vy = 0;
		break;

	}
}

VenusFireTrap::VenusFireTrap(int lv)
{
	this->level = lv;
	TakeMaxTopAndBot();
}

bool VenusFireTrap::CheckInArea(float l, float t, float r, float b)
{
	if (level == VENUS_GREEN_TRAP)
	{
		return l < 5690 && r>5530 && t < 530 && b>0;
		DebugOut(L"[ERROR----------lv2?------------------] DINPUT::GetDeviceData failed. Error: %d\n");
	}
	return l<1180 && r>1030 && t<530 && b>0;
}

void VenusFireTrap::TakeMaxTopAndBot()
{
	if (level == VENUS_RED_TRAP)
	{
		pos_y_venus_max_top = 340;//dm chiều y hướng xuống :(
		pos_y_venus_max_bot = 440;
	}
	else if(level == VENUS_GREEN_TRAP)
	{
		pos_y_venus_max_top = 350;//dm chiều y hướng xuống :(
		pos_y_venus_max_bot = 430;
	}
}
