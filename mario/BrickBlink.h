#pragma once
#include "GameObject.h"

#define BRICK_BLINK_BBOX_WIDTH  16*3
#define BRICK_BLINK_BBOX_HEIGHT 16*3

#define BRICK_BLINK_STATE_WAS_HIT 1

#define DEBRIS_DISTANCE 9


#define  BRICK_BLINK_STATE_MOVE_LEFT		100 // chỗ này chưa
#define  BRICK_BLINK_STATE_MOVE_RIGHT	200

class BrickBlink : public CGameObject
{
	vector<LPGAMEOBJECT> vec_debris;

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	BrickBlink();
};