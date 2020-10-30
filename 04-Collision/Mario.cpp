#include <algorithm>
#include "debug.h" 

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "ConCo.h"
#include "Brick_Coin.h"

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"


#include "Brick.h"
#include "Goomba.h"
#include "ConCo.h"
#include "Brick_Coin.h"
#include "Coin.h"
#include "CoinFly.h"
#include "Mushroom.h"
#include "Flatform.h"




extern vector<LPGAMEOBJECT> objects;



void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject* temp =NULL;

	float x_flatform = 0;
	float y_flatform = 0;

	float vy_flatform = 0;

	DebugOutTitle(L"04 - collision %0.1f, %0.1f", this->x, this->y);
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	
	

	if (is_fly==true)//còn render
	{
		if(!(GetState() == MARIO_STATE_FLY && animations[MARIO_ANI_FLY]->IsRenderDone()))
		vy = 0.1;
	}
	else
	{
		vy += MARIO_GRAVITY * dt;
	}

	
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear(); // ủa tại sao ở dưới delete rồi mà ở đây lại clear nữa?

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	// tính ra danh sách các đối tượng có khả năng va chạm với mario


	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (GetTickCount() - jumping_start < 250) //  < ấn nhẹ thì nó bay thấp, ấn mạnh thì nó bay cao.
	{											// > ấn nhẹ nhảy cao , ấn mạnh nhảy thấp.
		vy -= 0.02f*2;
		//DebugOut(L"[ERROR-----------get-------------------] DINPUT::GetDeviceData failed. Error: %lu\n", GetTickCount());
	}

	// No collision occured, proceed normally
	// nếu như không có bất cứ va chạm nào
	if (coEvents.size()==0)
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
	
		x_flatform = min_tx * dx + nx * 0.4f;
		y_flatform = min_ty * dy + ny * 0.4f;

		vy_flatform = vy;
		
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0; // tại sao lại có hai dòng này- theo mình nghĩ là té từ trên cao xuống thì
		if (ny!=0) vy = 0; // sẽ bị chặn lại_ không đúng má ơi.

	

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			

			//DebugOut(L"[EEEEEEEEEEEEEEE] DINPUT::GetDeviceData failed. Error: %d\n", coEventsResult.size());
			LPCOLLISIONEVENT e = coEventsResult[i];


			if (ny < 0)
			{
				is_in_object = true;
			}

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba // nếu như là goomba
			{
				
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
				
				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0) //nêu như phương va chạm hướng lên ( lưu ý trục y hướng xuống)
					// thì cho phép đạp bẹp
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0) // vec tơ pháp tuyến từ bên trái qua, từ bên phải xuống
				{		// thì làm mario rớt level, bất tử hoặc chết
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
			if (dynamic_cast<CConCo*>(e->obj))
			{
				/*CConCo* conco = dynamic_cast<CConCo*>(e->obj);
				if (e->ny < 0) // phương va chạm hướng lên (con cò)
				{
					if (conco->GetState() == CONCO_STATE_THUT_VAO)// nếu đang chạy sẽ thụt vào,else cuối
					{
						conco->SetState(CONCO_STATE_MAI_RUA_CHAY);
						
					}
					else if (conco->GetState()==CONCO_STATE_FLY_LEFT|| 
						conco->GetState() == CONCO_STATE_FLY_RIGHT)
					{
						if (conco->nx < 0)
							conco->SetState(CONCO_STATE_WALKING_LEFT);
						else if (conco->nx > 0)
							conco->SetState(CONCO_STATE_WALKING_RIGHT);
					}
					
					else{
						//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", conco->GetState());
						conco->SetState(CONCO_STATE_THUT_VAO);
						 // chữa cháy thôi, phải búng ra chứ nhỉ
					}
					vy = -MARIO_JUMP_DEFLECT_SPEED;			
				}*/

				if (state == MARIO_STATE_BRING_KOOMPA)
				{
					CConCo* conco = dynamic_cast<CConCo*>(e->obj);

					DebugOut(L"[ERROR-------------cua con co là---------------] DINPUT::GetDeviceData failed. Error: %d\n", conco->GetState());
					if (this->nx > 0)
					{
						//conco->SetPosition(x + 45.8f, y);
						conco->SetState(CONCO_STATE_WAS_BROUGHT);
						DebugOut(L"[ERROR-------------nx>0---------------] DINPUT::GetDeviceData failed. Error: %d\n");
						
						is_bring = true;
						temp = conco;
					}
					else {

						conco->SetPosition(x - 55.0f, y);
						DebugOut(L"[ERROR-------------nx<0---------------] DINPUT::GetDeviceData failed. Error: %d\n");
					}
				}
			}


			if (dynamic_cast<Brick_Coin*>(e->obj))
			{
				Brick_Coin* brickcoin = dynamic_cast<Brick_Coin*>(e->obj);
				if (e->ny > 0) // phương va chạm hướng lên
				{
					if (brickcoin->GetState() == BRICK_COIN_STATE_CHUA_DAP)
					{
						brickcoin->SetState(BRICK_COIN_STATE_DA_DAP);

						Mushroom* mushroom = new Mushroom();
						objects.insert(objects.begin()+2, mushroom);



					}
				

				}


			}

			

			if (dynamic_cast<Flatform*>(e->obj)) {
				if (e->ny > 0) // hướng xuống
				{
					y +=( y_flatform + y_flatform);// double for safe
					vy = vy_flatform;
				}
			}

		}
	}

	//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", y);

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	

	if (GetState() == MARIO_STATE_SPIN && animations[39]->IsRenderDone())
	{
		SetState(MARIO_STATE_IDLE);
		SetSpin(false);
		is_render_animation = false;
	}
	if (GetState() ==  MARIO_STATE_SHOOT_BULLET && animations[MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT]->IsRenderDone())
	{
		SetState(MARIO_STATE_IDLE);
		is_render_animation = false;
	}


	if (GetState() ==  MARIO_STATE_JUMP_SHOOT_BULLET && animations[MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT]->IsRenderDone())
	{
		SetState(MARIO_STATE_IDLE);
		is_render_animation = false;
	}
	if (GetState() == MARIO_STATE_FLY && animations[MARIO_ANI_FLY]->IsRenderDone())
	{
		SetState(MARIO_STATE_IDLE);
		is_render_animation = false;
		//DebugOut(L"Hello , vo day khong???\n");
		is_fly = false;
	}


//	DebugOut(L"stae cua mario la: %d\n", GetState());
	//if (is_shoot == true)
	//	is_shoot == false;

	//DebugOutTitle(L"vi tri cua con marioooooooooooooooo %0.001f, %0.001f", this->vx, this->vy);
	if(is_bring==true)
		temp->SetPosition(x+50, y);

}

void CMario::Render()
{
	int ani=0;
	if (state == MARIO_STATE_DIE)
	{
		ani = MARIO_ANI_DIE;
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		if (is_in_object == true)
		{
			if(is_sitdown==false) // trên object thì nó mới sitdown được, if bên ngoài
			{
				if (vx == 0) //nếu đứng yên
						ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else  //nếu di chuyển trái
				    	ani = MARIO_ANI_BIG_WALKING_RIGHT;
			}
			else 
				ani = MARIO_ANI_BIG_SITDOWN_RIGT;	
		}
		else if (is_in_object == false)
		{
			ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
			if (vy < 0.0f) //fall down
					ani = MARIO_ANI_BIG_JUMP_UP_LEFT; // mới thêm zô
		}
	
	
	}
	else if (level == MARIO_LEVEL_BIG_ORANGE)
	{
		if (is_in_object == true)
		{
			if (is_sitdown == false) // trên object thì nó mới sitdown được, if bên ngoài
			{
				if (state== MARIO_STATE_SHOOT_BULLET)
						ani = MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT;
				else
				{
					if (vx == 0) //nếu đứng yên
							ani = MARIO_ANI_ORANGE_IDLE_RIGHT;
					else 
						ani = MARIO_ANI_ORANGE_WALKING_RIGHT;
				}
				
			}
			else
					ani = MARIO_ANI_ORANGE_SITDOWN_RIGHT;
		}
		else if (is_in_object == false)
		{
			if (state == MARIO_STATE_JUMP_SHOOT_BULLET)
				ani = MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT;
			else
			{ 
				ani = MARIO_ANI_ORANGE_JUMP_DOWN_RIGHT;
				if (vy < 0.0f)
					ani = MARIO_ANI_ORANGE_JUMP_UP_RIGHT;
			}
				
		}


	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (is_in_object == true)
		{
			
				if (vx == 0)
				//{
					//if (nx > 0)
						ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					//else ani = MARIO_ANI_SMALL_IDLE_LEFT;
				//}
				else// if (vx > 0)
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				//else ani = MARIO_ANI_SMALL_WALKING_LEFT;
			
			

		} else if (is_in_object == false)
	//	{
			//if (nx > 0)
			//{
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			//}
		//	else if (nx < 0)
			//{
			//	ani = MARIO_ANI_SMALL_JUMP_LEFT;
			//}


	//	}
		
	}
	else if (level == MARIO_LEVEL_BIG_TAIL)
	{
		 if (state == MARIO_STATE_SPIN)
			ani = MARIO_ANI_TAIL_SPIN_TAIL_RIGHT;


		 else if (is_in_object == false)
		 {
			 if (state == MARIO_STATE_FLY)
				 ani = MARIO_ANI_FLY;
			 else
			 {

				 
				 ani = MARIO_ANI_TAIL_JUMP_DOWN_RIGHT;

				 if (vy < 0.0f)
					 ani = MARIO_ANI_TAIL_JUMP_UP_RIGHT;
				// if(vy==0.1)
				//	 ani = MARIO_ANI_FLY;
				 if(is_fly==true)
					 ani = MARIO_ANI_FLY;
			 }



		 }
		 else if (is_in_object == true)
		 {
			if (is_sitdown == true) // trên object thì nó mới sitdown được, if bên ngoài
				ani = MARIO_ANI_TAIL_SITDOWN_RIGHT;
			else
			{
				if (vx == 0) //nếu đứng yên
					ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				else
					ani = MARIO_ANI_TAIL_WALKING_RIGHT;
			}
					
		}
		
	}

	int alpha = 255;
	if (untouchable) alpha = 128;


	//DebugOut(L"DA ZO NGOIIIIIIIIIIIiii swith case: \n");
	animations[ani]->Render(x, y,0,alpha,nx);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		//DebugOut(L"[INFO] vannnn toccccc~~~~~: %f\n", vx);
		//vx += acceleration * dt;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP: 
		vy = -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_SITDOWN:
		//DebugOut(L"DA ZO NGOIIIIIIIIIIIiii swith case: \n");
		//y += MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITDOWN_BBOX_HEIGHT - 2;
		is_sitdown = true;
		vx = 0;
		break;
	case MARIO_STATE_IDLE: 
		is_sitdown = false;
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_SPIN:
		//is_spin == true;
		animations[39]->ResetCurrentFrame();
		animations[39]->StartTimeAnimation();
		is_render_animation = true;
		break;
	case MARIO_STATE_SHOOT_BULLET:
	//	DebugOut(L"da vo ban sungggggggggggggggggggggggggggggggggggggg: \n");
		animations[MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT]->ResetCurrentFrame();
		animations[MARIO_ANI_ORANGE_SHOOT_BULLET_RIGHT]->StartTimeAnimation();
		is_render_animation = true;
		break;
	case MARIO_STATE_JUMP_SHOOT_BULLET:
		//DebugOut(L"da vo ban sungggggggggggggggggggggggggggggggggggggg: \n");
		animations[MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT]->ResetCurrentFrame();
		animations[MARIO_ANI_ORANGE_JUMP_SHOOT_BULLET_RIGHT]->StartTimeAnimation();
		is_render_animation = true;
		break;
	case MARIO_STATE_FLY:
		animations[MARIO_ANI_FLY]->ResetCurrentFrame();
		animations[MARIO_ANI_FLY]->StartTimeAnimation();
		is_render_animation = true;
		break;
	case MARIO_STATE_BRING_KOOMPA:
		//vx = 1.5f;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG|| level== MARIO_LEVEL_BIG_ORANGE)
	{
		if (is_sitdown == false) {
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_BIG_SITDOWN_BBOX_WIDTH;
			bottom = y + MARIO_BIG_SITDOWN_BBOX_HEIGHT;
		}
		
	}
	else if (level == MARIO_LEVEL_BIG_TAIL)
	{
		if (is_sitdown == false) {
			right = x + MARIO_BIG_TAIL_BBOX_WIDTH;
			bottom = y + MARIO_BIG_TAIL_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_BIG_TAIL_SITDOWN_BBOX_WIDTH;
			bottom = y + MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT;
		}
	}
	else if(level==MARIO_LEVEL_SMALL)
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

