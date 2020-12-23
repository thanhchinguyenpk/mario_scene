#include "SuperLeaf.h"
#include "Mario.h"
#include "debug.h"
#include "Game.h"
#include "Map.h"

SuperLeaf::SuperLeaf(float brick_pos_x, float brick_pos_y)
{
	original_pos_x = brick_pos_x;
	original_pos_y = brick_pos_y;

	CAnimationSets * animation_sets_temp = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets_temp->Get(11);
	this->SetAnimationSet(ani_set);


	SetPosition(brick_pos_x, brick_pos_y);
	SetState(SUPER_LEAF_STATE_MOVE_UP);

}

void SuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_LEAF_BBOX_WIDTH / 2;
	t = y - SUPER_LEAF_BBOX_HEIGHT / 2;
	r = x + SUPER_LEAF_BBOX_WIDTH / 2;
	b = y + SUPER_LEAF_BBOX_HEIGHT / 2;
}

void SuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == SUPER_LEAF_STATE_MOVE_UP && this->y > original_pos_y - SUPER_LEAF_DISTANT_MOVE_UP)
		y += dy;
	else if(state == SUPER_LEAF_STATE_MOVE_UP && this->y <= original_pos_y - SUPER_LEAF_DISTANT_MOVE_UP)
		SetState(SUPER_LEAF_STATE_MOVE_RIGHT);
	
	if (state == SUPER_LEAF_STATE_MOVE_RIGHT && this->x < original_pos_x + SUPER_LEAF_DISTANT_MOVE_HORIZONTALLY)
	{
		y += dy;
		x += dx;
	}else if(state == SUPER_LEAF_STATE_MOVE_RIGHT && this->x >= original_pos_x + SUPER_LEAF_DISTANT_MOVE_HORIZONTALLY)
		SetState(SUPER_LEAF_STATE_MOVE_LEFT);

	if (state == SUPER_LEAF_STATE_MOVE_LEFT && this->x > original_pos_x)
	{
		y += dy;
		x += dx;
	}
	else if (state == SUPER_LEAF_STATE_MOVE_LEFT && this->x <= original_pos_x)
		SetState(SUPER_LEAF_STATE_MOVE_RIGHT);

	if (y > CGame::GetInstance()->GetCamY() + SCREEN_WIDTH)
		this->used = true;

}

void SuperLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUPER_LEAF_STATE_MOVE_UP:
		vx = 0;
		vy =-SUPER_LEAF_SPEED_VERTICAL;
		break;
	case SUPER_LEAF_STATE_MOVE_LEFT:
		vx = -SUPER_LEAF_SPEED_HORIZONTAL;
		vy = SUPER_LEAF_SPEED_VERTICAL;
		break;
	case SUPER_LEAF_STATE_MOVE_RIGHT:
		vx = SUPER_LEAF_SPEED_HORIZONTAL;
		vy = SUPER_LEAF_SPEED_VERTICAL;
		break;
	}
}

void SuperLeaf::Render()
{
	int direction = 1;
	int ny = 1;
	if (state == SUPER_LEAF_STATE_MOVE_RIGHT)
		direction = -1;
	animation_set->at(0)->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}
