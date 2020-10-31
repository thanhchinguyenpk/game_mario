﻿#include "Goomba.h"
#include "debug.h"
#include "MarioBullet.h"
#include "Flatform.h"

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	//x += dx;
	//y += dy;

	vy += GOOMBA_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();


	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx; // quãng đường di chuyển thực sự trong frame , nếu như k có va chạm
		y += dy;
	}
	else // trong trường hợp có va chạm xẩy ra
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// filter đối tượng trên từng trục để xử lí va chạm

		// block // đẩy lùi ra so với chiều của các hướng bị va chạm, 0.4f là tránh bị trùng mép
		
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;
		

		if (nx != 0)
		{
			vx = 0;
		//	DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] co nhay vo phuong ngang. Error: \n");
			//delete this;
		}// tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
		if (ny != 0)
		{
			//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] co nhay vo phuong DOC Error: \n");
			 // sẽ bị chặn lại_ không đúng má ơi.

			vy = 0;

			// tý dùng
			//vy = -0.25 * 3;
		}



		//int boQuaVienDaDongTienDauTienAnNap = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];
			

			//delete nó đi nè :D
			if (dynamic_cast<Flatform*>(e->obj) && state == GOOMBA_STATE_WAS_SHOOTED)
			{
				

			}
	
				/*	if (dynamic_cast<MarioBullet*>(e->obj))
					{
						SetState(GOOMBA_STATE_WAS_SHOOTED);
						//SetPosition(x, y - 20);
						DebugOut(L"[ERROR~~~~~~~~~~~~~~~~CO BAO GIO NHAY VO DAY k: \n");
					}
					*/

			

		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	/*	if (state == GOOMBA_STATE_WAS_SHOOTED)
	{
		y += 20;
	}
	*/
}

void CGoomba::Render()
{
	//int ny = 1;

	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	else if (state == GOOMBA_STATE_WAS_SHOOTED)
	{
		ani = GOOMBA_ANI_WAS_SHOOTED;
		ny = -1;
	}

	int alpha = 255;
	animations[ani]->Render(x, y, 0, alpha, nx,ny);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = GOOMBA_WALKING_SPEED;
			//vx = 0;
			//vy = 0;
			break;
		case GOOMBA_STATE_WAS_SHOOTED:
			vy = -0.25 * 3;
			//vx = vx;
			ny = -1;
			break;
	}
}
