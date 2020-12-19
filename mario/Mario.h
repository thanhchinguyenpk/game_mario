#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED			0.3 
//0.1f
#define MARIO_JUMP_SPEED_Y			0.9
#define MARIO_JUMP_DEFLECT_SPEED	1.2
#define MARIO_GRAVITY				0.003
#define MARIO_DIE_DEFLECT_SPEED	 1.5
#define MARIO_ACCELERATION		 0.0005
#define MARIO_VY_JUM_UP			 0.04

#define MARIO_STATE_IDLE						0
#define MARIO_STATE_WALKING_RIGHT				100
#define MARIO_STATE_WALKING_LEFT				200
#define MARIO_STATE_JUMP						300
#define MARIO_STATE_DIE							400
#define MARIO_STATE_SITDOWN						500
#define MARIO_STATE_SHOOT_BULLET				600
#define MARIO_STATE_SPIN						700
#define MARIO_STATE_JUMP_SHOOT_BULLET			800
#define MARIO_STATE_FLY							900
#define MARIO_STATE_FLY_HIGH					1000
#define MARIO_STATE_BRING_KOOMPASHELL_RIGHT			1100
#define MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT			1200

#define MARIO_ANI_BIG_IDLE_RIGHT			0
#define MARIO_ANI_BIG_IDLE_LEFT				1
#define MARIO_ANI_SMALL_IDLE_RIGHT			2
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
#define MARIO_ANI_BIG_SITDOWN_LEFT		16



#define MARIO_ANI_TAIL_IDLE_RIGHT				17
#define MARIO_ANI_TAIL_IDLE_LEFT				18
#define MARIO_ANI_TAIL_WALKING_RIGHT			19
#define MARIO_ANI_TAIL_WALKING_LEFT				20
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT			21
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT			22
#define MARIO_ANI_TAIL_JUMP_UP_LEFT				23
#define MARIO_ANI_TAIL_JUMP_DOWN_LEFT			24
#define MARIO_ANI_TAIL_SITDOWN_RIGHT			25
#define MARIO_ANI_TAIL_SITDOWN_LEFT				26


#define MARIO_ANI_ORANGE_IDLE_RIGHT					27
#define MARIO_ANI_ORANGE_IDLE_LEFT					28
#define MARIO_ANI_ORANGE_WALKING_RIGHT				29
#define MARIO_ANI_ORANGE_WALKING_LEFT				30
#define MARIO_ANI_ORANGE_JUMP_UP_RIGHT				31
#define MARIO_ANI_ORANGE_JUMP_DOWN_RIGHT			32
#define MARIO_ANI_ORANGE_JUMP_UP_LEFT				33
#define MARIO_ANI_ORANGE_JUMP_DOWN_LEFT				34
#define MARIO_ANI_ORANGE_SITDOWN_RIGHT				35
#define MARIO_ANI_ORANGE_SITDOWN_LEFT				36
#define MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT			37
#define MARIO_ANI_ORANGE_SHOOT_BULLET_LEFT			38

#define MARIO_ANI_TAIL_SPIN_TAIL_RIGHT			39
#define MARIO_ANI_TAIL_SPIN_TAIL_LEFT			40

#define MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT			41
#define MARIO_ANI_TAIL_FLY										42
#define MARIO_ANI_TAIL_FLY_HIGH									43
#define MARIO_ANI_BRING_KOOMPASHELL_RIGHT			44
#define MARIO_ANI_ROUSE_KOOMPASHELL_RIGHT			45

#define MARIO_ANI_BIG_SKID	46
#define MARIO_ANI_BIG_RUN 47

#define MARIO_ANI_SMALL_RUN_RIGHT	48
#define MARIO_ANI_SMALL_SKID_LEFT 49

#define MARIO_ANI_TAIL_RUN_RIGHT	50
#define MARIO_ANI_TAIL_SKID_LEFT 51

#define MARIO_ANI_ORANGE_RUN_RIGHT	52
#define MARIO_ANI_ORANGE_SKID_LEFT 53

#define MARIO_ANI_TAIL_ROUSE_KOOMPASHELL_RIGHT			54
#define MARIO_ANI_TAIL_BRING_KOOMPASHELL_RIGHT			55

#define MARIO_ANI_SMALL_ROUSE_KOOMPASHELL_RIGHT			56
#define MARIO_ANI_SMALL_BRING_KOOMPASHELL_RIGHT			57

#define MARIO_ANI_ORANGE_ROUSE_KOOMPASHELL_RIGHT			58
#define MARIO_ANI_ORANGE_BRING_KOOMPASHELL_RIGHT			59

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_BIG_TAIL		3
#define	MARIO_LEVEL_BIG_ORANGE		4

#define MARIO_BIG_BBOX_WIDTH  15*3
#define MARIO_BIG_BBOX_HEIGHT 27*3

#define MARIO_BIG_SITDOWN_BBOX_WIDTH  14*3
#define MARIO_BIG_SITDOWN_BBOX_HEIGHT 19*3

#define MARIO_SMALL_BBOX_WIDTH  13*3
#define MARIO_SMALL_BBOX_HEIGHT 15*3

#define MARIO_BIG_TAIL_BBOX_WIDTH  21*3
#define MARIO_BIG_TAIL_BBOX_HEIGHT 28*3

#define MARIO_BIG_TAIL_SPIN_BBOX_WIDTH  45*3


#define MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH  22*3
#define MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT 19*3




#define MARIO_UNTOUCHABLE_TIME 5000



class CMario : public CGameObject
{
public:
	int level;
	int untouchable;
	float acceleration= MARIO_ACCELERATION;
	CGameObject* hold_somthing = NULL;

	DWORD untouchable_start;
	DWORD jumping_start;
	
	bool is_on_the_ground = false;

	bool is_in_object = false;
	bool is_sitdown = false;
	bool is_shoot = false;
	bool is_spin = false;
	bool is_slightly_lower_limit = false; // đã đến lúc giảm tốc
	bool is_right = false;
	bool is_left = false;
	bool is_skid = false;
	bool is_max_speed = false;
	bool is_walking = false;
	bool is_press_z = false;
	bool is_slightly_lower_than_zero = false;
	bool is_press_left = false;
	bool is_brouse = false;
	bool is_press_h = false;
	bool is_fly = false;
	bool is_fly_short = false;
	bool is_fly_high = false;
	bool is_bring = false;
	bool is_increase_speed = false;
	bool is_run_for_fly_high = false;

public: 
	CMario() : CGameObject()
	{
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		nx = 1;
	}
	void CheckOverlapWithItems(vector<LPGAMEOBJECT>* itemsMarioCanEat);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetIsInObject(bool temp) { is_in_object = temp; }
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetShoot(bool temp) { is_shoot = temp; }
	void SetSpin(bool temp) { is_spin = temp; }
	void SetIsFly(bool temp) { is_fly = temp; }
	void SetIsBring(bool temp) { is_bring = temp; }
	void SetIsIncreaseSpeed(bool temp) { is_increase_speed = temp; }
	void SetAcceleration(float temp) { acceleration = temp; }

	void StartJumping() { jumping_start = GetTickCount64(); };
	void EndJumping() { jumping_start = 0; };
	DWORD GetJumpingTime() { return jumping_start; };
	bool GetIsInObject() { return is_in_object; };
	int GetLevel() { return level; };
	bool GetIsShoot() { return is_shoot; };
	bool GetIsSpin() { return is_spin; };
	bool GetIsFly() { return is_fly; };
	bool GetIsBring() { return is_bring; };
	bool GetIsIncreaseSpeed() { return is_increase_speed; }
	float GetAcceleration() { return acceleration; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};