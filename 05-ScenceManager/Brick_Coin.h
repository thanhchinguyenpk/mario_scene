#pragma once
#include "GameObject.h"

#define BRICK_COIN_BBOX_WIDTH  16*3
#define BRICK_COIN_BBOX_HEIGHT 16*3

#define BRICK_COIN_STATE_CHUA_DAP	100
#define BRICK_COIN_STATE_DA_DAP 	200
#define BRICK_COIN_STATE_BOUCING 	300


#define BRICK_COIN_ANI_CHUA_DAP	 0
#define BRICK_COIN_ANI_DA_DAP	 1

//extern vector<LPGAMEOBJECT> itemsMarioCanEat;

class Brick_Coin : public CGameObject
{

	//float originalX;
	float originalY;
	
	bool is_hit = false;
	bool flag = false;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void SetState(int state);
	Brick_Coin(float pos_y);
};
