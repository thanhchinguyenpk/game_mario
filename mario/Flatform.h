#pragma once
#include "GameObject.h"
#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

class Flatform : public CGameObject
{
public:
	float width;
	float height;
	bool is_portal = false;

	Flatform(float Width, float Height) { width = Width; height = Height; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};