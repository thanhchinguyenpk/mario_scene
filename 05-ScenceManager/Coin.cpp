#include "Coin.h"

void Coin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x- COIN_BBOX_WIDTH/2;
	top = y- COIN_BBOX_HEIGHT/2;
	right = x + COIN_BBOX_WIDTH/2;
	bottom = y + COIN_BBOX_HEIGHT/2;
}


void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Coin::Render()
{
	int direction = 1;
	int ny = 1;

	animations[0]->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

void Coin::SetState(int state)
{
}
