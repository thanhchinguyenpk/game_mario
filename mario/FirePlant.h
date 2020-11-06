#pragma once
#include "GameObject.h"

#define FIRE_PLANT_BBOX_WIDTH  10
#define FIRE_PLANT_BBOX_HEIGHT 10




class FirePlant : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};