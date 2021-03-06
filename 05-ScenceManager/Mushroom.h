#pragma once
#include "GameObject.h"
#include "Pine.h"

#define MUSHROOM_MOVING_SPEED 0.15f;

#define  MUSHROOM_BBOX_WIDTH 16*3
#define  MUSHROOM_BBOX_HEIGHT 14*3
#define  MUSHROOM_BBOX_HEIGHT_DIE 9

#define  MUSHROOM_STATE_GOING_UP		 0
#define  MUSHROOM_STATE_MOVING_LEFT		 100
#define  MUSHROOM_STATE_MOVING_RIGHT	 200

#define  MUSHROOM_ANI_WALKING 0
#define  MUSHROOM_ANI_DIE 1

#define  MUSHROOM_TIME_GO_UP 100;
#define  MUSHROOM_FLAT_EXCEPT_FIRST_BRICK_COIN 0;

class Mushroom : public CGameObject
{
	float pos_y_brick = 0;
	bool enable_gravity = false;
	//bool is_red = true;

	public:
		bool is_read_mushroom = true;
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();
		DWORD time_go_out_brick;


	
		virtual void SetState(int state);
		Mushroom(float pos_x_brick,float pos_y_brick);
};

