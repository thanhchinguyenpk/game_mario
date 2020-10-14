#include "MarioBullet.h"



void MarioBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIOBULLET_BBOX_WIDTH;

	if (state == MARIOBULLET_STATE_DIE)
		bottom = y + MARIOBULLET_BBOX_HEIGHT_DIE;
	else
		bottom = y + MARIOBULLET_BBOX_HEIGHT;
}

void MarioBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIOBULLET_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear(); // ủa tại sao ở dưới delete rồi mà ở đây lại clear nữa?

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	// tính ra danh sách các đối tượng có khả năng va chạm với mario


	// reset untouchable timer if untouchable time has passed




	// No collision occured, proceed normally
	// nếu như không có bất cứ va chạm nào
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
		}; // tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
		if (ny != 0) vy = -0.25;// sẽ bị chặn lại_ không đúng má ơi.



	}
}

void MarioBullet::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}

	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void MarioBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_FLY_RIGHT:
		vx = GOOMBA_WALKING_SPEED;
		break;
	case BULLET_STATE_FLY_LEFT:
		vx = -GOOMBA_WALKING_SPEED;
		break;
		//vy = 0.07;
	}
}

