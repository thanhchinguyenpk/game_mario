#include "Pmeter.h"

void Pmeter::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void Pmeter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Pmeter::Render()
{

	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();
	//CSprites::GetInstance()->Get(280000)->DrawFlipX(x + 20 + 76 * 3, y + 730 - 100 + 10 + 5);
	animations[0]->Render(x + 20 + 76 * 3, y + 730 - 100 + 10 + 5, 0, 255, 1, 1);
}
