#include "BrickBlinkCoin.h"
#include "Brick_Coin.h"
#include <dinput.h>
#include "debug.h"
#include "Mushroom.h"
#include "SwitchBlock.h"

//extern vector<LPGAMEOBJECT> objects;

void BrickBlinkCoin::Render()
{
	int ani = BRICK_COIN_ANI_BLINK_BLINK;

	
	//DebugOut(L"[ERROR------------------------------] DINPUT::GetDeviceData failed. Error: %d\n", ani);
	if (state == BRICK_COIN_STATE_STAND_STILL)
		ani = BRICK_COIN_ANI_DA_DAP;

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}



void BrickBlinkCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;

	

	if (y < originalY - 20 && flag == false)
	{
		vy = -vy;
		flag = true;
	}

	else if (flag == true && y >= originalY)
	{
		//DebugOut(L"[ERROR-------vy của viên gạch-----------------] DINPUT::GetDeviceData failed. Error: %f\n",y);

		vy = 0;
		y = originalY;
		//is_hit = true;
		flag = false;
	}

	//DebugOut(L"[ERROR-------vy của viên gạch-----------------] DINPUT::GetDeviceData failed. Error: %f\n", originalY);
}

void BrickBlinkCoin::SetState(int state)
{

	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_COIN_STATE_DA_DAP:
		vy = -0.4f;
		break;
	case BRICK_COIN_STATE_STAND_STILL:
		vx = 0;
		vy = 0;
		break;


	}

}

BrickBlinkCoin::BrickBlinkCoin(float pos_y, CMario * player)
{
	// originalX = x;
	mario = player;
	this->originalY = pos_y;

}


void BrickBlinkCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_COIN_BBOX_WIDTH / 2;
	t = y - BRICK_COIN_BBOX_HEIGHT / 2;
	r = x + BRICK_COIN_BBOX_WIDTH / 2;
	b = y + BRICK_COIN_BBOX_HEIGHT / 2;
}

