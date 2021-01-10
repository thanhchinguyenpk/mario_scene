#include "MovingFlatform.h"
void MovingFlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MOVING_FLATFORM_BBOX_WIDTH / 2;
	t = y - MOVING_FLATFORM_BBOX_HEIGHT / 2;
	r = x + MOVING_FLATFORM_BBOX_WIDTH / 2;
	b = y + MOVING_FLATFORM_BBOX_HEIGHT / 2;
}

void MovingFlatform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if(is_touch)
	vy += MOVING_FLATFORM_GRAVITY * dt;

	//x += dx;
	//y += dy;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		if (is_touch)
			y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0;

		if (ny != 0)
			//vy = 0;






		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];



			
		}

	}




	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void MovingFlatform::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MOVING_FLATFORM_STATE_MOVE_LEFT:
		vx = MOVING_FLATFORM_WALKING_SPEED;
		vy = 0;
		break;
	case MOVING_FLATFORM_STATE_MOVE_RIGHT:
		vx = -MOVING_FLATFORM_WALKING_SPEED;
		break;
	case MOVING_FLATFORM_STATE_JUMP_SMALL:
		vy = -MOVING_FLATFORM_WALKING_SPEED;
		break;
	}
}

void MovingFlatform::Render()
{
	int direction = 1;
	int ny = 1;
	animation_set->at(0)->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

