#pragma once
#include "GameObject.h"



#define COIN_BBOX_WIDTH		 14*3 //ok
#define COIN_BBOX_HEIGHT		 16*3 //ok
#define CONCO_BBOX_HEIGHT_DIE	 9



class Coin : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	virtual void SetState(int state);
};

