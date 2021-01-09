#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "PlantBullet.h"

#define VENUS_WALKING_SPEED 0.06f;

#define VENUS_BBOX_WIDTH 16*3
#define VENUS_BBOX_HEIGHT 22*3
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define VENUS_STATE_GOING_UP			 100
#define VENUS_STATE_GOING_DOWN			 200
#define VENUS_STATE_SHOOTING_UP			 300
#define VENUS_STATE_SHOOTING_DOWN		 400
#define VENUS_STATE_SEEING				 500
#define VENUS_STATE_STANDING_STILL		 600
#define VENUS_STATE_SLEEPING	700

#define VENUS_ANI_SCORPION_DOWN 0
#define VENUS_ANI_SCORPION_UP 1
#define VENUS_ANI_SHOOTING_DOWN 2
#define VENUS_ANI_SHOOTING_UP 3

#define VENUS_GREEN_ANI_SCORPION_DOWN 4
#define VENUS_GREEN_ANI_SCORPION_UP 5
#define VENUS_GREEN_ANI_SHOOTING_DOWN 6
#define VENUS_GREEN_ANI_SHOOTING_UP 7



#define VENUS_TIME_GOING_UP			 2400
#define VENUS_TIME_GOING_DOWN			 200
#define VENUS_TIME_SHOOTING_UP			 300
#define VENUS_TIME_SHOOTING		 2200
#define VENUS_TIME_SEEING				 3000
#define VENUS_TIME_STANDING_STILL		 4000

#define VENUS_HEIGHT_RAISE_HEAD		 1068

#define VENUS_RED_TRAP		 1
#define VENUS_GREEN_TRAP		 2

class VenusFireTrap : public CGameObject
{
public:
	vector<LPGAMEOBJECT> listFireball;
	CMario* mario;
	//VenusFireTrap();
	int pos_y_venus_max_top=1002;//dm chiều y hướng xuống :(
	int pos_y_venus_max_bot= 11002;

	float pos_y_fireball;
	float pos_x_fireball;

	int level = 1;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void SetState(int state);
	VenusFireTrap(CMario* player,int levlel);
	//TimerCustom* contemplation_time = new TimerCustom(3000);
	TimerCustom* sleep_time = new TimerCustom(2000);
	TimerCustom* seeing_time = new TimerCustom(1800);
	TimerCustom* seeing_time_shoot_go_down = new TimerCustom(3000);

	bool CheckInArea(float l,float t,float r,float b);
	void TakeMaxTopAndBot();


};

