#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "TimerCustom.h"

#define	 BROTHER_WEAPON_BBOX_WIDTH 48
#define	 BROTHER_WEAPON_BBOX_HEIGHT 48

//vy = -0.25*3;
#define  BROTHER_WEAPON_WALKING_SPEED			 0.3f;

#define  BROTHER_WEAPON_STATE_MOVE_LEFT		100
#define  BROTHER_WEAPON_STATE_MOVE_RIGHT		200
#define  BROTHER_WEAPON_STATE_MOVE_DOWN		300

#define	 BROTHER_WEAPON_SPEED_VERTICAL		0.1


#define  BROTHER_WEAPON_GRAVITY		0.0009

class BoomerangWeapon :public CGameObject
{
public:

	CMario * mario = NULL;
	bool was_hit_mario = false;

	float original_x = 0;
	float original_y = 0;

	DWORD time_move_left = 0;
	DWORD time_move_down = 0;
	DWORD time_move_right = 0;

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	void SetWhereToGo(float x, float y) { original_x = x, original_y = y; };
	BoomerangWeapon(float x,float y, CMario *player);
};
