#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PIRANHA_PLANT_BBOX_WIDTH 16*3
#define PIRANHA_PLANT_BBOX_HEIGHT 24*3

#define PIRANHA_PLANT_STATE_GOING_UP 100
#define PIRANHA_PLANT_STATE_GOING_DOWN 200

#define GREEN_PIRANHA_SPEED_Y 0.06

#define GREEN_PIRANHA_MIN_HEIGHT 1118
#define GREEN_PIRANHA_MAX_HEIGHT 1195

#define GREEN_PIRANHA_LEFT_ZONE 5370
#define GREEN_PIRANHA_RIGHT_ZONE 5475
#define GREEN_PIRANHA_TOP_ZONE 0
#define GREEN_PIRANHA_BOTTOM_ZONE 4000

//extern CMario* mario;

class PiranhaPlant : public CGameObject
{
	DWORD cap_cap_time=0;
	DWORD couch_time = 0;
	DWORD attackStartTime;
	bool flag = false;
public:
	PiranhaPlant(CMario* player);
	CMario* mario;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
	bool CheckMarioNear(float l, float t, float r, float b);
};

