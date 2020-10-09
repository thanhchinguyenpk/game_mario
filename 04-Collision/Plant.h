#pragma once
#include "GameObject.h"

#define PLANT_WALKING_SPEED 0.02f;

#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 33
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define PLANT_STATE_WALKING 100
#define PLANT_STATE_SHOOTING_UP 200
#define PLANT_STATE_SHOOTING_DOWN 300

#define PLANT_ANI_WALKING 0
#define PLANT_ANI_SHOOTING_UP 1
#define PLANT_ANI_SHOOTING_DOWN 2

class Plant : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD time_go_out_brick;


public:
	virtual void SetState(int state);
	Plant();
};