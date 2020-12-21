#pragma once
#include "GameObject.h"


#define MARIOBULLET_GRAVITY			0.002f*1.5

#define MARIOBULLET_BBOX_WIDTH 9*3
#define MARIOBULLET_BBOX_HEIGHT 9*3
#define MARIOBULLET_BBOX_HEIGHT_DIE 9

#define MARIOBULLET_STATE_WALKING_RIGHT 100
#define MARIOBULLET_STATE_WALKING_LEFT 200
#define MARIOBULLET_STATE_BUM 300
#define MARIOBULLET_STATE_DIE 400

#define MARIOBULLET_ANI_WALKING 0
#define MARIOBULLET_ANI_BUM 1
#define MARIOBULLET_ANI_DIE 2

#define  MARIOBULLET_WALKING_SPEED 0.5f;



class MarioBullet : public CGameObject
{
	bool is_disapear = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	//MarioBullet();
	virtual void SetState(int state);
	 ~MarioBullet() {};
};
