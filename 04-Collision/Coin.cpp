#include "Coin.h"

void Coin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + COIN_BBOX_WIDTH;
	bottom = y + COIN_BBOX_HEIGHT;
}


void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Coin::Render()
{
	int ani = 0;
	animations[ani]->Render(x, y);
}

void Coin::SetState(int state)
{
}
