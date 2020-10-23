#pragma once
#include "GameObject.h"

#define MUSHROOM_WALKING_SPEED 0.05f;

#define  MUSHROOM_BBOX_WIDTH 16*3
#define  MUSHROOM_BBOX_HEIGHT 16*3
#define  MUSHROOM_BBOX_HEIGHT_DIE 9

#define  MUSHROOM_STATE_WALKING 100
#define  MUSHROOM_STATE_DIE 200

#define  MUSHROOM_ANI_WALKING 0
#define  MUSHROOM_ANI_DIE 1

#define  MUSHROOM_TIME_GO_UP 100;
#define  MUSHROOM_FLAT_EXCEPT_FIRST_BRICK_COIN 0;

class Mushroom : public CGameObject
	{
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();
		DWORD time_go_out_brick;


	public:
		virtual void SetState(int state);
		Mushroom();
	};

