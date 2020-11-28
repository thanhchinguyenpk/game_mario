#pragma once
#include "GameObject.h"

#define SWITCH_BLOCK_BBOX_WIDTH 16*3
#define SWITCH_BLOCK_BBOX_HEIGHT 16*3

#define SWITCH_BLOCK_STATE_WAS_PRESSED 100


class SwitchBlock :public CGameObject
{
public:

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
};

