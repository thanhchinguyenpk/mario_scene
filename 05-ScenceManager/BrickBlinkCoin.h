#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayScence.h"
#include "Mario.h"

#define BRICK_COIN_BBOX_WIDTH  16*3
#define BRICK_COIN_BBOX_HEIGHT 16*3

#define BRICK_COIN_STATE_CHUA_DAP	100
#define BRICK_COIN_STATE_DA_DAP 	200
#define BRICK_COIN_STATE_BOUCING 	300
#define BRICK_COIN_STATE_STAND_STILL 400


#define BRICK_COIN_ANI_CHUA_DAP	 0
#define BRICK_COIN_ANI_DA_DAP	 1
#define BRICK_COIN_ANI_BLINK_BLINK	 2

class BrickBlinkCoin : public CGameObject
{

	//float originalX;
public:

	int count_to_stand_still = 0;

	CMario * mario = NULL;
	float originalY;



	bool is_hit = false;
	bool dropped = false;
	bool flag = false;

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void SetState(int state);
	BrickBlinkCoin(float pos_y, CMario * player);
};

