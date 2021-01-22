#pragma once
#include "GameObject.h"

#define SUPER_LEAF_BBOX_WIDTH 16*3
#define SUPER_LEAF_BBOX_HEIGHT 14*3

#define  SUPER_LEAF_STATE_MOVE_LEFT		100
#define  SUPER_LEAF_STATE_MOVE_RIGHT	200
#define  SUPER_LEAF_STATE_MOVE_UP		300

#define  SUPER_LEAF_DISTANT_MOVE_UP		100
#define  SUPER_LEAF_DISTANT_MOVE_HORIZONTALLY		100

#define  SUPER_LEAF_SPEED_VERTICAL		0.1f
#define  SUPER_LEAF_SPEED_HORIZONTAL		0.15f

class SuperLeaf:public CGameObject
{
	float original_pos_x;
	float original_pos_y;

public:
	SuperLeaf(float brick_pos_x, float brick_pos_y);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
};

