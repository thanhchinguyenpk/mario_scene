#include "Hub.h"
#include "Game.h"

void Hub::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void Hub::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Hub::SetState(int state)
{
}

void Hub::Render()
{
	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();
	CSprites::GetInstance()->Get(280000)->DrawFlipX(x+20+76*3, y+ 730-100+10+5);
	//animations[0]->Render(x, y, 0, 255, 1, 1);
}
