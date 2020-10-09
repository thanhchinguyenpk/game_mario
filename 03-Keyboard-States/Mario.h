#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_GRAVITY			0.025f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300

#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3


#define CONCO_WALKING_SPEED		0.1f
#define CONCO_JUMP_SPEED_Y		0.5f
#define CONCO_GRAVITY			0.025f

#define CONCO_STATE_IDLE			0
#define CONCO_STATE_WALKING_RIGHT	100
#define CONCO_STATE_WALKING_LEFT	200
#define CONCO_STATE_JUMP			300

#define CONCO_ANI_IDLE_RIGHT		4
#define CONCO_ANI_IDLE_LEFT			5
#define CONCO_ANI_WALKING_RIGHT		6
#define CONCO_ANI_WALKING_LEFT		7

class CMario : public CGameObject
{
public: 

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

class CConCo : public CGameObject
{
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};