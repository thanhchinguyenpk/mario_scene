#pragma once
#include "GameObject.h"

#define CONCO_WALKING_SPEED			 0.01f;
#define CONCO_MAI_RUA_CHAY_SPEED	 0.1f;

#define COIN_BBOX_WIDTH		 14*3 //ok
#define COIN_BBOX_HEIGHT		 16*3 //ok
#define CONCO_BBOX_HEIGHT_DIE	 9

#define CONCO_STATE_WALKING_LEFT	100
#define CONCO_STATE_DIE				200
#define CONCO_STATE_WALKING_RIGHT	300
#define CONCO_STATE_THUT_VAO		400
#define CONCO_STATE_MAI_RUA_CHAY	500

#define CONCO_ANI_WALKING_LEFT	 0
#define CONCO_ANI_WALKING_RIGHT	 1
#define CONCO_ANI_THUT_VAO		 2
#define CONCO_ANI_MAI_RUA_CHAY	 3
#define CONCO_ANI_DIE			 4

class Coin : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	virtual void SetState(int state);
};

