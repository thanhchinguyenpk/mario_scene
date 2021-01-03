#pragma once

#include "GameObject.h"
#include "Mario.h"

#define RANDOMBONUS_BBOX_WIDTH 48
#define RANDOMBONUS_BBOX_HEIGHT 48

#define STATE_RANDOM_BONUS_MUSHROOM		0
#define STATE_RANDOM_BONUS_STAR			1
#define STATE_RANDOM_BONUS_FIRE_FLOWER	2
#define STATE_GOT_BONUS_MUSHROOM		3
#define STATE_GOT_BONUS_STAR			4
#define STATE_GOT_BONUS_FIRE_FLOWER		5

#define ANI_BONUS_MUSHROOM			0
#define ANI_BONUS_STAR				1
#define ANI_BONUS_FIRE_FLOWER		2
#define ANI_GOT_BONUS_MUSHROOM		3
#define ANI_GOT_BONUS_STAR			4
#define ANI_GOT_BONUS_FIRE_FLOWER	5

class RandomBonus:public CGameObject
{
public:
	CMario *mario = NULL;
	bool got_bonus = false;
	DWORD start_ani = 0;
	RandomBonus(CMario *player);
	~RandomBonus() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects );
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

