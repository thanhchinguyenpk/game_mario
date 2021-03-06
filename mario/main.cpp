﻿

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "ConCo.h"
#include "Brick_Coin.h"
#include "Coin.h"
#include "CoinFly.h"
#include "BrickBlink.h"
#include "Mushroom.h"
#include "OngNuoc.h"
#include "Plant.h"
#include "MarioBullet.h"
#include "Map.h"
#include "Flatform.h"
#include "UI.h"
#include "GameTime.h"
#include "PlantBullet.h"
#include "SuperLeaf.h"
#include "DebrisBrick.h"
#include "ParaGoomba.h"
#include "PiranhaPlant.h"
#include "SwitchBlock.h"
#include "VenusFireTrap.h"
#include "Hub.h"
#include "Pmeter.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"mario"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)


#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO		 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC	20
#define ID_TEX_CONCO		30 // conco
#define ID_TEX_CONCO_2		32
#define ID_TEX_BRICK_COIN	40
#define ID_TEX_COIN	50
#define ID_TEX_COIN_FLY	60
#define ID_TEX_BRICK_BLINK	70
#define ID_TEX_NUMBER	80
#define ID_TEX_MUSHROOM	90
#define ID_TEX_ONGNUOC	100
#define ID_TEX_PLANT	110
#define ID_TEX_MARIOPRO	120
#define ID_TEX_MARIO_BULLET	130
#define ID_TEX_MARIO_TAIL_SPIN	140
#define ID_TEX_BULLET_EFFECT	150
#define ID_TEX_NUMBER_AND_TEXT	160
#define ID_TEX_HUB	170
#define ID_TEX_P	180


vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> itemsMarioCanEat;
vector<LPGAMEOBJECT> listBricks;

CGame *game;

CMario *mario;
CGoomba *goomba;
CConCo* conco;
Brick_Coin* brickcoin;
Coin* coin;
CoinFly* coinfly;
BrickBlink* brickblink;
OngNuoc* ongnuoc;
Plant* plant;
MarioBullet* mario_bullet;
Map* map;
Flatform* flatform;
UI* game_ui;
GameTime* game_time;
PlantBullet *plant_bullet;



class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);


	switch (KeyCode)
	{
	
	case DIK_K:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX() + 100, CGame::GetInstance()->GetCamY());
		break;
	case DIK_U:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() - 100);
		break;
	case DIK_G:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX() - 100, CGame::GetInstance()->GetCamY());
		break;
	case DIK_N:
		CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX() , CGame::GetInstance()->GetCamY() + 50);
		break;
	/*case DIK_5:
		goomba = new CGoomba();
		goomba->AddAnimation(701);
		goomba->AddAnimation(702);
		goomba->AddAnimation(703);
		goomba->SetPosition(mario->x+500, 100);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
		break;
	case DIK_6:
		conco = new CConCo();
		conco->AddAnimation(901);
		conco->AddAnimation(902);
		conco->AddAnimation(903);
		conco->AddAnimation(904);
		conco->AddAnimation(905);
		conco->AddAnimation(906);
		conco->AddAnimation(907);
		conco->AddAnimation(908);
		conco->SetPosition(mario->x + 500, 100.0f);
		conco->SetState(CONCO_STATE_WALKING_LEFT);//CONCO_STATE_WALKING_LEFT
		objects.push_back(conco);
			break;*/
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		mario->SetPosition(mario->x, 80.0f);
		//goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
			break;
	case DIK_2:
		mario->SetPosition(mario->x, 80.0f);
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetPosition(mario->x, 80.0f);
		mario->SetLevel(MARIO_LEVEL_BIG_TAIL);
		break;
	case DIK_4:
		mario->SetPosition(mario->x, 80.0f);
		mario->SetLevel(MARIO_LEVEL_BIG_ORANGE);
		break;
	case DIK_R:
		mario->SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
		break;
	case DIK_H:
		mario->is_press_h=true;
		break;
	case DIK_Q:
		//mario->SetPosition(mario->GetX()+5, mario->GetY());
		//mario->SetState(MARIO_STATE_JUMP);
	//	if (mario->GetIsInObject() == false)
	//	{
		if (mario->is_run_for_fly_high)
		{
			mario->SetIsInObject(false);
			mario->SetState(MARIO_STATE_FLY_HIGH);
			mario->SetIsFly(true);
		}

	//	}
		break;
	case DIK_LEFT:
		mario->is_press_left = true;
		break;
	case DIK_S:
	//case 14:
		

		if (mario->GetIsInObject() == true&& mario->is_run_for_fly_high==false)
		{
			mario->StartJumping();
			mario->SetState(MARIO_STATE_JUMP);
			mario->SetIsInObject(false);
		}
		else
		{	
			if (mario->is_run_for_fly_high==true)
			{
				mario->SetIsInObject(false);
				mario->SetState(MARIO_STATE_FLY_HIGH);
				mario->SetIsFly(true);
			}
			else if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			{
				mario->SetState(MARIO_STATE_FLY);
				mario->SetIsFly(true);
			}
		}
		//DebugOut(L"[INFO] KeyAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADown: %d\n", KeyCode);

		break;
	case DIK_A:
	case DIK_BACKSPACE:
	//case DIK_BACKSPACE:// reset
	/*mario->SetState(MARIO_STATE_IDLE);
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(50.0f,0.0f);
		mario->SetSpeed(0, 0);*/
		mario->is_press_h = true; // cho trạng thái cấm mai rùa

		DebugOut(L"[INFO] ssssssssssssssssssssssssssssssssssssssssssssss: %d\n", KeyCode);

		if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
		{

			mario->SetSpin(true);
			mario->SetState(MARIO_STATE_SPIN);

		}
		else if (mario->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
		{
				if(mario->GetIsInObject()==true)
					mario->SetState(MARIO_STATE_SHOOT_BULLET);
				else
					mario->SetState(MARIO_STATE_JUMP_SHOOT_BULLET);

				MarioBullet* temp = new MarioBullet();

				temp->AddAnimation(14001);
				temp->AddAnimation(14002);

				if (mario->GetNX() > 0)
				{
					temp->SetState(MARIOBULLET_STATE_WALKING_RIGHT);
					temp->SetPosition(mario->GetX() + 10 + 5, mario->GetY());
				}
				else
				{
					temp->SetState(MARIOBULLET_STATE_WALKING_LEFT);
					temp->SetPosition(mario->GetX() - 5, mario->GetY());
				}

				objects.push_back(temp);
				mario->SetShoot(true);
			
		}

	
				
		break;
	case DIK_DOWN:
		if (mario->GetLevel() == MARIO_LEVEL_BIG|| mario->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
			mario->SetPosition(mario->x,mario->y+ MARIO_BIG_BBOX_HEIGHT/2 - MARIO_BIG_SITDOWN_BBOX_HEIGHT/2 );
		else if(mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			mario->SetPosition(mario->x, mario->y + MARIO_BIG_TAIL_BBOX_HEIGHT/2 - MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT/2);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		mario->EndJumping();
		//DebugOut(L"[INFO] KeyAAAAAAAAAAAAABBBBBBBBBBBBBBBAAAAAAAAAAAAADown: %d\n", KeyCode);
		break;
	case DIK_Q:
		mario->SetIsBring(false);
		break;
	//case DIK_BACKSPACE:
		//mario->SetShoot(false);
		//mario->SetSpin(false);
	case DIK_H:

		if (mario->hold_somthing != NULL) 
		{
			mario->is_press_h = false;
			CConCo* conco = dynamic_cast<CConCo*>(mario->hold_somthing);
			conco->is_brought = false;
			conco->is_brought = false;
			conco->SetState(CONCO_STATE_MAI_RUA_CHAY);
			mario->hold_somthing = NULL;
			mario->is_bring = false;
			mario->SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
		}

	break;
	case DIK_RIGHT:
		
		break;
	case DIK_LEFT:
		mario->is_press_left = false;
		break;
		
	case DIK_DOWN:
		//DebugOut(L"UPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPp\n", KeyCode);
		if(mario->GetLevel()== MARIO_LEVEL_BIG|| mario->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
			mario->SetPosition(mario->x, mario->y - MARIO_BIG_BBOX_HEIGHT/2 + MARIO_BIG_SITDOWN_BBOX_HEIGHT/2  );
		else if(mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			mario->SetPosition(mario->x, mario->y - MARIO_BIG_TAIL_BBOX_HEIGHT/2 + MARIO_BIG_TAIL_SITDOWN_BBOX_HEIGHT/2);
		break;

	case DIK_A:
		mario->SetIsIncreaseSpeed(false);
		mario->is_press_z = false;
		mario->is_run_for_fly_high = false;



		if(mario->hold_somthing!=NULL){
			mario->is_press_h = false;
			CConCo* conco = dynamic_cast<CConCo*>(mario->hold_somthing);
			conco->is_brought = false;

			if (mario->x < conco->x)
				conco->SetState(CONCO_STATE_MAI_RUA_CHAY_PHAI);
			else
				conco->SetState(CONCO_STATE_MAI_RUA_CHAY_TRAI);

			mario->hold_somthing = NULL;
			mario->is_bring = false;
			mario->SetState(MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT);
		}

		break;
	}
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;

	if (game->IsKeyDown(DIK_A) && (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT)))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->is_press_z = true;
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		
			if (game->IsKeyDown(DIK_LEFT))
			{
				mario->nx = -1;
				mario->is_left = true;
				if (mario->is_right == false)
				{
					mario->SetAcceleration(-MARIO_ACCELERATION);
				}
				else
				{
					mario->SetAcceleration(-1.8 * MARIO_ACCELERATION);
					mario->is_slightly_lower_limit = true;
					mario->is_skid = true;
					if (mario->vx < 0) //tắt điều điện bên phải if dể sang chiều âm không vị vượt limit
					{
						mario->is_slightly_lower_limit = false;
						mario->is_skid = false;
					}
				}
			}

			if (game->IsKeyDown(DIK_RIGHT))
			{
				mario->nx = 1;
				mario->is_right = true;
				if (mario->is_left == false)
				{
					mario->SetAcceleration(MARIO_ACCELERATION);
				}
				else
				{
					mario->SetAcceleration(1.8 * MARIO_ACCELERATION);
					mario->is_slightly_lower_limit = true;
					mario->is_skid = true;

					//vận tốc lúc này đang là dương chuyển về âm rồi chuyển về dương
					if (mario->vx > 0)
					{
						mario->is_slightly_lower_limit = false;
						mario->is_skid = false;
					}
				}
			}


		}// huhu hai dòng dưới quan trọng
		//else
		//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
		return;
	}
	/*else if (game->IsKeyDown(DIK_A))
	{
		float speed_x = abs(mario->vx);
		DebugOut(L"co vo diz z? \n");
		mario->is_press_z = true;
		if(speed_x > 0.4)
		{
			
			if (mario->nx > 0)
			{
				DebugOut(L"vo peed_x > 0.4 khong mario->nx > 0 \n");
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(-1.8 * MARIO_ACCELERATION);
				
			}
			else if (mario->nx < 0)
			{
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(1.8 * MARIO_ACCELERATION);
				DebugOut(L"vo tru bu luon moi ge \n");
			}
			
		}
		else
		{
			//mario->SetState(MARIO_STATE_IDLE); // co bug thi xem lai cho nay
			//mario->vx = 0;
			mario->is_slightly_lower_limit = false;
		}
		return;
	}*/



	 if (game->IsKeyDown(DIK_RIGHT))
	{
		//mario->vx = MARIO_WALKING_SPEED;
		//mario->nx = 1;


		/*mario->SetAcceleration(MARIO_ACCELERATION);
		mario->SetState(MARIO_STATE_WALKING_RIGHT);*/
		//return;
		 mario->SetState(MARIO_STATE_WALKING_RIGHT);
		 if (game->IsKeyDown(DIK_RIGHT))
		 {
			 mario->nx = 1;
			 mario->is_right = true;
			 if (mario->is_left == false)
			 {
				 mario->SetAcceleration(MARIO_ACCELERATION);
			 }
			 else
			 {
				 mario->SetAcceleration(1.2 * MARIO_ACCELERATION);
				 mario->is_slightly_lower_limit = true;
				 mario->is_skid = true;

				 //vận tốc lúc này đang là dương chuyển về âm rồi chuyển về dương
				 if (mario->vx > 0)
				 {
					 mario->is_slightly_lower_limit = false;
					 mario->is_skid = false;
				 }
			 }
		 }
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		//mario->vx = -MARIO_WALKING_SPEED;
		//mario->nx = -1;
		/*mario->SetAcceleration(-MARIO_ACCELERATION);
		mario->SetState(MARIO_STATE_WALKING_LEFT);*/
		//return;
		 mario->SetState(MARIO_STATE_WALKING_LEFT);
		 if (game->IsKeyDown(DIK_LEFT))
		 {
			 mario->nx = -1;
			 mario->is_left = true;
			 if (mario->is_right == false)
			 {
				 mario->SetAcceleration(-MARIO_ACCELERATION);
			 }
			 else
			 {
				 mario->SetAcceleration(-1.2 * MARIO_ACCELERATION);
				 mario->is_slightly_lower_limit = true;
				 mario->is_skid = true;
				 if (mario->vx < 0) //tắt điều điện bên phải if dể sang chiều âm không vị vượt limit
				 {
					 mario->is_slightly_lower_limit = false;
					 mario->is_skid = false;
				 }
			 }
		 }
	}
	else if (game->IsKeyDown(DIK_DOWN))
		mario->SetState(MARIO_STATE_SITDOWN);
		//CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() + 10);
	//else if (game->IsKeyDown(DIK_UP))
		//CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamX(), CGame::GetInstance()->GetCamY() - 10);
	//{
		

//	}
	
	else //trạng thái đứng yên
	{
		// nên đặt biến is_shooting hay is_spin gì gì đó cho khỏi kẹp đk, nhiều đk vai lon
		/*if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
		{
			if(mario->GetState() == MARIO_STATE_FLY)

			else if(mario->GetState() == MARIO_STATE_)
		}*/
		if (mario->GetState() == MARIO_STATE_FLY)
			return;
		if (mario->GetState() == MARIO_STATE_FLY_HIGH)	
			return;
		if (mario->GetState() == MARIO_STATE_SPIN)
			return;
		
		if (mario->GetState() == MARIO_STATE_JUMP_SHOOT_BULLET)
			return;
		if (mario->GetState() == MARIO_STATE_ROUSE_KOOMPASHELL_RIGHT)
			return;

		float speed_x = abs(mario->vx);
		//DebugOut(L"co vo diz z? \n");
		//mario->is_press_z = true;

		if (speed_x > 0.2)
		{

			if (mario->nx > 0)
			{
				DebugOut(L"vo peed_x > 0.4 khong mario->nx > 0 \n");
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(-1.8 * MARIO_ACCELERATION);

			}
			else if (mario->nx < 0)
			{
				mario->is_slightly_lower_limit = true;
				mario->SetAcceleration(1.8 * MARIO_ACCELERATION);
				DebugOut(L"vo tru bu luon moi ge \n");
			}

		}
		else
		{
			
			mario->is_slightly_lower_limit = false;
			//mario->SetState(MARIO_STATE_IDLE);
			mario->is_skid = false;
			mario->is_max_speed = false;
			mario->is_left = false;
			mario->is_right = false;
			//mario->is_walking = false;

			//DebugOut(L"helooo , zo idle hemmmmmmmmmmm: \n");
			mario->SetIsFly(false);

			

			if (mario->GetState() == MARIO_STATE_SHOOT_BULLET)
				return;

			mario->SetState(MARIO_STATE_IDLE);

		}
		
		mario->is_fly_high = false;
		mario->is_fly_short = false;
	
	//	{
		
	//	}

	//	if (mario->GetState() != MARIO_STATE_SHOOT_BULLET&&mario->GetIsInObject() == true)
	//		mario->SetState(MARIO_STATE_IDLE);

	//	if (mario->GetState() != MARIO_STATE_FLY_SHOOT_BULLET && mario->GetIsInObject()==false )
	//		mario->SetState(MARIO_STATE_IDLE);
		
		
	}

}
		

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, L"textures\\mario.png",D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_CONCO, L"textures\\ENEMY.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_CONCO_2, L"textures\\ENEMY2.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BRICK_COIN, L"textures\\NAM_GACH.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_COIN, L"textures\\NAM_GACH.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_COIN_FLY, L"textures\\NAM_GACH.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BRICK_BLINK, L"textures\\NAM_GACH.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_NUMBER, L"textures\\NUMBER1.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_MUSHROOM, L"textures\\NAM_GACH.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_ONGNUOC, L"textures\\BACK_GROUND.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_PLANT, L"textures\\CONPHUNLUA.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_MARIOPRO, L"textures\\MARIOPRO.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MARIO_BULLET, L"textures\\MARIOPRO.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MARIO_TAIL_SPIN, L"textures\\MARIO_TAIL_SPIN.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BULLET_EFFECT, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_NUMBER_AND_TEXT, L"textures\\TextAndNumber.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_HUB, L"textures\\status_bar.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_P, L"textures\\power_state.png", D3DCOLOR_XRGB(176, 224, 248));
	


	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	LPDIRECT3DTEXTURE9 texMarioPro = textures->Get(ID_TEX_MARIOPRO);
	LPDIRECT3DTEXTURE9 texMarioTailSpin = textures->Get(ID_TEX_MARIO_TAIL_SPIN);

	// big
	sprites->Add(10001, 246, 154, 260, 181, texMario);		// idle right

	sprites->Add(10002, 275, 154, 290, 181, texMario);		// walk
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);		// idle left
	sprites->Add(10012, 155, 154, 170, 181, texMario);		// walk
	sprites->Add(10013, 125, 154, 140, 181, texMario);

	sprites->Add(10099, 215, 120, 231, 135, texMario);		// die 

	sprites->Add(10100, 270, 49, 270 +17, 49+26, texMarioPro);		//big jump up r
	sprites->Add(10101, 1400, 49, 1400 + 16, 49 + 26, texMarioPro);	//big jump up l
	sprites->Add(10102, 233, 49, 233 + 16, 49 + 26, texMarioPro);	//big jump down r
	sprites->Add(10103, 1438, 49, 1438 + 16, 49 + 26, texMarioPro);	//big jump down l

	sprites->Add(10104, 379, 57, 379 + 14, 57 + 19, texMarioPro);	//big sitdown r
	sprites->Add(10105, 1294, 57, 1294 + 14, 57 + 19, texMarioPro);	//big sitdown r

	// small
	sprites->Add(10021, 247, 0, 259, 15, texMario);			// idle small right
	sprites->Add(10022, 275, 0, 291, 15, texMario);			// walk 
	sprites->Add(10023, 306, 0, 320, 15, texMario);			// 

	sprites->Add(10031, 187, 0, 198, 15, texMario);			// idle small left

	sprites->Add(10032, 155, 0, 170, 15, texMario);			// walk
	sprites->Add(10033, 125, 0, 139, 15, texMario);			// 
	//lv small chỉ có 1 texture
	sprites->Add(10034,  303, 8,  303 + 17, 8 + 16, texMarioPro);//small jump r
	sprites->Add(10035, 1367, 8, 1367 + 16, 8 + 16, texMarioPro);	//small jump l

	//lv co duoi
	sprites->Add(10036,	  80,    142,   80 + 21, 142 + 28, texMarioPro);	// tail idle r

	sprites->Add(10037, 1586,    142, 1586 + 21, 142 + 28, texMarioPro);	//tail idle l

	sprites->Add(10038, 104, 142, 104 + 22, 142 + 28, texMarioPro);	// tail walk r
	sprites->Add(10039, 129+1, 143, 129 + 23, 143 + 27, texMarioPro);	

	sprites->Add(10040, 1561, 142, 1561 + 22, 142 + 28, texMarioPro);	// tail walk l
	sprites->Add(10041, 1535, 143, 1535 + 23, 143 + 27, texMarioPro);

	sprites->Add(10042, 257, 143, 257 + 23, 143 + 27, texMarioPro);	// tail jum up r
	sprites->Add(10043, 283, 143, 283 + 23, 143 + 27, texMarioPro);// tail jum dowm r

	sprites->Add(10044, 1407, 143, 1407 + 23, 143 + 27, texMarioPro);	// tail jum up l
	sprites->Add(10045, 1381, 143, 1381 + 23, 143 + 27, texMarioPro);// tail jum down l

	sprites->Add(10046, 522, 152, 522 + 22, 152 + 19, texMarioPro);	// tail sit r
	sprites->Add(10047, 1143, 152,1143 + 22, 152+ 19, texMarioPro);// tail sit l

	// lv organe
	sprites->Add(10048, 206, 109, 206 + 14, 109 + 27, texMarioPro);// idle r
	sprites->Add(10049, 1467, 109, 1467 + 14, 109 + 27, texMarioPro);// idle l

	sprites->Add(10050, 223, 109, 223 + 16, 109 + 27, texMarioPro);// walk r
	sprites->Add(10051, 242, 110, 242 + 16, 110 + 26, texMarioPro);// 

	sprites->Add(10052, 1448, 109, 1448 + 16, 109 + 27, texMarioPro);// walk l
	sprites->Add(10053, 1429, 110, 1429 + 16, 110 + 26, texMarioPro);//

	sprites->Add(10054, 314, 110, 314 + 16, 110 + 26, texMarioPro);//jump up r
	sprites->Add(10055, 242, 110, 242 + 16, 110 + 26, texMarioPro);//jump down r

	sprites->Add(10056, 1357, 110, 1357 + 16, 110 + 26, texMarioPro);//jump up l
	sprites->Add(10057, 1429, 110, 1429 + 16, 110 + 26, texMarioPro);//jump down l

	sprites->Add(10058, 422, 118,422 + 14, 118 + 18, texMarioPro);//sit r
	sprites->Add(10059, 1251, 118, 1251 + 14, 118 + 18, texMarioPro);//sit l

	sprites->Add(10060,  280, 109,  280 + 14, 109 + 27, texMarioPro);// shoot bullet r
	sprites->Add(10061,  297, 109,  297 + 14, 109 + 27, texMarioPro);//
	sprites->Add(10062, 1393, 109, 1393 + 14, 109 + 27, texMarioPro);// shoot bullet l
	sprites->Add(10063, 1376, 109, 1376 + 14, 109 + 27, texMarioPro);//

	//lv tail spin tail
	/*sprites->Add(10064,   12 - 2, 13,   12 + 21 + 7 + 12,  13 + 28, texMarioTailSpin);//spin tail right
	sprites->Add(10065,       62, 13,        62 + 23 + 9,  13 + 28, texMarioTailSpin);//
	sprites->Add(10066,   114 -8, 13,         114+ 16+ 8,  13 + 28, texMarioTailSpin);// 
	sprites->Add(10067,  156 - 9, 12,           156 + 23,  13 + 29, texMarioTailSpin);//
	sprites->Add(10068,  203 - 8, 13,       203 + 16 + 8,  13 + 28, texMarioTailSpin);//
	sprites->Add(10069, 12 - 2, 13, 12 + 21 + 7 + 12, 13 + 28, texMarioTailSpin);*/

	sprites->Add(10064, 12 , 13, 12 + 21 , 13 + 28, texMarioTailSpin);//spin tail right
	sprites->Add(10065, 62-7, 13, 62 + 23 + 9, 13 + 28, texMarioTailSpin);//
	sprites->Add(10066, 114 - 8-3, 13, 114 + 16 + 8, 13 + 28, texMarioTailSpin);// 
	sprites->Add(10067, 156 - 9, 12, 156 + 23, 13 + 29, texMarioTailSpin);//
	sprites->Add(10068, 203 - 8-3, 13, 203 + 16 + 8, 13 + 28, texMarioTailSpin);//
	sprites->Add(10069, 12 , 13, 12 + 21 , 13 + 28, texMarioTailSpin);

	//sprites->Add(10069,  210 -7 -2, 61, 210+21+2, 61+28, texMarioTailSpin);//spin tail left
	sprites->Add(10070,      158-9, 61,   158+23, 61+28, texMarioTailSpin);//
	sprites->Add(10071,      113-8, 61, 113+16+8, 61+28, texMarioTailSpin);//
	sprites->Add(10072,         64, 61,  64+23+9, 61+28, texMarioTailSpin);//
	sprites->Add(10073,       24-8, 61,  24+16+8, 61+28, texMarioTailSpin);//

	sprites->Add(10074, 642, 110, 642 + 19, 110 + 26, texMarioPro);// fly shoot bullet r
	sprites->Add(10075, 621, 109, 621 + 18, 109 + 27, texMarioPro);
	sprites->Add(10076, 599, 109, 599 + 16, 109 + 27, texMarioPro);

	sprites->Add(10077, 283		, 143, 283 + 23, 143 + 27, texMarioPro);//fly tail r
	sprites->Add(10078, 335-1	, 142, 335 + 22, 142 + 28, texMarioPro);
	sprites->Add(10079, 309		, 143, 309 + 23, 143 + 27, texMarioPro);
	
	sprites->Add(10080, 441, 143, 441 + 24, 143 + 27, texMarioPro);		//fly tail high r
	sprites->Add(10081, 495, 142, 495 + 24, 142 + 28, texMarioPro);
	sprites->Add(10082, 468, 143, 468 + 24, 143 + 27, texMarioPro);


	sprites->Add(10083, 434,	  48, 434 + 14, 48 + 27, texMarioPro);		//big bring koompa
	sprites->Add(10084, 451,	  48, 451 + 15, 48 + 27, texMarioPro);
	sprites->Add(10085, 469,  	 49, 469 + 16, 49 + 27, texMarioPro);

	sprites->Add(10086, 488, 48, 488 + 21, 48 + 27, texMarioPro);// big rouse koompa shell r

	sprites->Add(10087, 1419, 47, 1419 + 16, 47+ 28, texMarioPro);// big skid l

	sprites->Add(10088, 290, 48, 290 + 19, 48 + 27, texMarioPro);//big run r
	sprites->Add(10089, 312, 48, 312 + 19, 48 + 27, texMarioPro);
	sprites->Add(10090, 335, 48, 335 + 19, 49 + 26, texMarioPro);

	//=======
	sprites->Add(10091, 323, 8, 323 + 16, 8 + 16, texMarioPro);//small run r
	sprites->Add(10092, 341, 8, 341 + 16, 8 + 16, texMarioPro);
	sprites->Add(10093, 1386, 8, 1386 + 14, 8 + 16, texMarioPro);// small skid l

	sprites->Add(10094, 360, 142, 360 + 24, 142 + 28, texMarioPro);//tail run r
	sprites->Add(10095, 387, 142, 387 + 24, 142 + 28, texMarioPro);
	sprites->Add(10096, 414, 143, 414 + 24, 143 + 27, texMarioPro);
	sprites->Add(10097, 1516, 140, 1516 + 16, 140 + 30, texMarioPro);// tail skid l


	/*sprites->Add(10098, 360, 142, 360 + 24, 142 + 28, texMarioPro);//tail run r
	sprites->Add(10200, 347, 142, 347 + 24, 142 + 28, texMarioPro);
	sprites->Add(10201, 414, 143, 414 + 24, 143 + 27, texMarioPro);                          //chú ý 10099 đã có
	sprites->Add(10202, 1516, 140, 1516 + 16, 140 + 30, texMarioPro);// tail skid l*/


	sprites->Add(10098, 333, 109, 333 + 19, 109 + 27, texMarioPro);//orange run r
	sprites->Add(10200, 355, 109, 355 + 19, 109 + 27, texMarioPro);
	sprites->Add(10201, 378, 110, 378 + 19, 110 + 26, texMarioPro);
	sprites->Add(10202, 1410, 107, 1410 + 16, 107 + 29, texMarioPro);//orange skid l


	sprites->Add(10203, 641, 142, 641 + 22, 142+ 28, texMarioPro);// tail rouse koompa shell r
	sprites->Add(10204, 566, 142, 566 + 21, 142 + 28, texMarioPro);		//tail bring koompa
	sprites->Add(10205, 590, 142, 590 + 22, 142 + 28, texMarioPro);
	sprites->Add(10206, 615, 143, 615 + 23, 143 + 27, texMarioPro);

	sprites->Add(10207, 470, 8, 470 + 16, 8 + 16, texMarioPro);// small rouse koompa shell r
	sprites->Add(10208, 435, 8, 435 + 14, 8 + 16, texMarioPro);		//small bring koompa
	sprites->Add(10209, 452, 8, 452 + 15, 8 + 16, texMarioPro);

	sprites->Add(10210, 531, 109, 531 + 21, 109 + 27, texMarioPro);// orange rouse koompa shell r
	sprites->Add(10211, 477, 109, 477 + 14, 109 + 27, texMarioPro);//orange bring koompa
	sprites->Add(10212, 494, 109, 494 + 15, 109 + 27, texMarioPro);		
	sprites->Add(10213, 512, 110, 512 + 16, 110 + 26, texMarioPro);
	

	
		


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 14, 21, 29, texEnemy);//walk
	sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	sprites->Add(30003, 45, 14, 45+16, 14 +16, texEnemy); // die sprite

	sprites->Add(30004, 5, 14, 21, 29, texEnemy);//was shooted



	LPDIRECT3DTEXTURE9 texConCo = textures->Get(ID_TEX_CONCO); // con con qua ben trai
	sprites->Add(60001, 205, 191, 205+16, 191+27, texConCo);
	sprites->Add(60002, 222, 191, 222+16, 191+27, texConCo);

	sprites->Add(60003, 170, 192, 170 + 16, 192 + 27, texConCo);// con co qua ben phai
	sprites->Add(60004, 187, 191, 187 + 16, 191 + 27, texConCo);

	sprites->Add(60005, 239, 202, 239 + 16, 202 + 16, texConCo);// thụt vào

	sprites->Add(60006, 256, 202, 256 + 17, 202 + 17, texConCo);//thụt vào chạy
	sprites->Add(60007, 272+1, 202, 272 + 17, 202 + 17, texConCo);
	sprites->Add(60008, 288+1, 202, 288 + 17, 202 + 17, texConCo);

	sprites->Add(60009, 205, 248, 205 + 16, 248 + 28, texConCo);// con cò bay qua trái
	sprites->Add(60010, 222, 250, 222 + 16, 250 + 26, texConCo);
	sprites->Add(60011, 239, 249, 239 + 16, 249 + 27, texConCo);
	sprites->Add(60012, 256, 249, 256 + 16, 249 + 27, texConCo);

	LPDIRECT3DTEXTURE9 texConCo2 = textures->Get(ID_TEX_CONCO_2); //vì lấy ảnh đảo ngược á, tứk

	sprites->Add(60013, 262, 249, 262 + 16, 249 + 27, texConCo2);// con cò bay qua phải
	sprites->Add(60014, 279, 249, 279 + 16, 249 + 27, texConCo2);
	sprites->Add(60015, 296, 250, 296 + 16, 250 + 26, texConCo2);
	sprites->Add(60016, 313, 248, 313 + 16, 248 + 28, texConCo2);

	LPDIRECT3DTEXTURE9 texConCo3 = textures->Get(ID_TEX_PLANT);
	sprites->Add(60017, 32, 149, 32 + 16, 149 + 16, texConCo3);// mai rùa thụt vào rung rinh
	sprites->Add(60018, 31, 149, 32 + 16, 149 + 16, texConCo3);
	//sprites->Add(60019, 30, 149, 32 + 16, 149 + 16, texConCo3);
	//sprites->Add(60020, 32, 149, 32 + 16, 149 + 16, texConCo3);

	sprites->Add(60021, 74, 127, 74 + 18, 127 + 16, texConCo3);// mai rùa thò chân
	sprites->Add(60022, 31, 149, 32 + 16, 149 + 16, texConCo3);








	//gạch chấm hỏi có tiền
	LPDIRECT3DTEXTURE9 texBrickCoin = textures->Get(ID_TEX_BRICK_COIN); // cục gạch tiền
	sprites->Add(70001, 157, 188, 157 + 16, 188 + 16, texBrickCoin); //dấu chấm hỏi chạy chạy
	sprites->Add(70002, 176, 188, 176 + 16, 188 + 16, texBrickCoin);
	sprites->Add(70003, 196, 188, 196 + 16, 188 + 16, texBrickCoin);
	sprites->Add(70004, 215, 188, 215 + 16, 188 + 16, texBrickCoin);

	sprites->Add(70005, 235, 188, 235 + 16, 188 + 16, texBrickCoin); // trống trơn( đã bị đội đầu)

	// đồng tiền xoay xoay bay lên, tạo một cái hộp có width l
	LPDIRECT3DTEXTURE9 texCoinFly = textures->Get(ID_TEX_COIN_FLY);
	sprites->Add(80001, 294 - 3, 101, 294 +  8 +  3, 101 + 14, texCoinFly);
	sprites->Add(80002, 311 - 6, 101, 311 +  1 +  6, 101 + 14, texCoinFly);   //đặc biệt
	sprites->Add(80003, 321 - 5, 101, 321 +  4 +  5, 101 + 14, texCoinFly);
	sprites->Add(80004, 334    , 100, 334 + 14     , 101 + 16, texCoinFly);
	sprites->Add(80005, 357 - 4, 100, 357 +  6 +  4, 101 + 16, texCoinFly);
	sprites->Add(80006, 372 - 2, 100, 357 + 10 +  2, 101 + 16, texCoinFly);


	// viên gạch phát sáng
	LPDIRECT3DTEXTURE9 texBrickBlink = textures->Get(ID_TEX_BRICK_BLINK);
	sprites->Add(90001, 274, 188, 274 + 16, 188 + 16, texBrickBlink);
	sprites->Add(90002, 293, 188, 293 + 16, 188 + 16, texBrickBlink);
	sprites->Add(90003, 312, 188, 312 + 16, 188 + 16, texBrickBlink);
	sprites->Add(90004, 331, 188, 331 + 16, 188 + 16, texBrickBlink);


	//Số 100
	LPDIRECT3DTEXTURE9 texNumber = textures->Get(ID_TEX_NUMBER);
	sprites->Add(100001, 185, 10, 185+13, 10+9, texNumber);

	//Nấm
	LPDIRECT3DTEXTURE9 texMushroom = textures->Get(ID_TEX_MUSHROOM);
	sprites->Add(110001, 156, 121, 156 + 16, 121 + 16, texMushroom);

	//Ống nước
	LPDIRECT3DTEXTURE9 texOngNuoc= textures->Get(ID_TEX_ONGNUOC);
	sprites->Add(120001, 5, 28, 5 + 32, 28 + 48, texOngNuoc);

	//plant
	LPDIRECT3DTEXTURE9 texPlant = textures->Get(ID_TEX_PLANT);
	sprites->Add(130001, 219, 81, 219 + 16, 81 + 32, texPlant); //đỏ hả miệng ngước xuống
	sprites->Add(130002, 242, 81, 242 + 16, 81 + 32, texPlant); //đỏ khép miệng ngước xuống
	sprites->Add(130003, 267, 81, 267 + 16, 81 + 32, texPlant); //đỏ hả miệng ngước lên
	sprites->Add(130004, 289, 81, 289 + 16, 81 + 32, texPlant); //đỏ khép miệng ngước lên

	sprites->Add(130005, 219, 43, 219 + 16, 43 + 24, texPlant); //xanh hả miệng ngước xuống
	sprites->Add(130006, 244, 43, 244 + 16, 43 + 24, texPlant); //xanh khép miệng ngước xuống
	sprites->Add(130007, 267, 43, 267 + 16, 43 + 24, texPlant); //xanh hả miệng ngước lên
	sprites->Add(130008, 289, 43, 289 + 16, 43 + 24, texPlant); //xanh khép miệng ngước lên

	//Bullet
	LPDIRECT3DTEXTURE9 texMarioBullet = textures->Get(ID_TEX_MARIO_BULLET);
	sprites->Add(140001, 162, 124, 162 + 8, 124 + 8, texMarioBullet);
	sprites->Add(140002, 173, 123, 173 + 8, 123 + 9, texMarioBullet);
	sprites->Add(140003, 184, 124, 184 + 8, 124 + 8, texMarioBullet);
	sprites->Add(140004, 195, 123, 195 + 8, 123 + 9, texMarioBullet);

	LPDIRECT3DTEXTURE9 texMarioBulletEffect = textures->Get(ID_TEX_BULLET_EFFECT);
	sprites->Add(140005, 526, 19, 526 + 19, 19 + 19, texMarioBulletEffect);
	sprites->Add(140006, 544, 20, 544 + 16, 20 + 16, texMarioBulletEffect);
	sprites->Add(140007, 599, 21, 599 + 16, 21 + 16, texMarioBulletEffect);
	//	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	//sprites->Add(20001, 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texNumberAndText = textures->Get(ID_TEX_NUMBER_AND_TEXT);
	sprites->Add(200000, 31, 24, 31 + 9, 24 + 8, texNumberAndText);//0
	sprites->Add(200001, 54, 24, 54 + 7, 24 + 7, texNumberAndText);
	sprites->Add(200002, 71, 24, 71 + 9, 24 + 8, texNumberAndText);

	sprites->Add(200003, 90, 24, 90 + 8, 24 + 7, texNumberAndText);//3
	sprites->Add(200004, 108, 24, 108 + 8, 24 + 7, texNumberAndText);
	sprites->Add(200005, 127, 24, 127 + 8, 24 + 8, texNumberAndText);

	sprites->Add(200006, 143, 24, 143 + 10, 24 + 7, texNumberAndText);//6
	sprites->Add(200007, 162, 24, 162 + 8, 24 + 8, texNumberAndText);
	sprites->Add(200008, 179, 24, 179 + 9, 24 + 8, texNumberAndText);

	sprites->Add(200009, 197, 24, 197 + 8, 24 + 8, texNumberAndText);//9

	//super leaf
	LPDIRECT3DTEXTURE9 texSuperLeaf = textures->Get(ID_TEX_BRICK_COIN);
	sprites->Add(210000, 180, 123, 180 + 16, 123 + 14, texSuperLeaf);
	
	//debris brick
	LPDIRECT3DTEXTURE9 texDebrisBrick = textures->Get(ID_TEX_MISC);
	sprites->Add(220000, 458, 119, 458+10, 119+10, texDebrisBrick);
	sprites->Add(220001, 470, 119, 470 + 10, 119 + 10, texDebrisBrick);
	
	//para goompa
	LPDIRECT3DTEXTURE9 texParaGoomba = textures->Get(ID_TEX_PLANT);
	sprites->Add(230000, 116, 40, 116 + 20, 40 + 19, texParaGoomba);//walking with swing
	sprites->Add(230001, 140, 40, 140 + 20, 40 + 19, texParaGoomba);

	sprites->Add(230002, 66, 35, 66 + 20, 35 + 24, texParaGoomba);//swing small

	sprites->Add(230003, 116, 35, 116 + 20, 34 + 24, texParaGoomba);//swing big

	sprites->Add(230004, 104, 70, 104 + 16, 70 + 16, texParaGoomba);// walking without swing
	sprites->Add(230005, 125, 70, 125 + 16, 70 + 16, texParaGoomba);

	sprites->Add(230006, 145, 70, 145 + 16, 70 + 16, texParaGoomba);//dead



	//piranha plant
	LPDIRECT3DTEXTURE9 texPiranhaPlant = textures->Get(ID_TEX_PLANT);
	sprites->Add(240000, 6, 108-1, 6 + 17, 108 + 24, texPiranhaPlant);//cạp cạp
	sprites->Add(240001, 7, 137, 7 + 17, 137 + 24, texPiranhaPlant);

	LPDIRECT3DTEXTURE9 texCoin = textures->Get(ID_TEX_BRICK_COIN); // Đồng tiên đứng yên
	sprites->Add(250000, 334, 100, 334 + 14, 100 + 16, texCoin);

	LPDIRECT3DTEXTURE9 texSwitchBlock = textures->Get(ID_TEX_BRICK_COIN); // switch block
	sprites->Add(260000, 156, 144, 156 + 16, 144 + 16, texSwitchBlock);// nhấp nháy chữ P
	sprites->Add(260001, 178, 144, 178 + 16, 144 + 16, texSwitchBlock);
	sprites->Add(260002, 200, 144, 200 + 16, 144 + 16, texSwitchBlock);// switch bị đạp

	LPDIRECT3DTEXTURE9 texUpMushroom = textures->Get(ID_TEX_BRICK_COIN);
	sprites->Add(270000, 286, 121, 286 + 16, 121 + 16, texSwitchBlock);//nấm xanh

	LPDIRECT3DTEXTURE9 texHub = textures->Get(ID_TEX_HUB);
	sprites->Add(280000, 3, 3, 3 + 152, 3 + 28, texHub);//nấm xanh


	LPDIRECT3DTEXTURE9 texP = textures->Get(ID_TEX_P);
	sprites->Add(290000, 2,  2, 66,  9, texP);
	sprites->Add(290001, 2, 11, 66, 18, texP);
	sprites->Add(290002, 2, 20, 66, 27, texP);
	sprites->Add(290003, 2, 29, 66, 36, texP);
	sprites->Add(290004, 2, 38, 66, 45, texP);
	sprites->Add(290005, 2, 47, 66, 54, texP);
	sprites->Add(290006, 2, 56, 66, 63, texP);
	sprites->Add(290007, 2, 65, 66, 72, texP);

	

	/*# tier_0
		1020	2	2	66	9	
		# tier_1
		1021	2	11	66	18	
		# tier_2
		1022	2	20	66	27	
		# tier_3
		1023	2	29	66	36	
		# tier_4
		1024	2	38	66	45	
		# tier_5
		1025	2	47	66	54	
		# tier_6
		1026	2	56	66	63	
		# tier_7
		1027	2	65	66	72	
		*/



	LPANIMATION ani;

	ani = new CAnimation(100);	// idle big right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle big left
	ani->Add(10011);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// idle small right
	ani->Add(10021);
	animations->Add(402, ani);

	ani = new CAnimation(100);	// idle small left
	ani->Add(10031);
	animations->Add(403, ani);

	ani = new CAnimation(100);	// walk right big
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);	// // walk left big
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);	// walk right small
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(502, ani);

	ani = new CAnimation(100);	// walk left small
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(503, ani);


	ani = new CAnimation(100);		// Mario die
	ani->Add(10099);
	animations->Add(599, ani);

	ani = new CAnimation(100);		// Mario big jum up  l
	ani->Add(10100);
	animations->Add(450, ani);

	ani = new CAnimation(100);		// Mario big jum up  r
	ani->Add(10101);
	animations->Add(451, ani);

	ani = new CAnimation(100);		// Mario big jum down r
	ani->Add(10102);
	animations->Add(452, ani);
	
	ani = new CAnimation(100);		// Mario big jum down l
	ani->Add(10103);
	animations->Add(453, ani);

	//=====
	ani = new CAnimation(100);		// Mario big jum down l
	ani->Add(10034);
	animations->Add(454, ani);

	ani = new CAnimation(100);		// Mario big jum down l
	ani->Add(10035);
	animations->Add(455, ani);

	ani = new CAnimation(100);		// Mario big sitdowm r
	ani->Add(10104);
	animations->Add(456, ani);

	ani = new CAnimation(100);		// Mario big sitdowm l
	ani->Add(10105);
	animations->Add(457, ani);

	//tail
	ani = new CAnimation(100);		// Mario tail idle r
	ani->Add(10036);
	animations->Add(458, ani);

	ani = new CAnimation(100);		// Mario tail idle l
	ani->Add(10037);
	animations->Add(459, ani);

	ani = new CAnimation(100);		// Mario tail walk r
	ani->Add(10036);
	ani->Add(10038);
	ani->Add(10039);
	animations->Add(460, ani);

	ani = new CAnimation(100);		// l
	ani->Add(10037);
	ani->Add(10040);
	ani->Add(10041);
	animations->Add(461, ani);

	//tail
	ani = new CAnimation(100);		//  jump up r
	ani->Add(10042);
	animations->Add(462, ani);

	ani = new CAnimation(100);		//  jump down r
	ani->Add(10043);
	animations->Add(463, ani);

	ani = new CAnimation(100);		// jump up l
	ani->Add(10044);
	animations->Add(464, ani);


	ani = new CAnimation(100);		// jump down l
	ani->Add(10045);
	animations->Add(465, ani);

	ani = new CAnimation(100);		// sit down r
	ani->Add(10046);
	animations->Add(466, ani);


	ani = new CAnimation(100);		// sit down l
	ani->Add(10047);
	animations->Add(467, ani);

	//orange
	ani = new CAnimation(100);		// idle r
	ani->Add(10048);
	animations->Add(468, ani);

	ani = new CAnimation(100);		// idle l
	ani->Add(10049);
	animations->Add(469, ani);

	ani = new CAnimation(100);		// walk r
	ani->Add(10048);
	ani->Add(10050);
	ani->Add(10051);
	animations->Add(470, ani);

	ani = new CAnimation(100);		// walk l
	ani->Add(10049);
	ani->Add(10052);
	ani->Add(10053);
	animations->Add(471, ani);


	ani = new CAnimation(100);		// jumb up r
	ani->Add(10054);
	animations->Add(472, ani);

	ani = new CAnimation(100);		// jumb down r
	ani->Add(10055);
	animations->Add(473, ani);

	ani = new CAnimation(100);		// jumb up l
	ani->Add(10056);
	animations->Add(474, ani);

	ani = new CAnimation(100);		// jumb down l
	ani->Add(10057);
	animations->Add(475, ani);

	ani = new CAnimation(100);		// sit r
	ani->Add(10058);
	animations->Add(476, ani);

	ani = new CAnimation(100);		// sit l
	ani->Add(10059);
	animations->Add(477, ani);

	ani = new CAnimation(100);		// shoot bullet r
	ani->Add(10060);
	ani->Add(10061);
	animations->Add(478, ani);

	ani = new CAnimation(100);		// shoot bullet l
	ani->Add(10062);
	ani->Add(10063);
	animations->Add(479, ani);

	//tail
	ani = new CAnimation(30);		// tail spin right
	//ani->Add(10064);
	ani->Add(10065);
	ani->Add(10066);
	ani->Add(10067);
	ani->Add(10068);
	ani->Add(10069);
	animations->Add(480, ani);

	//tail
	ani = new CAnimation(100);		// spin tail left
	ani->Add(10069);
	ani->Add(10070);
	ani->Add(10071);
	ani->Add(10072);
	ani->Add(10073);
	animations->Add(481, ani);

	ani = new CAnimation(100);		// fly shoot r
	ani->Add(10074);
	ani->Add(10075);
	ani->Add(10076);
	animations->Add(482, ani);

	ani = new CAnimation(70);		// fly tail r
	ani->Add(10077);
	ani->Add(10078);
	ani->Add(10079);
	animations->Add(483, ani);

	ani = new CAnimation(70);		// fly tail high r
	ani->Add(10080);
	ani->Add(10081);
	ani->Add(10082);
	animations->Add(484, ani);

	ani = new CAnimation(60);		// big bring coompa r
	ani->Add(10083);
	ani->Add(10084);
	ani->Add(10085);
	animations->Add(485, ani);

	ani = new CAnimation(400);		// big brouse coompa r
	ani->Add(10086);
	animations->Add(486, ani);

	ani = new CAnimation(100);		// big skid l
	ani->Add(10087);
	animations->Add(487, ani);

	ani = new CAnimation(40);		// big run r
	ani->Add(10088);
	ani->Add(10089);
	ani->Add(10090);
	animations->Add(488, ani);
	//=====================
	ani = new CAnimation(40);		// small run r
	ani->Add(10091);
	ani->Add(10092);
	animations->Add(489, ani);

	ani = new CAnimation(100);		// small skid l
	ani->Add(10093);
	animations->Add(490, ani);


	ani = new CAnimation(40);		// big tail run r
	ani->Add(10094);
	ani->Add(10095);
	ani->Add(10096);
	animations->Add(491, ani);

	ani = new CAnimation(100);		// big tail skid r
	ani->Add(10097);
	animations->Add(492, ani);

	/*ani = new CAnimation(5);		// big tail run r
	ani->Add(10094);
	ani->Add(10095);
	ani->Add(10096);
	animations->Add(493, ani);

	ani = new CAnimation(100);		// big tail skid r
	ani->Add(10097);
	animations->Add(494, ani);*/

	ani = new CAnimation(40);		// big orange run r
	ani->Add(10098);
	ani->Add(10200);
	ani->Add(10201);
	animations->Add(493, ani);

	ani = new CAnimation(100);		// big orange skid r
	ani->Add(10202);
	animations->Add(494, ani);

	ani = new CAnimation(400);		 // tail brouse coompa r
	ani->Add(10203);
	animations->Add(495, ani);

	ani = new CAnimation(60);		// tail bring coompa r
	ani->Add(10204);
	ani->Add(10205);
	ani->Add(10206);
	animations->Add(496, ani);

	ani = new CAnimation(400);		// small brouse coompa r
	ani->Add(10207);
	animations->Add(497, ani);

	ani = new CAnimation(60);		// small bring coompa r
	ani->Add(10208);
	ani->Add(10209);
	animations->Add(498, ani);

	ani = new CAnimation(400);		// orange brouse coompa r
	ani->Add(10210);
	animations->Add(499, ani);

	ani = new CAnimation(60);		// orange bring coompa r
	ani->Add(10211);
	ani->Add(10212);
	animations->Add(600, ani);// 500 bị trùng lên 600 nhe

	
	//====================================================================================================





	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);

	ani = new CAnimation(300);		// Goomba walk
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(701, ani);

	ani = new CAnimation(1000);		// Goomba dead
	ani->Add(30003);
	animations->Add(702, ani);
	
	ani = new CAnimation(1000);		// Goomba was shoot
	ani->Add(30004);
	animations->Add(703, ani);









	//=======================//
	//con còn
	ani = new CAnimation(300);
	ani->Add(60001);
	ani->Add(60002);
	animations->Add(901,ani);

	ani = new CAnimation(300);
	ani->Add(60003);
	ani->Add(60004);
	animations->Add(902, ani);

	ani = new CAnimation(300);
	ani->Add(60005);
	animations->Add(903, ani);

	ani = new CAnimation(300); // mai rùa cút chạy chạy chạy
	ani->Add(60006);
	ani->Add(60007);
	ani->Add(60008);
	animations->Add(904, ani);

	ani = new CAnimation(100); //rùa bay trái
	ani->Add(60009);
	ani->Add(60010);
	ani->Add(60011);
	ani->Add(60012);
	animations->Add(905, ani);

	ani = new CAnimation(80); //rùa bay phải
	ani->Add(60013);
	ani->Add(60014);
	ani->Add(60015);
	ani->Add(60016);
	animations->Add(906, ani);

	/*ani = new CAnimation(300); //mai rùa thụt vào rung rinh
	ani->Add(60017);
	ani->Add(60018);
	ani->Add(60019);
	ani->Add(60020);
	animations->Add(907, ani);*/

	ani = new CAnimation(15); //mai rùa thụt chân ra vào
	ani->Add(60021);
	ani->Add(60022);
	animations->Add(907, ani);

	ani = new CAnimation(10); //mai rùa thụt vào rung rinh
	ani->Add(60017);
	ani->Add(60018);
	//ani->Add(60019);
	//ani->Add(60020);
	animations->Add(908, ani);

	
	

	//=======================//
	ani = new CAnimation(100);  // viên đá đồng tiền chạy chạy
	ani->Add(70001);
	ani->Add(70002);
	ani->Add(70003);
	ani->Add(70004);
	animations->Add(1001, ani);

	ani = new CAnimation(100);  // viên đá đồng tiền nhưng trống trơn vì đã bị đội đầu
	ani->Add(70005);
	animations->Add(1002, ani);

	//=========================//
	//đồng tiền bay
	ani = new CAnimation(50);
	ani->Add(80001);
	ani->Add(80002);
	ani->Add(80003);
	ani->Add(80004);
	ani->Add(80005);
	ani->Add(80006);
	animations->Add(8001, ani);


	// viên gạch sáng
	ani = new CAnimation(100);
	ani->Add(90001);
	ani->Add(90002);
	ani->Add(90003);
	ani->Add(90004);
	animations->Add(9001, ani);


	// điểm 100
	ani = new CAnimation(100);
	ani->Add(100001);
	animations->Add(10001, ani);


	//nam
	ani = new CAnimation(100);
	ani->Add(110001);
	animations->Add(11001, ani);

	//ống nước
	ani = new CAnimation(100);
	ani->Add(120001);
	animations->Add(12001, ani);

	//venus đỏ
	ani = new CAnimation(200); // cạp cạp ngước xuống
	ani->Add(130001);
	ani->Add(130002);
	animations->Add(13001, ani);

	ani = new CAnimation(200); // cạp cạp ngước lên
	ani->Add(130003);
	ani->Add(130004);
	animations->Add(13002, ani);

	ani = new CAnimation(200); // hả miệng ngước xuống
	ani->Add(130001);
	animations->Add(13003, ani);

	ani = new CAnimation(200); // hả ngước lên
	ani->Add(130003);
	animations->Add(13004, ani);

	//venus xanh
	ani = new CAnimation(200); // cạp cạp ngước xuống
	ani->Add(130005);
	ani->Add(130006);
	animations->Add(13005, ani);

	ani = new CAnimation(200); // cạp cạp ngước lên
	ani->Add(130007);
	ani->Add(130008);
	animations->Add(13006, ani);


	ani = new CAnimation(200); // hả miệng ngước xuống
	ani->Add(130005);
	animations->Add(13007, ani);

	ani = new CAnimation(200); // hả ngước lên
	ani->Add(130007);
	animations->Add(13008, ani);







	//mario bullet

	ani = new CAnimation(200); 
	ani->Add(140001);
	ani->Add(140002);
	ani->Add(140003);
	ani->Add(140004);
	animations->Add(14001, ani);

	//effects bullet
	ani = new CAnimation(200);
	ani->Add(140005);
	ani->Add(140006);
	ani->Add(140007);
	animations->Add(14002, ani);

	//superleaf
	ani = new CAnimation(200);
	ani->Add(210000);
	animations->Add(15000, ani);

	//superleaf
	ani = new CAnimation(50);
	ani->Add(220000);
	ani->Add(220001);
	animations->Add(16000, ani);

	//para koompa
	ani = new CAnimation(100);//walking with swing
	ani->Add(230000);
	ani->Add(230001);
	animations->Add(17000, ani);

	ani = new CAnimation(100); //jumb swing small
	ani->Add(230002);
	animations->Add(17001, ani);

	ani = new CAnimation(40); //jumb swing big
	ani->Add(230002);
	ani->Add(230003);
	animations->Add(17002, ani);


	ani = new CAnimation(100); //walking without swing
	ani->Add(230004);
	ani->Add(230005);
	animations->Add(17003, ani);

	ani = new CAnimation(100); //walking without swing
	ani->Add(230006);
	animations->Add(17004, ani);



	//piranha plant
	ani = new CAnimation(100);
	ani->Add(240000);
	ani->Add(240001);
	animations->Add(18000, ani);


	//coin stay
	ani = new CAnimation(100);
	ani->Add(250000);
	animations->Add(19000, ani);

	//switch block chữ P nhấp nháy
	ani = new CAnimation(100); 
	ani->Add(260000);
	ani->Add(260001);
	animations->Add(20000, ani);

	//switch block bị đạp
	ani = new CAnimation(100);
	ani->Add(260002);
	animations->Add(20001, ani);
	
	//nấm xanh 270000
	ani = new CAnimation(100);
	ani->Add(270000);
	animations->Add(21000, ani);

	//nấc p
	ani = new CAnimation(100);
	ani->Add(290000);
	animations->Add(28000, ani);
	ani = new CAnimation(100);
	ani->Add(290001);
	animations->Add(28001, ani);
	ani = new CAnimation(100);
	ani->Add(290002);
	animations->Add(28002, ani);
	ani = new CAnimation(100);
	ani->Add(290003);
	animations->Add(28003, ani);
	ani = new CAnimation(100);
	ani->Add(290004);
	animations->Add(28004, ani);
	ani = new CAnimation(100);
	ani->Add(290005);
	animations->Add(28005, ani);
	ani = new CAnimation(100);
	ani->Add(290006);
	animations->Add(28006, ani);
	ani = new CAnimation(100);
	ani->Add(290007);
	animations->Add(28007, ani);





	mario = new CMario();
	mario->AddAnimation(400);		// idle right big
	mario->AddAnimation(401);		// idle left big
	mario->AddAnimation(402);		// idle right small
	mario->AddAnimation(403);		// idle left small

	mario->AddAnimation(500);		// walk right big
	mario->AddAnimation(501);		// walk left big
	mario->AddAnimation(502);		// walk right small
	mario->AddAnimation(503);		// walk left big

	mario->AddAnimation(599);		// die

	mario->AddAnimation(450);		//jum big up l
	mario->AddAnimation(451);		//jum big up r
	mario->AddAnimation(452);		//jum big down r
	mario->AddAnimation(453);		//jum big down l

	mario->AddAnimation(454);		//jum sm down r
	mario->AddAnimation(455);		//jum sm down l

	mario->AddAnimation(456);		//sitdown big r
	mario->AddAnimation(457);		//sitdown big l

	mario->AddAnimation(458);		//tail idle r
	mario->AddAnimation(459);		//tail idle l

	mario->AddAnimation(460);		//tail walk r
	mario->AddAnimation(461);		//l

	mario->AddAnimation(462);		//tail jumb up r
	mario->AddAnimation(463);		//tail jumb down r
	mario->AddAnimation(464);		//tail jumb up l
	mario->AddAnimation(465);		//tail jumb down l

	mario->AddAnimation(466);		//tail sitdown r
	mario->AddAnimation(467);		//tail sitdown l

	//orange
	mario->AddAnimation(468);		//idle r
	mario->AddAnimation(469);		//idle l

	mario->AddAnimation(470);		//walk r
	mario->AddAnimation(471);		//walk l

	mario->AddAnimation(472);		//jump up r
	mario->AddAnimation(473);		//jump down r


	mario->AddAnimation(474);		//jump  up l
	mario->AddAnimation(475);		//jump down l

	mario->AddAnimation(476);		//sit r
	mario->AddAnimation(477);		//sit  l

	mario->AddAnimation(478);		//shoot bullet r
	mario->AddAnimation(479);		//shoot bullet l

	mario->AddAnimation(480);		//tail spin r
	mario->AddAnimation(481);		//tail spin l

	mario->AddAnimation(482);		//fly shoot r
	
	mario->AddAnimation(483);		//fly tail r

	mario->AddAnimation(484);		//fly tail high r

	mario->AddAnimation(485);		//big bring koompashell;
	mario->AddAnimation(486);		//big rouse koompashell;

	mario->AddAnimation(487);		//big skid r
	mario->AddAnimation(488);		//big run l

	mario->AddAnimation(489);		//small run r
	mario->AddAnimation(490);		//small skid l

	mario->AddAnimation(491);		//big tail run r
	mario->AddAnimation(492);		//big tail skid l

	mario->AddAnimation(493);		//orange run r
	mario->AddAnimation(494);		//orange skid l

	mario->AddAnimation(495);		//tail rouse r
	mario->AddAnimation(496);		//tail bring r

	mario->AddAnimation(497);		//small rouse r
	mario->AddAnimation(498);		//small bring r

	mario->AddAnimation(499);		//orange rouse r
	mario->AddAnimation(600);		//orange bring r

	//mario->SetPosition(6399,1800);
	mario->SetPosition(5415, 1000);
	objects.push_back(mario);


	
	//=======================================================================================================================================
	/*for (int i = 0; i < 1; i++)
	{
		conco = new CConCo();
		conco->AddAnimation(901);
		conco->AddAnimation(902);
		conco->AddAnimation(903);
		conco->AddAnimation(904);
		conco->AddAnimation(905);
		conco->AddAnimation(906);
		conco->SetPosition(2600.0f, 200.0f);
		conco->SetState(CONCO_STATE_WALKING_LEFT);//CONCO_STATE_WALKING_LEFT
		objects.push_back(conco);
	}

	*/
	/*goomba = new CGoomba();
	goomba->AddAnimation(701);
	goomba->AddAnimation(702);
	goomba->AddAnimation(703);
	goomba->SetPosition(800, 100);
	goomba->SetState(GOOMBA_STATE_WALKING);
	objects.push_back(goomba);*/

	

/*	for (int i = 0; i < 5; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(100.0f + i*60.0f, 74.0f);
		objects.push_back(brick);

		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(100.0f + i*60.0f, 90.0f);
		objects.push_back(brick);

		brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(84.0f + i*60.0f, 90.0f);
		objects.push_back(brick);

		
	}*/
	/*CBrick* brick = new CBrick();
	brick->AddAnimation(601);
	brick->SetPosition(84.0f +3 * 60.0f, 90.0f);
	objects.push_back(brick);*/


	/*for (int i = 0; i < 90; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*48.0f, 300); //1 ủa  tại sao trừ  thì nó lại lúng xuống nhỉ? //honf ddas mas oi
		objects.push_back(brick);
	}*/

	// and Goombas 
	/*for (int i = 0; i < 4; i++)
	{
		goomba = new CGoomba();
		goomba->AddAnimation(701);
		goomba->AddAnimation(702);
		goomba->SetPosition(200 + i*60, 135);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
	}*/

	//add con co


	//hon da dong tien
/*	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(100.0f, 90.0f);
	//set state đâu?
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);*/


/*	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(170, 134);
	//set state đâu?
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);*/

	//chùm gạch đầu tiên
	/*brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(530,340);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);

	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(530+48-3, 340);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);

	//chùm gạch thứ 2
	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(677, 224);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);

	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(677+48-3, 224);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);

	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(530 , 340);
	//set state đâu?
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);*/


/*	ongnuoc = new OngNuoc();
	ongnuoc->AddAnimation(12001);
	ongnuoc->SetPosition(220.0f, 150-48);
	objects.push_back(ongnuoc);


*/

//1058, 388-2
	/*plant = new Plant();
	plant->AddAnimation(13001);
	plant->AddAnimation(13002);
	plant->AddAnimation(13003);
	plant->SetPosition(1058+96/2, 435);
	plant->SetState(PLANT_STATE_GOING_UP);
	//objects.insert(objects.begin() + 3, plant);
	objects.push_back(plant);*/

	VenusFireTrap *venus = new VenusFireTrap(1);
	venus->AddAnimation(13001);
	venus->AddAnimation(13002);
	venus->AddAnimation(13003);
	venus->AddAnimation(13004);
	venus->AddAnimation(13005);
	venus->AddAnimation(13006);
	venus->AddAnimation(13007);
	venus->AddAnimation(13008);
	venus->SetPosition(1058 + 96 / 2, 1080);
	venus->SetState(PLANT_STATE_GOING_UP);
	//objects.insert(objects.begin() + 3, plant);
	objects.push_back(venus);

	venus = new VenusFireTrap(2);
	venus->AddAnimation(13001);
	venus->AddAnimation(13002);
	venus->AddAnimation(13003);
	venus->AddAnimation(13004);
	venus->AddAnimation(13005);
	venus->AddAnimation(13006);
	venus->AddAnimation(13007);
	venus->AddAnimation(13008);
	venus->SetPosition(5615, 1130);
	venus->SetState(PLANT_STATE_GOING_UP);
	//objects.insert(objects.begin() + 3, plant);
	objects.push_back(venus);




	conco = new CConCo();
	conco->AddAnimation(901);
	conco->AddAnimation(902);
	conco->AddAnimation(903);
	conco->AddAnimation(904);
	conco->AddAnimation(905);
	conco->AddAnimation(906);
	conco->AddAnimation(907);
	conco->AddAnimation(908);
	conco->SetPosition(1745,391);
	conco->SetState(CONCO_STATE_WALKING_RIGHT);//CONCO_STATE_WALKING_LEFT
	objects.push_back(conco);
	
	brickcoin = new Brick_Coin(360);
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(200, 260);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);
	brickcoin = new Brick_Coin(360);
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(250, 260);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);
	brickcoin = new Brick_Coin(360);
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(300, 260);
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);

	SuperLeaf* super_leaf = new SuperLeaf(300, 360);
	super_leaf->AddAnimation(15000);
	super_leaf->SetState(SUPER_LEAF_STATE_MOVE_UP);
	super_leaf->SetPosition(300, 360);
	itemsMarioCanEat.push_back(super_leaf);

	brickblink = new BrickBlink();
	brickblink->AddAnimation(9001); // viên gạch lấp lánh
	brickblink->AddAnimation(19000); // đồng tiền
	brickblink->SetPosition(150.0f, 320.0f);
	brickblink->SetState(0);
	listBricks.push_back(brickblink);

	brickblink = new BrickBlink();
	brickblink->AddAnimation(9001); // viên gạch lấp lánh
	brickblink->AddAnimation(19000); // đồng tiền
	brickblink->SetPosition(450.0f, 520.0f);
	brickblink->SetState(0);
	listBricks.push_back(brickblink);

	brickblink = new BrickBlink();
	brickblink->AddAnimation(9001); // viên gạch lấp lánh
	brickblink->AddAnimation(19000); // đồng tiền
	brickblink->SetPosition(650.0f, 520.0f);
	brickblink->SetState(0);
	listBricks.push_back(brickblink);

	

	/*Mushroom* mr = new Mushroom(60, 60);
	mr->AddAnimation(11001);
	mr->SetPosition(300, 500);
	mr->SetState(MUSHROOM_STATE_GOING_UP);
	objects.push_back(mr);

	 mr = new Mushroom(60, 60);
	mr->AddAnimation(11001);
	mr->SetPosition(400, 500);
	mr->SetState(MUSHROOM_STATE_GOING_UP);
	objects.push_back(mr);

	 mr = new Mushroom(60, 60);
	mr->AddAnimation(11001);
	mr->SetPosition(500, 500);
	mr->SetState(MUSHROOM_STATE_GOING_UP);
	objects.push_back(mr);*/

	ParaGoomba* para_goomba = new ParaGoomba();
	para_goomba->AddAnimation(17000);
	para_goomba->AddAnimation(17001);
	para_goomba->AddAnimation(17002);
	para_goomba->AddAnimation(17003);
	para_goomba->AddAnimation(17004);
	para_goomba->SetState(PARA_GROOMBA_STATE_JUMP_BIG);
	para_goomba->SetPosition(500, 460);
	objects.push_back(para_goomba);


	PiranhaPlant* paranha_plant = new PiranhaPlant();
	paranha_plant->AddAnimation(18000);
	paranha_plant->SetState(PIRANHA_PLANT_STATE_GOING_UP);
	paranha_plant->SetPosition(5424, 1160);
	objects.push_back(paranha_plant);

	Coin* coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(500, 360);
	itemsMarioCanEat.push_back(coin);

	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(650, 360);
	itemsMarioCanEat.push_back(coin);

	 coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(700, 360);
	itemsMarioCanEat.push_back(coin);





	//coin dưới lòng đất:

	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6606, 1512);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6606, 1704);
	itemsMarioCanEat.push_back(coin);

	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6654, 1464);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6654, 1608);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6654, 1752);
	itemsMarioCanEat.push_back(coin);

	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6702, 1464);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6702, 1608);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6702, 1752);
	itemsMarioCanEat.push_back(coin);

	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6750, 1512);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6750, 1560);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6750, 1656);
	itemsMarioCanEat.push_back(coin);
	coin = new Coin();
	coin->AddAnimation(19000);
	coin->SetPosition(6750, 1704);
	itemsMarioCanEat.push_back(coin);





/*	SwitchBlock* switch_block = new SwitchBlock();
	switch_block->AddAnimation(20000);
	switch_block->AddAnimation(20001);
	switch_block->SetState(SWITCH_BLOCK_STATE_INIT);
	switch_block->SetPosition(600, 360);
	objects.push_back(switch_block);*/
	
//==========================================================================================================================================


	//viên đá lấp lánh <3

	/*brickblink = new BrickBlink();
	brickblink->AddAnimation(9001);
	brickblink->SetPosition(100.0f, 90.0f);
	brickblink->SetState(100);
	objects.push_back(brickblink);*/


	/*Mushroom* mr = new Mushroom();
	mr->AddAnimation(11001);
	mr->SetPosition(150.0f, 90.0f);
	mr->SetState(100);
	objects.push_back(mr);*/


	/*mario_bullet = new MarioBullet();
	mario_bullet->AddAnimation(14001);
	mario_bullet->AddAnimation(14002);
	mario_bullet->SetPosition(100,50);
	//set state đâu?
	mario_bullet->SetState(100);
	objects.push_back(mario_bullet);*/


	//cổng thử nghiệm:
	//cổng trên đất
	Hub* hub = new Hub();
	objects.push_back(hub);

	Pmeter* pmeter = new Pmeter();
	pmeter->AddAnimation(28000);
	pmeter->AddAnimation(28001);
	pmeter->AddAnimation(28002);
	pmeter->AddAnimation(28003);
	pmeter->AddAnimation(28004);
	pmeter->AddAnimation(28005);
	pmeter->AddAnimation(28006);
	pmeter->AddAnimation(28007);
	objects.push_back(pmeter);

	flatform = new Flatform(50, 70);
	flatform->SetPosition(300, 1194);
	flatform->is_portal = true;
	objects.push_back(flatform);

	//cổng dưới đất
	flatform = new Flatform(50, 70);
	flatform->SetPosition(2151*3, 540*3);
	flatform->is_portal = true;
	objects.push_back(flatform);


	//chặt đầu chặt cuối:
	flatform = new Flatform(5, 700);
	flatform->SetPosition(0, 916);
	objects.push_back(flatform);

	flatform = new Flatform(5, 700);
	flatform->SetPosition(8447, 916);
	objects.push_back(flatform);

	//nền
	//1
	flatform = new Flatform(1872, 5);
	flatform->SetPosition(0,1248 ); //532 + 700
	objects.push_back(flatform);


	//2
	flatform = new Flatform(1390, 5);//nền cao  Flatform(1392, 100)onkeyup//1390
	flatform->SetPosition(1872, 1200);
	objects.push_back(flatform);


	//3
	flatform = new Flatform(1052, 5);
	flatform->SetPosition(3470, 1248 );
	objects.push_back(flatform);

	//4
	flatform = new Flatform(230, 5);
	flatform->SetPosition(4620, 1248);
	objects.push_back(flatform);

	flatform = new Flatform(1724, 5);
	flatform->SetPosition(5005, 1248);
	objects.push_back(flatform);

	//6
	flatform = new Flatform(2000, 5);
	flatform->SetPosition(6782, 1248);
	objects.push_back(flatform);


	// dưới nền demo:
	flatform = new Flatform(1000, 5);
	flatform->SetPosition(6288, 1872);
	objects.push_back(flatform);

	//chùm 3 gạch thiệt bự tăng dần chiều cao



	/*//4
	flatform = new Flatform(233, 5);
	flatform->SetPosition(4610, 532);
	objects.push_back(flatform);

	flatform = new Flatform(3500, 5);
	flatform->SetPosition(4993, 532);
	objects.push_back(flatform);*/

	//chùm ô vuông đầu tiên:
	flatform = new Flatform(144, 5);
	flatform->SetPosition(722, 388-2);
	objects.push_back(flatform);

	flatform = new Flatform(144, 5);
	flatform->SetPosition(815,288);
	objects.push_back(flatform);

	//ống nước
	//1
	flatform = new Flatform(91, 144);
	flatform->SetPosition(1058, 388-2);
	objects.push_back(flatform);

	//2 3
	flatform = new Flatform(91, 94);
	flatform->SetPosition(5376, 438);
	objects.push_back(flatform);

	flatform = new Flatform(91, 144);
	flatform->SetPosition(5568, 386);
	objects.push_back(flatform);

	//hai cái chụm
	flatform = new Flatform(96, 248);
	flatform->SetPosition(6768, 0);
	objects.push_back(flatform);

	flatform = new Flatform(96, 144);
	flatform->SetPosition(6768, 390);
	objects.push_back(flatform);

	//ống nước cuối 
	flatform = new Flatform(96, 144);
	flatform->SetPosition(6960, 438);
	objects.push_back(flatform);

	//group 4 cục: x-c-t-x

	//chùm gach bự
	//x
	flatform = new Flatform(243, 5);
	flatform->SetPosition(1199, 386);
	objects.push_back(flatform);

	//c
	flatform = new Flatform(183, 5);
	flatform->SetPosition(1394, 288);
	objects.push_back(flatform);

	//t
	flatform = new Flatform(188, 5);
	flatform->SetPosition(1537, 193);
	objects.push_back(flatform);


	//x
	flatform = new Flatform(286, 5);
	flatform->SetPosition(1537, 432);
	objects.push_back(flatform);

	//chùm 3 gạch bự:

	//
	flatform = new Flatform(333, 5);
	flatform->SetPosition(3794, 436);
	objects.push_back(flatform);

	//
	flatform = new Flatform(334, 5);
	flatform->SetPosition(3893, 338);
	objects.push_back(flatform);

	//
	flatform = new Flatform(328, 5);
	flatform->SetPosition(3984, 243);
	objects.push_back(flatform);

	//chùm 2 gạch bự:

		//
	flatform = new Flatform(144, 5);
	flatform->SetPosition(6432, 338+50);
	objects.push_back(flatform);

	//
	flatform = new Flatform(144, 5);
	flatform->SetPosition(6528, 50+50);
	objects.push_back(flatform);
	


	//gạch đá bình thường:
	//2 chụm đầu
	flatform = new Flatform(48*2, 48);
	flatform->SetPosition(4515, 300-15);
	objects.push_back(flatform);

	//chùm đối xứng:
	flatform = new Flatform(48 * 3, 48);
	flatform->SetPosition(4706, 485);
	objects.push_back(flatform);

	flatform = new Flatform(48 * 2, 48);
	flatform->SetPosition(4706+48, 485-48);
	objects.push_back(flatform);

	flatform = new Flatform(48 *1, 48);
	flatform->SetPosition(4706+48*2, 485-48*2);
	objects.push_back(flatform);

	//chùm đối xứng:
	flatform = new Flatform(48 * 3, 48);
	flatform->SetPosition(4993, 485);
	objects.push_back(flatform);

	flatform = new Flatform(48 * 2, 48);
	flatform->SetPosition(4993, 485-48);
	objects.push_back(flatform);

	flatform = new Flatform(48 * 1, 48);
	flatform->SetPosition(4993, 485-48*2);
	objects.push_back(flatform);

	//DebugOut(L"[ERROR------------------------------] day la sizeeeeeee:  %d\n", objects.size());


	//map
	/*void Map::LoadMap(int id,
	LPCWSTR mapFilePath,
	int RowMap,
	int ColumnMap,
	LPCWSTR mapFileTexture,
	int RowTile,
	int ColumnTile,
	int TileFrameWidth,
	int TileFrameHeight)*/
	map = new Map();
	map->LoadMap(0, L"textures\\map_thanh.txt", 41, 176, L"textures\\Final1.png", 30, 29, 48, 48);

	game_ui = new UI();


}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)  // chừa vị trí mario 
	{
		coObjects.push_back(objects[i]);
	}


	// push listbick vô trong mảng object
	for (int i = 0; i < listBricks.size(); i++)
	{
		//listBricks[i]->Update(dt, &coObjects);
		coObjects.push_back(listBricks[i]);
	}



	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}


	for (int i = 0; i < listBricks.size(); i++)
	{
		listBricks[i]->Update(dt, &coObjects);
	}



	for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		itemsMarioCanEat[i]->Update(dt, &coObjects);
	}


	mario->CheckOverlapWithItems(&itemsMarioCanEat);

	//remove objects which is used
	for (auto& pointer : objects)
	{
		if (pointer->used == true)
		{
			/*if (dynamic_cast<SuperLeaf*>(pointer))
				DebugOut(L"xoas roi ne!\n");
				*/
			delete pointer;
			pointer = nullptr;
			DebugOut(L"xoas roi ne!\n");
		}
	}
	objects.erase(std::remove(objects.begin(), objects.end(), nullptr), objects.end());

	//remove itmes which is used
	for (auto& item : itemsMarioCanEat)
	{
		if (item->used == true)
		{
			/*if (dynamic_cast<SuperLeaf*>(pointer))
				DebugOut(L"xoas roi ne!\n");
				*/
			delete item;
			item = nullptr;
			DebugOut(L"xoas roi ne!\n");
		}
	}
	itemsMarioCanEat.erase(std::remove(itemsMarioCanEat.begin(), itemsMarioCanEat.end(), nullptr), itemsMarioCanEat.end());


	for (auto& item : listBricks)
	{
		if (item->used == true)
		{
			/*if (dynamic_cast<SuperLeaf*>(pointer))
				DebugOut(L"xoas roi ne!\n");
				*/
			delete item;
			item = nullptr;
			DebugOut(L"xoas roi ne!\n");
		}
	}
	listBricks.erase(std::remove(listBricks.begin(), listBricks.end(), nullptr), listBricks.end());


	GameTime::GetInstance()->Update(dt);



/*	vector<LPGAMEOBJECT> coObjects;

	for (int i = 0; i < objects.size(); i++)
	{
		
		for (int j = 0; j <  objects.size(); j++)
		{
			if(j!=i)
				coObjects.push_back(objects[j]);
		}

		objects[i]->Update(dt, &coObjects);
		coObjects.clear();
	}*/
	


	// Update camera to follow mario
	float cx, cy;
	mario->GetPosition(cx, cy);


		
	cx -= SCREEN_WIDTH / 2; // set cam sao cho mario ở giữa màn hình
	cy -= SCREEN_HEIGHT / 2;

	cx += 200;// camera tiến lên xíu
	//cho cái cam bằng nửa chiều cao, chiều rộng của mario
	//xét cái chiều x của camera bằng chiều x của mario  như vậy nó sẽ đi theo thằng mario

	if (cx < 0)
		return;
	if (cx > 8447 - SCREEN_WIDTH+MARIO_BIG_BBOX_WIDTH/2)
		return;

	if(mario->is_on_the_ground==false)
		CGame::GetInstance()->SetCamPos(cx, 700 );

	
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		map->Draw();
		game_time = GameTime::GetInstance();
		//game_ui->Render(300-game_time->GetTime());

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		for (int i = 0; i < itemsMarioCanEat.size(); i++)
			itemsMarioCanEat[i]->Render();

		for (int i = 0; i < listBricks.size(); i++)
			listBricks[i]->Render();
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	
	Run();

	return 0;
}