#pragma once
#include "GameObject.h"

#define  DEBRIS_BRICK_GRAVITY		0.0009
#define  DEBRIS_BRICK_SPEED_X		0.07
#define  DEBRIS_BRICK_SPEED_Y		0.26

class DebrisBrick : public CGameObject
{
public:

	DebrisBrick(float brick_pos_x, float brick_pos_y, int nx, float height);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	

};

