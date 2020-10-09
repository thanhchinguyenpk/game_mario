#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = 0.07f;
}

void CGameObject::Update(DWORD dt)
{
	x += vx*dt;
	if ((vx>0 && x > 290) || (x < 0 && vx<0)) vx=-vx;
	// tại sao lại có điều kiện
}

void CGameObject::Render()
{
	LPANIMATION ani;
	LPANIMATION aniFrog;
	//if (vx>0) ani = animations[0]; else ani = animations[1];

			//if (vx>0) ani = CAnimations::GetInstance()->Get(500); 
			//else ani = CAnimations::GetInstance()->Get(501);

	if (vx > 0) aniFrog = CAnimations::GetInstance()->Get(800);
	else aniFrog = CAnimations::GetInstance()->Get(801);

	//ani = animations[0];
			//ani->Render(x, y);
	aniFrog->Render(x, y);
}

CGameObject::~CGameObject()
{
}