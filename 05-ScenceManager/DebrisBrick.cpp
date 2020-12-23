#include "DebrisBrick.h"
#include "Game.h"
#include "Map.h"

void DebrisBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);

	vy += DEBRIS_BRICK_GRAVITY * dt;

	x += dx;
	y += dy;

	if (y > CGame::GetInstance()->GetCamY() + SCREEN_WIDTH)
		this->used = true;
}

void DebrisBrick::Render()
{


	int direction = 1;
	int ny = 1;
	animation_set->at(0)->Render(x, y, 0, 255, direction, ny);
}

void DebrisBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

DebrisBrick::DebrisBrick(float brick_pos_x, float brick_pos_y, int nx, float height)
{
	vx = DEBRIS_BRICK_SPEED_X * nx;
	vy = -DEBRIS_BRICK_SPEED_Y * height;
	x = brick_pos_x;
	y = brick_pos_y;
	
	//this->AddAnimation(16000);
	CAnimationSets * animation_sets_temp = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets_temp->Get(20);
	SetAnimationSet(ani_set);
}
