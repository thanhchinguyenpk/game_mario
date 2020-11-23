#include "ParaGoomba.h"

void ParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PARA_GROOMBA_BBOX_WIDTH / 2;
	t = y - PARA_GROOMBA_BBOX_HEIGHT / 2;
	r = x + PARA_GROOMBA_BBOX_WIDTH / 2;
	b = y + PARA_GROOMBA_BBOX_HEIGHT / 2;
}

void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vy += PARA_GROOMBA_GRAVITY * dt;

	//x += dx;
	//y += dy;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = -vx;

		if (ny != 0)
		{
			if (GetTickCount64() - moving_time > 1200 && turn_on_moving == true)
			{
				SetState(PARA_GROOMBA_STATE_JUMP_SMALL);
				turn_on_moving = false;
				count++;
			}
			else if(state== PARA_GROOMBA_STATE_JUMP_BIG|| state== PARA_GROOMBA_STATE_JUMP_SMALL)
			{
				if (count % 5 == 0)
					SetState(PARA_GROOMBA_STATE_JUMP_BIG);
				else if(count %5==1)
					vx > 0 ? SetState(PARA_GROOMBA_STATE_MOVE_RIGHT): SetState(PARA_GROOMBA_STATE_MOVE_LEFT);
				else
					SetState(PARA_GROOMBA_STATE_JUMP_SMALL);

				count++;
			}
		

		}	






		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];



			/*if (dynamic_cast<Flatform*>(e->obj)) 
			{

				Flatform* flatform = dynamic_cast<Flatform*>(e->obj);

				if (this->x > flatform->x + 243)
					SetState(CONCO_STATE_WALKING_LEFT);
				if (this->x < flatform->x)
					SetState(CONCO_STATE_WALKING_RIGHT);
			}*/

		}

	}




	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void ParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_GROOMBA_STATE_MOVE_RIGHT:
		vx = PARA_GROOMBA_WALKING_SPEED;
		//vy = 0;
		turn_on_moving = true;
		moving_time = GetTickCount64();
		break;
	case PARA_GROOMBA_STATE_MOVE_LEFT:
		vx = -PARA_GROOMBA_WALKING_SPEED;
		turn_on_moving = true;
		moving_time = GetTickCount64();
		break;
	case PARA_GROOMBA_STATE_JUMP_SMALL:
		vy = -0.2;
		break;
	case PARA_GROOMBA_STATE_JUMP_BIG:
		vy = -0.35;
		break;
	}
}

void ParaGoomba::Render()
{
	int ani = 0;
	int direction = 1;
	int ny = 1;

	if (state == PARA_GROOMBA_STATE_JUMP_SMALL && vy > 0|| state == PARA_GROOMBA_STATE_JUMP_BIG && vy > 0)
		ani = PARA_GROOMBA_ANI_JUMP_SMALL;
	else if(state == PARA_GROOMBA_STATE_JUMP_BIG && vy <= 0)
		ani = PARA_GROOMBA_ANI_JUMP_BIG;

	animations[ani]->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

ParaGoomba::ParaGoomba()
{
	 vx = -PARA_GROOMBA_WALKING_SPEED;
}
