#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "Game.h"
#include "TextAndNumber.h"

#include "debug.h"
#include "Scence.h"
#include "Game.h"
#include "PlayScence.h"

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

#define MUSHROOM_CARD 1
#define STAR_MAN_CARD 2
#define FIRE_FLOWER_CARD 3

class RandomBonus:public CGameObject
{
public:
	CMario *mario = NULL;
	bool got_bonus = false;
	DWORD start_ani = 0;
	int cart_after_text = 0;
	RandomBonus(CMario *player);

	TextAndNumber text;
	DWORD time_order_to_render_text = 0;

	~RandomBonus() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects );
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

