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




extern vector<LPGAMEOBJECT> objects;



void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY*dt;

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

	if (GetTickCount() - jumping_start < 2000) //  < ấn nhẹ thì nó bay thấp, ấn mạnh thì nó bay cao.
	{											// > ấn nhẹ nhảy cao , ấn mạnh nhảy thấp.
		vy -= 0.02f;
		DebugOut(L"[ERROR-----------get-------------------] DINPUT::GetDeviceData failed. Error: %lu\n", GetTickCount());
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
				CConCo* conco = dynamic_cast<CConCo*>(e->obj);
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
						
						
						/*CoinFly* coinfly = new CoinFly();
						

						coinfly->StartFlyUp();

						objects.push_back(coinfly);*/


						Mushroom* mushroom = new Mushroom();
						objects.insert(objects.begin()+2, mushroom);
						//objects.push_back(mushroom);

						




						//DebugOut(L"[ERROR------------------------------] marioo vua doi dauuuuu \n", x);


					}
				

				}


			}



		}
	}

	//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", y);

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//DebugOutTitle(L"vi tri cua con marioooooooooooooooo %0.001f, %0.001f", this->vx, this->vy);
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
				{
					if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;

					/*if (state == MARIO_STATE_JUMP)
					{
						ani = MARIO_ANI_BIG_JUMP_LEFT; // mới thêm zô
						DebugOut(L"DA ZO JUMP LEFT. Error: %d\n", ani);
					}*/

				}
				else if (vx > 0) //nếu di chuyển trái
				{
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
				}
				else if (vx < 0)
				{
					ani = MARIO_ANI_BIG_WALKING_LEFT; // nếu di chuyển phải
				}
			}
			else
			{
				//DebugOut(L"DA ZO NGOIIIIIIIIIIIiii Error: %d\n", ani);
				if (nx > 0) ani = MARIO_ANI_BIG_SITDOWN_RIGT;
				else ani = MARIO_ANI_BIG_SITDOWN_LEFT;
			}
			
		}
		else if (is_in_object == false)
		{
			if (nx > 0)
				ani = MARIO_ANI_BIG_JUMP_DOWN_RIGHT;
			else if (nx < 0)
				ani = MARIO_ANI_BIG_JUMP_DOWN_LEFT;


			if (vy < 0.0f)
			{
				if (nx > 0)
					ani = MARIO_ANI_BIG_JUMP_UP_LEFT; // mới thêm zô
				else
					ani = MARIO_ANI_BIG_JUMP_UP_RIGHT;
				//DebugOut(L"DA ZO JUMP LEFT. Error: %d\n", ani);
			}
		}
	
	
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (is_in_object == true)
		{
			
				if (vx == 0)
				{
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				else ani = MARIO_ANI_SMALL_WALKING_LEFT;
			
			

		} else if (is_in_object == false)
		{
			if (nx > 0)
			{
				ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			}
			else if (nx < 0)
			{
				ani = MARIO_ANI_SMALL_JUMP_LEFT;
			}

		}
		
	}
	else if (level = MARIO_LEVEL_BIG_TAIL)
	{

		if (vx == 0)
		{
			if (nx > 0) ani = MARIO_ANI_TAIL_IDLE_RIGHT;
			else ani = MARIO_ANI_TAIL_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = MARIO_ANI_TAIL_WALKING_RIGHT;
		else ani = MARIO_ANI_TAIL_WALKING_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	//DebugOut(L"DA ZO JUMP LEFT load?????. Error: %d\n", ani);
	animations[ani]->Render(x, y, alpha);

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
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG)
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
		right = x + MARIO_BIG_TAIL_BBOX_WIDTH;
		bottom = y + MARIO_BIG_TAIL_BBOX_HEIGHT;
	}
	else if(level==MARIO_LEVEL_SMALL)
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

