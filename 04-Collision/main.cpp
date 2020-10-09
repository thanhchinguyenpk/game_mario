/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

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

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH	 320
#define SCREEN_HEIGHT	 240

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
vector<LPGAMEOBJECT> objects;

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




class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		if(mario->GetIsInObject()==true)
		{
			mario->SetState(MARIO_STATE_JUMP);
			mario->SetIsInObject(false);
		}
		
		break;
	case DIK_A: // reset
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(50.0f,0.0f);
		mario->SetSpeed(0, 0);
		break;
	case DIK_DOWN:
		mario->SetPosition(mario->x,mario->y+ MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITDOWN_BBOX_HEIGHT );
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	
	case DIK_DOWN:
		DebugOut(L"UPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPp\n", KeyCode);
		mario->SetPosition(mario->x, mario->y - MARIO_BIG_BBOX_HEIGHT + MARIO_BIG_SITDOWN_BBOX_HEIGHT  );
		break;
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else if(game->IsKeyDown(DIK_DOWN))
		mario->SetState(MARIO_STATE_SITDOWN);
	else
		mario->SetState(MARIO_STATE_IDLE);
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



	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	LPDIRECT3DTEXTURE9 texMarioPro = textures->Get(ID_TEX_MARIOPRO);

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

	
		


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite



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
	sprites->Add(130001, 189, 71, 189 + 16, 71 + 33, texPlant);
	sprites->Add(130002, 189, 35, 189 + 16, 35 + 31, texPlant);
	sprites->Add(130003,   6, 71,   6 + 17, 71 + 32, texPlant);
	sprites->Add(130004,   6, 33,   6 + 17, 33 + 33, texPlant);
	



	





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

	ani = new CAnimation(100);		// Mario b jum up  l
	ani->Add(10100);
	animations->Add(450, ani);

	ani = new CAnimation(100);		// Mario b jum up  r
	ani->Add(10101);
	animations->Add(451, ani);

	ani = new CAnimation(100);		// Mario b jum down r
	ani->Add(10102);
	animations->Add(452, ani);
	
	ani = new CAnimation(100);		// Mario b jum down l
	ani->Add(10103);
	animations->Add(453, ani);

	//=====
	ani = new CAnimation(100);		// Mario b jum down l
	ani->Add(10034);
	animations->Add(454, ani);

	ani = new CAnimation(100);		// Mario b jum down l
	ani->Add(10035);
	animations->Add(455, ani);

	ani = new CAnimation(100);		// Mario b sitdowm r
	ani->Add(10104);
	animations->Add(456, ani);

	ani = new CAnimation(100);		// Mario b sitdowm l
	ani->Add(10105);
	animations->Add(457, ani);

	



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

	ani = new CAnimation(300); //rùa bay trái
	ani->Add(60009);
	ani->Add(60010);
	ani->Add(60011);
	ani->Add(60012);
	animations->Add(905, ani);

	ani = new CAnimation(300); //rùa bay phải
	ani->Add(60013);
	ani->Add(60014);
	ani->Add(60015);
	ani->Add(60016);
	animations->Add(906, ani);

	
	

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

	//plant
	ani = new CAnimation(200); // go up
	ani->Add(130001);
	ani->Add(130002);
	animations->Add(13001, ani);

	ani = new CAnimation(200); //shooting up
	ani->Add(130003);
	animations->Add(13002, ani);

	ani = new CAnimation(200); //shooting down
	ani->Add(130004);
	animations->Add(13003, ani);














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

	mario->SetPosition(50.0f, 0);
	objects.push_back(mario);

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
	CBrick* brick = new CBrick();
	brick->AddAnimation(601);
	brick->SetPosition(84.0f +3 * 60.0f, 90.0f);
	objects.push_back(brick);


	for (int i = 0; i < 90; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*16.0f, 150); // ủa  tại sao trừ  thì nó lại lúng xuống nhỉ? //honf ddas mas oi
		objects.push_back(brick);
	}

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
/*	for (int i = 0; i < 1; i++)
	{
		conco = new CConCo();
		conco->AddAnimation(901);
		conco->AddAnimation(902);
		conco->AddAnimation(903);
		conco->AddAnimation(904);
		conco->AddAnimation(905);
		conco->AddAnimation(906);
		conco->SetPosition(200 + i*60, 135-12);
		conco->SetState(CONCO_STATE_FLY_RIGHT);
		objects.push_back(conco);
	}*/


	//hon da dong tien
	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(100.0f, 90.0f);
	//set state đâu?
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);


	brickcoin = new Brick_Coin();
	brickcoin->AddAnimation(1001);
	brickcoin->AddAnimation(1002);
	brickcoin->SetPosition(170, 134);
	//set state đâu?
	brickcoin->SetState(BRICK_COIN_STATE_CHUA_DAP);
	objects.push_back(brickcoin);


/*	ongnuoc = new OngNuoc();
	ongnuoc->AddAnimation(12001);
	ongnuoc->SetPosition(220.0f, 150-48);
	objects.push_back(ongnuoc);

	plant = new Plant();
	plant->AddAnimation(13001);
	plant->AddAnimation(13002);
	plant->AddAnimation(13003);
	plant->SetPosition(227.0f, 150 - 48);
	plant->SetState(PLANT_STATE_WALKING);
	objects.insert(objects.begin() + 3, plant);*/



	


	
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


	DebugOut(L"[ERROR------------------------------] day la sizeeeeeee:  %d\n", objects.size());


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

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}

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

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	//cho cái cam bằng nửa chiều cao, chiều rộng của mario
	//xét cái chiều x của camera bằng chiều x của mario  như vậy nó sẽ đi theo thằng mario

	CGame::GetInstance()->SetCamPos(cx+90, 0.0f /*cy*/);
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

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

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
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

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

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}