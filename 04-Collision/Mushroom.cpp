#include "Mushroom.h"
#include "Brick_Coin.h"
#include "debug.h"
#include "Brick.h"
extern vector<LPGAMEOBJECT> objects;

int boQuaVienDaDongTienDauTienAnNap = 0;

void Mushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MUSHROOM_BBOX_WIDTH;
	bottom = y + MUSHROOM_BBOX_HEIGHT;

}

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
//	DebugOut(L"[ERROR-------------VX-----------------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
	//DebugOut(L"[ERROR-------------VY-----------------] DINPUT::GetDeviceData failed. Error: %f\n", vy);

	//DebugOutTitle(L"vi tri cua con nammmmmmmmm %0.001f, %0.001f", this->vx, this->vy);
	if (GetTickCount() - time_go_out_brick < 320)
	{
		//vy = MUSHROOM_WALKING_SPEED;
		
		y -= dy;
	}
	else {

		

		vy += 0.002 * dt;
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
				//vx = 0;
				DebugOut(L"[ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~] co nhay vo phuong ngang. Error: \n");
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
				

				if (boQuaVienDaDongTienDauTienAnNap == 1 && dynamic_cast<Brick_Coin*>(e->obj))
				{
					vx = -vx;
					//DebugOut(L"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& %f\n", vy);
				}
				if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
				{
					boQuaVienDaDongTienDauTienAnNap = 1;

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





		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	

	

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}*/
		
	
}

void Mushroom::Render()
{
	int ani = MUSHROOM_ANI_WALKING;

	animations[ani]->Render(x, y);
}

void Mushroom::SetState(int state)
{

	CGameObject::SetState(state);
	vy = MUSHROOM_WALKING_SPEED;// nguen nhan la do hang nayyyyyyyyyyyyyyyyyyy
	//tại vì hàm sweepAABB giữa 2 vật chuyển động phải trừ vy(để lấy một vật làm mốc)
	// chình vì thế khi cập nhật vy thì sẽ ảnh hưởng đến hàm sweepAABB , vì vậy con mario 
	// sẽ đi ngang qua con nấm luôn :((
	vx = MUSHROOM_WALKING_SPEED;
	/*switch (state)
	{
	case MUSHROOM_STATE_DIE:
		y += MUSHROOM_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = -MUSHROOM_WALKING_SPEED;
	}*/
}

Mushroom::Mushroom()
{
	
	this->AddAnimation(11001);
	this->SetPosition(100.0f, 90.0f);//100,90
	this->SetState(100);  // cais nayf chuwa nha


	/*Brick_Coin* brc = new Brick_Coin();
	brc->AddAnimation(1001);
	brc->AddAnimation(1002);
	brc->SetPosition(180.0f, 90.0f);
	objects.insert(objects.begin() + 1, brc);**/

	this->time_go_out_brick = GetTickCount();
}
