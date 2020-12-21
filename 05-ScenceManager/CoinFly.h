#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.15f;

#define COIN_FLY_BBOX_WIDTH 16*3
#define COIN_FLY_BBOX_HEIGHT 15*3


#define COIN_FLY_STATE_FLY 100
#define COIN_FLY_STATE_MARK 200

#define COIN_FLY_ANI_FLY 0
#define COIN_FLY_ANI_MARK 1


#define COIN_FLY_UP_TIME 400
#define COIN_FLY_BECOME_MARK 700
#define COIN_FLY_DISAPEAR 900


class CoinFly : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int fly_up;
	DWORD fly_up_start;
	int fist_position;


public:
	virtual void SetState(int state);


	virtual void StartFlyUp();
	CoinFly();
	~CoinFly();
};
