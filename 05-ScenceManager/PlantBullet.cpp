#include "PlantBullet.h"

void PlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);



	mario->GetBoundingBox(ml, mt, mr, mb);

	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb)&& was_hit_mario==false)
	{
		mario->CollideWithEnemy();
		was_hit_mario = true;
	}
	

	DeleteWhenOutOfCam();

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
