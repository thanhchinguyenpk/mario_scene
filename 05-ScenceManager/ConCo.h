#pragma once
#include "GameObject.h"
#include "MoneyEffect.h"
#include "BrickBlink.h"

#define CONCO_WALKING_SPEED 0.05f
#define CONCO_MAI_RUA_CHAY_SPEED	 0.05f

#define CONCO_BBOX_WIDTH		 16*3 //ok
#define CONCO_BBOX_HEIGHT		 27*3 //ok
#define CONCO_BBOX_HEIGHT_DIE	 9
#define CONCO_BBOX_WIDTH_THUT_VAO 15*3
#define CONCO_BBOX_HEIGHT_THUT_VAO 13*3

#define CONCO_STATE_WALKING_LEFT	100
#define CONCO_STATE_DIE				200
#define CONCO_STATE_WALKING_RIGHT	300
#define CONCO_STATE_THUT_VAO		400
#define CONCO_STATE_MAI_RUA_CHAY_PHAI	500
#define CONCO_STATE_MAI_RUA_CHAY_TRAI	501
#define CONCO_STATE_FLY_LEFT	    600
#define CONCO_STATE_FLY_RIGHT	    700
#define CONCO_STATE_WAS_BROUGHT	    800
#define CONCO_STATE_WAS_SHOOTED		900
#define CONCO_STATE_INDENT_OUT		1000
#define CONCO_STATE_SHELL_MOVING		1100
#define CONCO_STATE_RED_FLY_Y		1200

#define CONCO_ANI_GREEN_WALKING_LEFT	 0
#define CONCO_ANI_GREEN_THUT_VAO		 1
#define CONCO_ANI_GREEN_MAI_RUA_CHAY	 2
#define CONCO_ANI_GREEN_FLY_LEFT		 3

#define CONCO_ANI_GREEN_FLY_RIGHT			 4
#define CONCO_ANI_GREEN_WALKING_RIGHT	     5
#define CONCO_ANI_GREEN_SHELL_MOVING		 6
#define CONCO_ANI_GREEN_INDENT_OUT		 7

#define CONCO_ANI_RED_WALKING_LEFT	 8
#define CONCO_ANI_RED_THUT_VAO		 9
#define CONCO_ANI_RED_MAI_RUA_CHAY	 10
#define CONCO_ANI_RED_FLY_LEFT		 11

#define CONCO_ANI_RED_FLY_RIGHT			 12
#define CONCO_ANI_RED_WALKING_RIGHT	     13
#define CONCO_ANI_RED_SHELL_MOVING		 14
#define CONCO_ANI_RED_INDENT_OUT		 15

#define CONCO_GRAVITY			0.003

class CConCo : public CGameObject
{
public:
	CMario * mario = NULL;
	CConCo(CMario *player, float y) ;
	int type = 0;

	float orginal_y;
	bool is_change_direction_vy;

	int is_walking_back_and_fort = 1;
	MoneyEffect *effect = NULL;
	int count_brick = 0;

	bool is_brought = false;
	DWORD time_to_indent_out;
	bool shell_moving = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	virtual void SetState(int state);
};
