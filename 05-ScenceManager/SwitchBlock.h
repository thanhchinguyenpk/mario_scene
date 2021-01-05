#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayScence.h"

#define SWITCH_BLOCK_BBOX_WIDTH 16*3
#define SWITCH_BLOCK_BBOX_HEIGHT 16*3

#define SWITCH_BLOCK_STATE_INIT 100
#define SWITCH_BLOCK_STATE_WAS_PRESSED 200
#define SWITCH_BLOCK_STATE_BRICK_FOREVER 300


//extern vector<LPGAMEOBJECT> listBricks;

class SwitchBlock :public CGameObject
{
public:

	TimerCustom* time_to_retransform = new TimerCustom(5000);
	bool transform_one_time = false;

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	void StartTransformListBrick(vector<LPGAMEOBJECT>* listBricks);
};

