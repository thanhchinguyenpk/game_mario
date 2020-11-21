#include "ConCo.h"
#include "Game.h"
#include "debug.h"
#include "Flatform.h"



void CConCo::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x- (float)CONCO_BBOX_WIDTH/2;
	top = y- (float)CONCO_BBOX_HEIGHT/2;
	right = x + (float)CONCO_BBOX_WIDTH/2;

	if (state == CONCO_STATE_DIE) // chua ok
		bottom = y + (float)CONCO_BBOX_HEIGHT_DIE/2;
	else
		bottom = y + (float)CONCO_BBOX_HEIGHT/2;

	if (state == CONCO_STATE_THUT_VAO||state==CONCO_STATE_MAI_RUA_CHAY)
	{
		left = x - (float)16*3/2;// ủa tại sao để define thì lại lỗi ????
		top = y - (float)17*3/2;
		right = x + (float)16*3/2;
		bottom = y + (float)17*3/2;
	}
}

void CConCo::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	if (is_brought == false)
	{
		CGameObject::Update(dt, coObjects);
	}

	vy += 0.002 * dt;

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	//x += dx;
	//y += dy;



	/*if (vx < 0 && x < 250) { // tai sao
		if (state == CONCO_STATE_MAI_RUA_CHAY) // mai rùa chạy thì kệ nó
			state = CONCO_STATE_MAI_RUA_CHAY;
		else if(state==CONCO_STATE_WALKING_LEFT){ // tới biên qua bên trái thì đi ngược chiều lại
			state = CONCO_STATE_WALKING_RIGHT;
		}
		else if (state == CONCO_STATE_FLY_LEFT)
			state = CONCO_STATE_FLY_RIGHT;

		x = 250; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		if (state == CONCO_STATE_MAI_RUA_CHAY) // mai rùa chạy thì kệ nó
			state = CONCO_STATE_MAI_RUA_CHAY;
		else if (state == CONCO_STATE_WALKING_RIGHT) { // tới biên qua bên trái thì đi ngược chiều lại
			state = CONCO_STATE_WALKING_LEFT;
		}
		else if (state == CONCO_STATE_FLY_RIGHT)
			state = CONCO_STATE_FLY_LEFT;
	//	state = CONCO_STATE_WALKING_LEFT;
		x = 290; vx = -vx;

		
	}*/




	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();


	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0|| state==CONCO_STATE_WAS_SHOOTED)
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
			//vx = 0;
			vx = 0;
		/*	if (state == CONCO_STATE_WALKING_LEFT)
			{
				SetState(CONCO_STATE_WALKING_RIGHT);
				//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] cham dau quay qua phải. Error: \n");
			}
			else if (state == CONCO_STATE_WALKING_RIGHT)
			{
				SetState(CONCO_STATE_WALKING_LEFT);
				//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] cham dau quay qua trái. Error: \n");
			}*/
		}// tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
		if (ny != 0)
		{
			//DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] co nhay vo phuong DOC Error: \n");
			vy = 0; // sẽ bị chặn lại_ không đúng má ơi.
		}



		//int boQuaVienDaDongTienDauTienAnNap = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];



			if (dynamic_cast<Flatform*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
			{

				Flatform* flatform = dynamic_cast<Flatform*>(e->obj);

				if (this->x > flatform->x + 243)
					SetState(CONCO_STATE_WALKING_LEFT);
				if(this->x < flatform->x)
					SetState(CONCO_STATE_WALKING_RIGHT);
				
				
			}
			// biến bỏ qua viên đá đồng tiền đầu tiên là để bỏ qua viên đá mà con 
			//nấm chui ra
			

				//vx = -vx;
				//if (nx != 0)
				//{
				//	if (nx < 0)
				//	{
						//vx = 0;
				//		DebugOut(L"[ERROR~~~~~~~~~~~~~cham phia tren trai~~~~~~~~~~~~~~~~] co nhay vo phuong ngang. Error: \n");
				//		DebugOut(L"[ERROR-------------VY*----------------] DINPUT::GetDeviceData failed. Error: %f\n", vy);
				//	}
				//}

			}

		}

		//}
		//vx = MUSHROOM_WALKING_SPEED;// cẩn thận nha, xem lại kĩ càng

		//vx = 0; vy = 0;





	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CConCo::Render()
{
	/*int ani = CONCO_ANI_WALKING_LEFT;
	if (state == CONCO_STATE_DIE) { //chua ok
		ani = CONCO_ANI_DIE;
	}
	else if (state == CONCO_STATE_WALKING_RIGHT)
	{
		ani = CONCO_ANI_WALKING_RIGHT;
	}
	else if (state == CONCO_STATE_THUT_VAO)
	{
		ani = CONCO_ANI_THUT_VAO;
	}
	else if (state == CONCO_STATE_MAI_RUA_CHAY)
	{
		ani = CONCO_ANI_MAI_RUA_CHAY;
	}
	else if (state == CONCO_STATE_FLY_LEFT)
	{
		ani = CONCO_ANI_FLY_LEFT;
	}
	else if (state == CONCO_STATE_FLY_RIGHT)
	{
		ani = CONCO_ANI_FLY_RIGHT;
	}
	else if (state == CONCO_STATE_WALKING_RIGHT)
	{
		ani = CONCO_ANI_WALKING_RIGHT;
	}
	*/
	int ani = CONCO_ANI_WALKING_RIGHT;
	if (state == CONCO_STATE_WALKING_RIGHT)
		ani = CONCO_ANI_WALKING_RIGHT;
	else if (state == CONCO_STATE_THUT_VAO||state==CONCO_STATE_WAS_SHOOTED)
		ani = CONCO_ANI_THUT_VAO;
	else if (state == CONCO_STATE_MAI_RUA_CHAY)
		ani = CONCO_ANI_MAI_RUA_CHAY;
	//int ani = CONCO_ANI_THUT_VAO;
	DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", nx);
	animations[ani]->Render(x, y,0,255,nx,ny);
	RenderBoundingBox();
}

void CConCo::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		y += CONCO_BBOX_HEIGHT - CONCO_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx =  -CONCO_WALKING_SPEED;
		nx = -1;
		break;
	case CONCO_STATE_WALKING_RIGHT:
		vx = CONCO_WALKING_SPEED;
		nx = 1;
		break;
	case CONCO_STATE_THUT_VAO:
		vx = 0;
		vy = 0;
		nx = 1;
		//y = 135;
		break;
	case CONCO_STATE_MAI_RUA_CHAY:
		vx = 8*CONCO_MAI_RUA_CHAY_SPEED;
		break;
	case CONCO_STATE_FLY_LEFT:
		vx = -CONCO_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = CONCO_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;// 0.1f * 1.5;
		vy = 0;
		//nx = 1;
		break;
	case CONCO_STATE_WAS_SHOOTED:
		vx = -vx;// 0.1f * 1.5;
		vy = -0.25*3;
		ny = -1;
		//nx = 1;
		break;
	}
}

