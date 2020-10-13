#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_JUMP_DEFLECT_SPEED 0.4f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SITDOWN			500
#define MARIO_STATE_JUMP_HIGH			600

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



#define MARIO_ANI_TAIL_IDLE_RIGHT			17
#define MARIO_ANI_TAIL_IDLE_LEFT			18
#define MARIO_ANI_TAIL_WALKING_RIGHT		19
#define MARIO_ANI_TAIL_WALKING_LEFT			20
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT			21
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT			22
#define MARIO_ANI_TAIL_JUMP_UP_LEFT				23
#define MARIO_ANI_TAIL_JUMP_DOWN_LEFT			24
#define MARIO_ANI_TAIL_SITDOWN_RIGHT			25
#define MARIO_ANI_TAIL_SITDOWN_LEFT			26


#define MARIO_ANI_ORANGE_IDLE_RIGHT			27
#define MARIO_ANI_ORANGE_IDLE_LEFT			28
#define MARIO_ANI_ORANGE_WALKING_RIGHT		29
#define MARIO_ANI_ORANGE_WALKING_LEFT			30
#define MARIO_ANI_ORANGE_JUMP_UP_RIGHT			31
#define MARIO_ANI_ORANGE_JUMP_DOWN_RIGHT			32
#define MARIO_ANI_ORANGE_JUMP_UP_LEFT				33
#define MARIO_ANI_ORANGE_JUMP_DOWN_LEFT			34
#define MARIO_ANI_ORANGE_SITDOWN_RIGHT			35
#define MARIO_ANI_ORANGE_SITDOWN_LEFT			36


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_BIG_TAIL		3
#define	MARIO_LEVEL_BIG_ORANGE		4

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_SITDOWN_BBOX_WIDTH  14
#define MARIO_BIG_SITDOWN_BBOX_HEIGHT 19

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_BIG_TAIL_BBOX_WIDTH  21
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28

#define MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH  22
#define MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT 19




#define MARIO_UNTOUCHABLE_TIME 5000



class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD jumping_start;
	bool is_in_object = false;
	bool is_sitdown = false;

public: 
	CMario() : CGameObject()
	{
		level = MARIO_LEVEL_BIG_ORANGE;
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetIsInObject(bool temp) { is_in_object = temp; };
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void StartJumping() { jumping_start = GetTickCount(); };
	void EndJumping() { jumping_start = 0; };
	DWORD GetJumpingTime() { return jumping_start; };
	bool GetIsInObject() { return is_in_object; };
	int GetLevel() { return level; };

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};