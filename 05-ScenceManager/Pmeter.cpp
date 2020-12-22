#include "Pmeter.h"
#include "Game.h"
Pmeter::Pmeter(CMario * player)
{
	mario = player;
}
void Pmeter::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

void Pmeter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void Pmeter::Render()
{

	float speed = abs(mario->vx);
	if (speed < 0.33)
		lv = 0;
	else if (speed < 0.38)
		lv = 1;
	else if (speed < 0.42)
		lv = 2;
	else if (speed < 0.47)
		lv = 3;
	else if (speed < 0.50)
		lv = 4;
	else if (speed < 0.53)
		lv = 5;
	else if (speed < 0.55)
		lv = 6;
	else if (speed < 0.59)
		lv = 7;
	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();
	//CSprites::GetInstance()->Get(280000)->DrawFlipX(x + 20 + 76 * 3, y + 730 - 100 + 10 + 5);
	animation_set->at(lv)->Render(x + 20 + 76 * 3+10+10+5, y + 730 - 100 + 10 - 5, 0, 255, 1, 1);
}
