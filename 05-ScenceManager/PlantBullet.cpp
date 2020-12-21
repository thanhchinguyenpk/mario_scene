#include "PlantBullet.h"

void PlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	//if (state != MARIO_STATE_DIE)
	//	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	/*	for (UINT i = 0; i < coEventsResult.size(); i++)
		{
		}
		*/
	}



	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void PlantBullet::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void PlantBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PLANT_BULLET_BBOX_WIDTH;
	bottom = y + PLANT_BULLET_BBOX_HEIGHT;
}

void PlantBullet::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case PLANT_BULLET_STATE_ONE:
		vx = PLANT_BULLET_WALKING_SPEED;
		vy = -PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_TWO:
		vx = PLANT_BULLET_WALKING_SPEED;
		vy = PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_THREE:
		vx = -PLANT_BULLET_WALKING_SPEED;
		vy = PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_FOUR:
		vx = -PLANT_BULLET_WALKING_SPEED;
		vy = -PLANT_BULLET_WALKING_SPEED;
		break;
	}

}
