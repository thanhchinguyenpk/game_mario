#pragma once
#include "GameObject.h"


class Pmeter :public CGameObject
{
public:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	//virtual void SetState(int state);
	virtual void Render();
};

