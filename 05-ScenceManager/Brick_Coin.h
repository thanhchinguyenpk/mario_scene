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


#define BRICK_COIN_ANI_CHUA_DAP	 0
#define BRICK_COIN_ANI_DA_DAP	 1
#define BRICK_COIN_ANI_BLINK_BLINK	 2

#define IS_QUESTION		0
#define IS_BLINK		1

//extern vector<LPGAMEOBJECT> itemsMarioCanEat;

class Brick_Coin : public CGameObject
{

	//float originalX;
public:

	int brick_type = 0; //0 ? chứ tiền, 1 ? chưa item, 2 ? nam xam, 3 blink nam xanh, 4 blink chua item

	CMario * mario = NULL;
	float originalY;

	int is_contain_button_p = 0;
	//int is_contain_item = 0;
	
	bool is_hit = false;
	bool dropped = false;
	bool flag = false;

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void SetState(int state);
	Brick_Coin(float pos_y, CMario * player,int is_has_button_p,int type_brick);
};
