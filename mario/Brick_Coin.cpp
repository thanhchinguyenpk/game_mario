#include "Brick_Coin.h"
#include <dinput.h>
#include "debug.h"

void Brick_Coin::Render()
{
	int ani = 0;
	if (state == BRICK_COIN_STATE_DA_DAP)
	{
		ani = 1;
	}
	//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", ani);


	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void Brick_Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_COIN_BBOX_WIDTH;
	b = y + BRICK_COIN_BBOX_HEIGHT;
}

void Brick_Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Brick_Coin::SetState(int state)
{

	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_COIN_ANI_DA_DAP:
		x = 100;
		y = 100;
		break;
	
	}

}
