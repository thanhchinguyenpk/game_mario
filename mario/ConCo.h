#pragma once
#include "GameObject.h"

#define CONCO_WALKING_SPEED			 0.05f;
#define CONCO_MAI_RUA_CHAY_SPEED	 0.1f;

#define CONCO_BBOX_WIDTH		 16*3 //ok
#define CONCO_BBOX_HEIGHT		 27*3 //ok
#define CONCO_BBOX_HEIGHT_DIE	 9
#define CONCO_BBOX_WIDTH_THUT_VAO 15*3;
#define CONCO_BBOX_HEIGHT_THUT_VAO 17*3;

#define CONCO_STATE_WALKING_LEFT	100
#define CONCO_STATE_DIE				200
#define CONCO_STATE_WALKING_RIGHT	300
#define CONCO_STATE_THUT_VAO		400
#define CONCO_STATE_MAI_RUA_CHAY	500
#define CONCO_STATE_FLY_LEFT	    600
#define CONCO_STATE_FLY_RIGHT	    700
#define CONCO_STATE_WAS_BROUGHT	    800
#define CONCO_STATE_WAS_SHOOTED		900
#define CONCO_STATE_INDENT_OUT		1000
#define CONCO_STATE_SHELL_MOVING		1100

#define CONCO_ANI_WALKING_LEFT	 0
#define CONCO_ANI_WALKING_RIGHT	 1
#define CONCO_ANI_THUT_VAO		 2
#define CONCO_ANI_MAI_RUA_CHAY	 3
#define CONCO_ANI_FLY_LEFT	    4
#define CONCO_ANI_FLY_RIGHT	    5
//#define CONCO_ANI_DIE			 6
#define CONCO_ANI_INDENT_OUT			6
#define CONCO_ANI_SHELL_MOVING			7

#define CONCO_GRAVITY			0.002f*1.5

class CConCo : public CGameObject
{
public:
	bool is_brought = false;
	DWORD time_to_indent_out;
	bool shell_moving = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	virtual void SetState(int state);
};
