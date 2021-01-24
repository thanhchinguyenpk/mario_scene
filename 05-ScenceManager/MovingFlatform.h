#pragma once

#include "GameObject.h"
#include "Mario.h"

#define	 MOVING_FLATFORM_BBOX_WIDTH 48*3
#define	 MOVING_FLATFORM_BBOX_HEIGHT 16*3

#define	MOVING_FLATFORM_WALKING_SPEED			0.05f// 0.09f;

#define  MOVING_FLATFORM_STATE_MOVE_LEFT		100
#define  MOVING_FLATFORM_STATE_MOVE_RIGHT		200
#define  MOVING_FLATFORM_STATE_JUMP_SMALL		300
#define  MOVING_FLATFORM_STATE_IS_TOUCH		400

#define	 MOVING_FLATFORM_SPEED_VERTICAL		0.1


#define  MOVING_FLATFORM_GRAVITY		0.00001

class MovingFlatform :public CGameObject
{
public:
	CMario *mario = NULL;
	bool is_touch = false;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	MovingFlatform(CMario *player) { mario = player; type = 1; };
};

