#pragma once
#include "GameObject.h"
#include "Mario.h"

#define	 BROTHER_BBOX_WIDTH 48
#define	 BROTHER_BBOX_HEIGHT 72

//vy = -0.25*3;
#define  BROTHER_WALKING_SPEED			 0.1f;

#define  BROTHER_STATE_MOVE_LEFT		100
#define  BROTHER_STATE_MOVE_RIGHT		200
#define  BROTHER_STATE_JUMP_SMALL		300

#define	 BROTHER_SPEED_VERTICAL		0.1


#define  BROTHER_GRAVITY		0.0009

class BoomerangBrother :public CGameObject
{
public:
	CMario * mario = NULL;
	float original_x=0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	BoomerangBrother(float x,CMario *player);
};
