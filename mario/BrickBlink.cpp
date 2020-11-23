#include "BrickBlink.h"
#include "DebrisBrick.h"

extern vector<LPGAMEOBJECT> objects;

void BrickBlink::Render()
{
	int direction = 1;
	int ny = 1;
	animations[0]->Render(x, y, 0, 255, direction, ny);
	//RenderBoundingBox();
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BLINK_BBOX_WIDTH/2;
	t = y - BRICK_BLINK_BBOX_HEIGHT/2;
	r = x + BRICK_BLINK_BBOX_WIDTH/2;
	b = y + BRICK_BLINK_BBOX_HEIGHT/2;
}

void BrickBlink::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_BLINK_STATE_WAS_HIT:

		

		float pos_x = this->x;
		float pos_y = this->y;

		DebrisBrick* debrick_brick=NULL;

		debrick_brick = new DebrisBrick(pos_x + DEBRIS_DISTANCE, pos_y - DEBRIS_DISTANCE, 1, 1.5);
		objects.push_back(debrick_brick);


		debrick_brick = new DebrisBrick(pos_x + DEBRIS_DISTANCE, pos_y + DEBRIS_DISTANCE, 1, 1);
		objects.push_back(debrick_brick);


		debrick_brick = new DebrisBrick(pos_x - DEBRIS_DISTANCE, pos_y + DEBRIS_DISTANCE, -1, 1);
		objects.push_back(debrick_brick);

		debrick_brick = new DebrisBrick(pos_x - DEBRIS_DISTANCE, pos_y - DEBRIS_DISTANCE, -1, 1.5);
		objects.push_back(debrick_brick);

		used = true;
		break;
	}

}

BrickBlink::BrickBlink()
{
}
