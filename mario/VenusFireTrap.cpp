#include "VenusFireTrap.h"
#include "Mario.h"
 extern CMario* mario;
 extern vector<LPGAMEOBJECT> objects;

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
	/*if (y < 340 && contemplation_time->startTime == 0)
	{
		vy = 0;
		contemplation_time->StartTime();
		SetState(PLANT_STATE_SEEING); 
	}
	else if (y > 440 && sleep_time->startTime == 0)
	{
		vy = 0;
		sleep_time->StartTime();
	}

	if (contemplation_time->IsTimeUp())
	{
		SetState(PLANT_STATE_GOING_DOWN);
		contemplation_time->startTime = 0;
	}
	else if (sleep_time->IsTimeUp())
	{
		SetState(PLANT_STATE_GOING_UP);
		sleep_time->startTime = 0;
	}*/

	if (y < 340&& seeing_time->startTime==false&& seeing_time_shoot_go_down->startTime==false)
	{
		vy = 0;
		SetState(PLANT_STATE_SEEING);
	}
	else if (y > 440 && sleep_time->startTime == 0)
	{
		vy = 0;
		SetState(PLANT_STATE_SLEEPING);
	}


	if (seeing_time->IsTimeUp())
	{
		//shoot
		seeing_time->startTime = 0;

		PlantBullet* plant_bullet;
		plant_bullet = new PlantBullet();
		plant_bullet->SetPosition(this->x, this->y - 40);
		plant_bullet->AddAnimation(14001);

		if (mario->y < PLANT_HEIGHT_RAISE_HEAD && mario->x < this->x)
			plant_bullet->SetState(PLANT_BULLET_STATE_FOUR);
		else if (mario->y >= PLANT_HEIGHT_RAISE_HEAD && mario->x < this->x)
			plant_bullet->SetState(PLANT_BULLET_STATE_THREE);
		else if (mario->y >= PLANT_HEIGHT_RAISE_HEAD && mario->x >= this->x)
			plant_bullet->SetState(PLANT_BULLET_STATE_TWO);
		else if (mario->y < PLANT_HEIGHT_RAISE_HEAD && mario->x >= this->x)
			plant_bullet->SetState(PLANT_BULLET_STATE_ONE);

		objects.push_back(plant_bullet);
	}else if (seeing_time_shoot_go_down->IsTimeUp())
	{
		seeing_time_shoot_go_down->startTime = 0;
		SetState(PLANT_STATE_GOING_DOWN);
	}
	else if (sleep_time->IsTimeUp())
	{
		float l, t, r, b;
		mario->GetBoundingBox(l, t, r, b);
		if(CheckInArea(l,t,r,b)==false)
		{
			SetState(PLANT_STATE_GOING_UP);
			sleep_time->startTime = 0;
		}
		
	}


}

void VenusFireTrap::Render()
{

	int ani = PLANT_ANI_SCORPION_DOWN;
	int direction = 1;
	
		if (mario->y < 345)
			ani = PLANT_ANI_SHOOTING_UP;
		else
			ani = PLANT_ANI_SHOOTING_DOWN;
		if (mario->x > 1105)
			direction = -1;
	if(state== PLANT_STATE_GOING_UP|| state == PLANT_STATE_GOING_DOWN)
		if (mario->y < 345)
			ani = PLANT_ANI_SCORPION_UP;
		else
			ani = PLANT_ANI_SCORPION_DOWN;
	if (mario->x > 1105)
		direction = -1;
	
	//	if(state== PLANT_STATE_SEEING)
	//	ani = PLANT_ANI_SHOOTING_UP;
	animations[ani]->Render(x, y, 0, 255, direction, ny);

	//RenderBoundingBox();
}

void VenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_GOING_UP:
		vy = -PLANT_WALKING_SPEED;
		break;
	case PLANT_STATE_GOING_DOWN:
		vy = PLANT_WALKING_SPEED;
		break;
	case PLANT_STATE_SEEING:
		seeing_time->StartTime();
		seeing_time_shoot_go_down->StartTime();
		vx = 0;
		vy = 0;
		break;
	case PLANT_STATE_SLEEPING:
		sleep_time->StartTime();
		vx = 0;
		vy = 0;
		break;

	}
}

VenusFireTrap::VenusFireTrap()
{
}

bool VenusFireTrap::CheckInArea(float l, float t, float r, float b)
{
	return l<1180 && r>1030 && t<530 && b>0;
}
