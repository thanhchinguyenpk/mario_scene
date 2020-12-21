#include <algorithm>
#include "CoinFly.h"
#include "debug.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <vector>

extern vector<LPGAMEOBJECT> objects;

void CoinFly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + COIN_FLY_BBOX_WIDTH;
	bottom = y + COIN_FLY_BBOX_HEIGHT;
}

void CoinFly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	//x += dx;
	//x = 50;
	if (GetTickCount() - fly_up_start < COIN_FLY_UP_TIME) //thời gian mới sinh ra cho đến khi
	{														// đổi chiều
		y -= dy;
		//DebugOut(L"[ERROR------------------------------] dang congggggggggggg \n");
	}
	else
	{
		//DebugOut(L"[ERROR------------------------------] dang truuuuuuuuuuuu \n");
		
		if(GetTickCount() - fly_up_start <= COIN_FLY_BECOME_MARK)
			y += dy; // hồi nảy lọt zô đây
		else if(GetTickCount() - fly_up_start > COIN_FLY_BECOME_MARK)//thời gian sinh ra bay len bay xuong cho đến khi biến
		{		
			SetState(COIN_FLY_STATE_MARK);
			y -= dy;

			if (GetTickCount() - fly_up_start > COIN_FLY_DISAPEAR)
			{
				objects.pop_back();
				delete this;
			}
		}
		
		
		
	}

	

	//DebugOutTitle(L"01 - Skeleton %0.1f, %0.1f", fly_up_start , this->y);
	//DebugOut(L"[ERROR-----------***------------------] DINPUT::GetDeviceData failed. Error: %f\n", this->fly_up_start);


}

void CoinFly::Render()
{
	int ani = 0;
	if (state == COIN_FLY_STATE_FLY)
		ani = COIN_FLY_ANI_FLY;
	else if (state == COIN_FLY_STATE_MARK)
		ani = COIN_FLY_ANI_MARK;

	animations[ani]->Render(x, y);
}

void CoinFly::SetState(int state)
{
	CGameObject::SetState(state);
	
	vy = GOOMBA_WALKING_SPEED;


	/*switch (state)
	{
	case COIN_FLY_STATE_FLY:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	*/
	//vx = 0;
}

void CoinFly::StartFlyUp()
{
	fly_up_start = GetTickCount();
	DebugOut(L"[ERROR------------------------------]BAT DAU BAY: %d \n", this->y);
}

CoinFly::CoinFly()
{
	//fist_position = this->y;
	
	this->AddAnimation(8001);
	this->AddAnimation(10001);
	this->SetPosition(100.0f, 90.0f);
	this->SetState(COIN_FLY_ANI_FLY);

	
}

CoinFly::~CoinFly()
{
}
