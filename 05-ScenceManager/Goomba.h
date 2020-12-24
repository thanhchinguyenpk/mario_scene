#pragma once
#include "GameObject.h"
#include "TimerCustom.h"
#include "Mario.h"
#include "MoneyEffect.h"
#define GOOMBA_WALKING_SPEED 0.01f;
#define GOOMBA_GRAVITY			0.002f*1.5

#define GOOMBA_BBOX_WIDTH 16*3
#define GOOMBA_BBOX_HEIGHT 15*3
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_WAS_SHOOTED 300

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_WAS_SHOOTED 2

//extern CMario* mario;

class CGoomba : public CGameObject
{
public:
	MoneyEffect *effect = NULL;
	CMario* mario;
	TimerCustom* time_to_disapear = new TimerCustom(400);
	CGoomba(CMario* player);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();



	virtual void SetState(int state);
};