#pragma once
#include "GameObject.h"

#define PLANT_BULLET_WALKING_SPEED 0.08f;

#define PLANT_BULLET_BBOX_WIDTH 9*3
#define PLANT_BULLET_BBOX_HEIGHT 9*3
#define PLANT_BULLET_BBOX_HEIGHT_DIE 9

#define PLANT_BULLET_STATE_ONE 100 //bắt đầu từ chiều kim đồng hồ 12h, góc 1 2 3 4
#define PLANT_BULLET_STATE_TWO 200
#define PLANT_BULLET_STATE_THREE 300
#define PLANT_BULLET_STATE_FOUR 400


class PlantBullet : public CGameObject
{

public:
	PlantBullet() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

