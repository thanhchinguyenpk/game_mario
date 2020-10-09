#pragma once
#include "GameObject.h"

#define BRICK_COIN_BBOX_WIDTH  16
#define BRICK_COIN_BBOX_HEIGHT 16

#define BRICK_COIN_STATE_CHUA_DAP	100
#define BRICK_COIN_STATE_DA_DAP 	200


#define BRICK_COIN_ANI_CHUA_DAP	 0
#define BRICK_COIN_ANI_DA_DAP	 1


class Brick_Coin : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void SetState(int state);
};
