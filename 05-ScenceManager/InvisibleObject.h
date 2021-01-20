#pragma once

#include "GameObject.h"
#include "Textures.h"
#include "Game.h"

#define STATE_GHOST_PLATFORM 0
#define STATE_CACTUS 1
#define STATE_HELP_TAG 2
#define STATE_GUARD 3
#define STATE_CURTAIN 4
#define STATE_3_INTRO 5
#define STATE_ARROW 6


#define ANI_GHOST_PLATFORM 0
#define ANI_CACTUS 1
#define ANI_HELP_TAG 2
#define ANI_GUARD 3
#define ANI_CURTAIN 4
#define ANI_3_INTRO 5
#define ANI_ARROW 6


class InvisibleObject : public CGameObject
{
public:
	int w;
	int h;
	InvisibleObject(float x, float y, float width, float height, int state = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects );
	virtual void Render();
};

