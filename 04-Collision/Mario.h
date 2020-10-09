#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.4f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SITDOWN			500

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3


#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7


#define MARIO_ANI_DIE				8

#define MARIO_ANI_BIG_JUMP_UP_LEFT			9
#define MARIO_ANI_BIG_JUMP_UP_RIGHT			10
#define MARIO_ANI_BIG_JUMP_DOWN_RIGHT			11
#define MARIO_ANI_BIG_JUMP_DOWN_LEFT			12

#define MARIO_ANI_SMALL_JUMP_RIGHT		13
#define MARIO_ANI_SMALL_JUMP_LEFT		14

#define MARIO_ANI_BIG_SITDOWN_RIGT		15
#define MARIO_ANI_BIG_SITDOWN_LEFT	16

#define MARIO_ANI_BIG_TAIL_IDLE_RIGHT		0
#define MARIO_ANI_BIG_TAIL_IDLE_LEFT			1

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_SITDOWN_BBOX_WIDTH  14
#define MARIO_BIG_SITDOWN_BBOX_HEIGHT 19

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15



#define MARIO_UNTOUCHABLE_TIME 5000



class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	bool is_in_object = false;
	bool is_sitdown = false;
public: 
	CMario() : CGameObject()
	{
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetIsInObject(bool temp) { is_in_object = temp; };
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool GetIsInObject() { return is_in_object; };

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};