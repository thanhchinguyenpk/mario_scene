#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "BoomerangWeapon.h"
#define	 BROTHER_BBOX_WIDTH 48
#define	 BROTHER_BBOX_HEIGHT 72

//vy = -0.25*3;
#define  BROTHER_WALKING_SPEED			 0.1f;

#define  BROTHER_STATE_MOVE_LEFT		100
#define  BROTHER_STATE_MOVE_RIGHT		200
#define  BROTHER_STATE_JUMP_SMALL		300
#define  BROTHER_STATE_DIE		400
#define  BROTHER_STATE_WAS_SHOOTED		500

#define	 BROTHER_SPEED_VERTICAL		0.1


#define  BROTHER_GRAVITY		0.0015

class BoomerangBrother :public CGameObject
{
public:
	CMario * mario = NULL;

	BoomerangWeapon *weapon = NULL;

	DWORD time_to_attack = 0;
	DWORD time_weapon_end = 0;

	bool is_allow_weapon = false;

	float original_x = 0;
	float original_y = 0;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	BoomerangBrother(float x, float y, CMario *player);
};
