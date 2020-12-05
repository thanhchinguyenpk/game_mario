#pragma once

#include "GameObject.h"
#include "PlantBullet.h"

#define PLANT_WALKING_SPEED 0.06f;

#define PLANT_BBOX_WIDTH 16*3
#define PLANT_BBOX_HEIGHT 33*3
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define PLANT_STATE_GOING_UP			 100
#define PLANT_STATE_GOING_DOWN			 200
#define PLANT_STATE_SHOOTING_UP			 300
#define PLANT_STATE_SHOOTING_DOWN		 400
#define PLANT_STATE_SEEING				 500
#define PLANT_STATE_STANDING_STILL		 600
#define PLANT_STATE_SLEEPING	700

#define PLANT_ANI_SCORPION_DOWN 0
#define PLANT_ANI_SCORPION_UP 1
#define PLANT_ANI_SHOOTING_DOWN 2
#define PLANT_ANI_SHOOTING_UP 3



#define PLANT_TIME_GOING_UP			 2400
#define PLANT_TIME_GOING_DOWN			 200
#define PLANT_TIME_SHOOTING_UP			 300
#define PLANT_TIME_SHOOTING		 2200
#define PLANT_TIME_SEEING				 3000
#define PLANT_TIME_STANDING_STILL		 4000

#define PLANT_HEIGHT_RAISE_HEAD		 300

class VenusFireTrap : public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void SetState(int state);
	VenusFireTrap();
	//TimerCustom* contemplation_time = new TimerCustom(3000);
	TimerCustom* sleep_time = new TimerCustom(2000);
	TimerCustom* seeing_time = new TimerCustom(1800);
	TimerCustom* seeing_time_shoot_go_down = new TimerCustom(3000);

	bool CheckInArea(float l,float t,float r,float b);


};

