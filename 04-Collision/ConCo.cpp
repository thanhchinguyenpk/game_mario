#include "ConCo.h"
#include "Game.h"
#include "debug.h"



void CConCo::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CONCO_BBOX_WIDTH;

	if (state == CONCO_STATE_DIE) // chua ok
		bottom = y + CONCO_BBOX_HEIGHT_DIE;
	else
		bottom = y + CONCO_BBOX_HEIGHT;
}

void CConCo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 250) { // tai sao
		if (state == CONCO_STATE_MAI_RUA_CHAY) // mai rùa chạy thì kệ nó
			state = CONCO_STATE_MAI_RUA_CHAY;
		else if(state==CONCO_STATE_WALKING_LEFT){ // tới biên qua bên trái thì đi ngược chiều lại
			state = CONCO_STATE_WALKING_RIGHT;
		}
		else if (state == CONCO_STATE_FLY_LEFT)
			state = CONCO_STATE_FLY_RIGHT;
	//	state = CONCO_STATE_WALKING_RIGHT;

		x = 250; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		/*if(state== CONCO_STATE_MAI_RUA_CHAY)
			state == CONCO_STATE_MAI_RUA_CHAY;
		else{
			
			state = CONCO_STATE_WALKING_LEFT;
		}*/
		if (state == CONCO_STATE_MAI_RUA_CHAY) // mai rùa chạy thì kệ nó
			state = CONCO_STATE_MAI_RUA_CHAY;
		else if (state == CONCO_STATE_WALKING_RIGHT) { // tới biên qua bên trái thì đi ngược chiều lại
			state = CONCO_STATE_WALKING_LEFT;
		}
		else if (state == CONCO_STATE_FLY_RIGHT)
			state = CONCO_STATE_FLY_LEFT;
	//	state = CONCO_STATE_WALKING_LEFT;
		x = 290; vx = -vx;

		
	}
}

void CConCo::Render()
{
	int ani = CONCO_ANI_WALKING_LEFT;
	if (state == CONCO_STATE_DIE) { //chua ok
		ani = CONCO_ANI_DIE;
	}
	else if (state == CONCO_STATE_WALKING_RIGHT)
	{
		ani = CONCO_ANI_WALKING_RIGHT;
	}
	else if (state == CONCO_STATE_THUT_VAO)
	{
		ani = CONCO_ANI_THUT_VAO;
	}
	else if (state == CONCO_STATE_MAI_RUA_CHAY)
	{
		ani = CONCO_ANI_MAI_RUA_CHAY;
	}
	else if (state == CONCO_STATE_FLY_LEFT)
	{
		ani = CONCO_ANI_FLY_LEFT;
	}
	else if (state == CONCO_STATE_FLY_RIGHT)
	{
		ani = CONCO_ANI_FLY_RIGHT;
	}
	else if (state == CONCO_STATE_WALKING_RIGHT)
	{
		ani = CONCO_ANI_WALKING_RIGHT;
	}
	//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", ani);
	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void CConCo::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		y += CONCO_BBOX_HEIGHT - CONCO_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx = -CONCO_WALKING_SPEED;
		nx = -1;
		break;
	case CONCO_STATE_WALKING_RIGHT:
		vx = CONCO_WALKING_SPEED;
		nx = 1;
		break;
	case CONCO_STATE_THUT_VAO:
		vx = 0;
		vy = 0;
		nx = 0;
		y = 135;
		break;
	case CONCO_STATE_MAI_RUA_CHAY:
		vx = CONCO_MAI_RUA_CHAY_SPEED;
		break;
	case CONCO_STATE_FLY_LEFT:
		vx = -CONCO_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = CONCO_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;

	}
}

