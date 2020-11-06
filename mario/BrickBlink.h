#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16*3
#define BRICK_BBOX_HEIGHT 16*3

class BrickBlink : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};