#pragma once
#include "GameObject.h"

#define	 PARA_GROOMBA_BBOX_WIDTH 20*3
#define	 PARA_GROOMBA_BBOX_HEIGHT 19*3

//vy = -0.25*3;
#define  PARA_GROOMBA_WALKING_SPEED			 0.03f;

#define  PARA_GROOMBA_STATE_MOVE_LEFT		100
#define  PARA_GROOMBA_STATE_MOVE_RIGHT		200
#define  PARA_GROOMBA_STATE_JUMP_SMALL		300
#define  PARA_GROOMBA_STATE_JUMP_BIG		400

#define  PARA_GROOMBA_ANI_JUMP_SMALL		1
#define  PARA_GROOMBA_ANI_JUMP_BIG		2

#define	 PARA_GROOMBA_SPEED_VERTICAL		0.1


#define  PARA_GROOMBA_GRAVITY		0.0009

class ParaGoomba :public CGameObject
{
	int count =1;
	DWORD moving_time;
	bool turn_on_moving = false;
public:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	ParaGoomba();
};

