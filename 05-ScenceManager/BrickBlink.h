#pragma once
#include "GameObject.h"
#include "TimerCustom.h"
#include "Mario.h"

#define BRICK_BLINK_BBOX_WIDTH  16*3
#define BRICK_BLINK_BBOX_HEIGHT 16*3

#define BRICK_BLINK_STATE_WAS_HIT 100
#define BRICK_BLINK_STATE_TRANSFORM 200

#define BRICK_BLINK_ANI_BLINK 0
#define BRICK_BLINK_ANI_COIN 1

#define DEBRIS_DISTANCE 9


#define  BRICK_BLINK_STATE_MOVE_LEFT		100 // chỗ này chưa
#define  BRICK_BLINK_STATE_MOVE_RIGHT	200

//extern CMario* mario;
class BrickBlink : public CGameObject
{
public:
	CMario* mario;

	vector<LPGAMEOBJECT> vec_debris;
	int number_debris = 0;

	bool is_brick = true;
	bool vanish = false;
	BrickBlink(CMario* player);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	
};