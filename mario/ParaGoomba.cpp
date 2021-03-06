﻿#include "ParaGoomba.h"
#include "Mario.h"
#include "Flatform.h"
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
			// nếu mà <1200s thì đi á còn lớn thì set cho nó nhảy nhỏ
			
			vy = 0;

		}	

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Flatform*>(e->obj))
			{
				if (state == PARA_GROOMBA_STATE_WALKING|| state == PARA_GROOMBA_STATE_DIE)
				{
					//vx = -vx;
				}
				else if (GetTickCount64() - moving_time > 500) //ban đầu chưa set thời gian này thì if chắc chắc đúng
				{

					if (count % 6 == 0)
						SetState(PARA_GROOMBA_STATE_JUMP_BIG);
					else if (count % 6 == 1)
						vx > 0 ? SetState(PARA_GROOMBA_STATE_MOVE_RIGHT) : SetState(PARA_GROOMBA_STATE_MOVE_LEFT);
					else if (count % 6 == 2)
					{
						if (mario->x > this->x)
							SetState(PARA_GROOMBA_STATE_MOVE_RIGHT);
						else if (mario->x < this->x)
							SetState(PARA_GROOMBA_STATE_MOVE_LEFT);
					}
					else
						SetState(PARA_GROOMBA_STATE_JUMP_SMALL);

					count++;
				}
			}

		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (time_to_disapear->IsTimeUp())
		used = true;

	DebugOut(L"[ERROR-------------state----------------] DINPUT::GetDeviceData failed. Error: %d\n",state);
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
		vy = -0.13;
		break;
	case PARA_GROOMBA_STATE_JUMP_BIG:
		vy = -0.4;
		break;
	case PARA_GROOMBA_STATE_WALKING:
		//vy = 0;
		break;
	case PARA_GROOMBA_STATE_DIE:
		vy = 0;
		vx = 0;
		time_to_disapear->StartTime();
		break;


		
	}
}

void ParaGoomba::Render()
{
	int ani = PARA_GROOMBA_ANI_MOVE;
	int direction = 1;
	int ny = 1;

	if (state == PARA_GROOMBA_STATE_JUMP_SMALL && vy > 0|| state == PARA_GROOMBA_STATE_JUMP_BIG && vy > 0)
		ani = PARA_GROOMBA_ANI_JUMP_SMALL;
	else if(state == PARA_GROOMBA_STATE_JUMP_BIG && vy <= 0)
		ani = PARA_GROOMBA_ANI_JUMP_BIG;
	
	if (state == PARA_GROOMBA_STATE_WALKING)
		ani = PARA_GROOMBA_ANI_WALKING;

	if (state == PARA_GROOMBA_STATE_DIE)
		ani = PARA_GROOMBA_ANI_DIE;

	animations[ani]->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

ParaGoomba::ParaGoomba()
{	
	vx = -PARA_GROOMBA_WALKING_SPEED;
}
