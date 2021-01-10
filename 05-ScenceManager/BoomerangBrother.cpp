#include "BoomerangBrother.h"
#include "debug.h"
#include "debug.h"

void BoomerangBrother::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BROTHER_BBOX_WIDTH / 2;
	t = y - BROTHER_BBOX_HEIGHT / 2;
	r = x + BROTHER_BBOX_WIDTH / 2;
	b = y + BROTHER_BBOX_HEIGHT / 2;
}

void BoomerangBrother::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);

	vy += BROTHER_GRAVITY * dt;

	//x += dx;
	//y += dy;
	if (x > original_x + 100)
		SetState(BROTHER_STATE_MOVE_LEFT);
	else if(x<original_x)
		SetState(BROTHER_STATE_MOVE_RIGHT);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	//if đã nha nếu mà nấm khác với nấm biến mất thì
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		DebugOut(L"[x] DINPUT::GetDeviceData failed. Error: %f\n", x);
		DebugOut(L"[origin +100] DINPUT::GetDeviceData failed. Error: %f\n", original_x + 100);
		
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0;

		if (ny != 0)
			vy = 0;






		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];



			/*if (dynamic_cast<Flatform*>(e->obj))
			{

				Flatform* flatform = dynamic_cast<Flatform*>(e->obj);

				if (this->x > flatform->x + 243)
					SetState(CONCO_STATE_WALKING_LEFT);
				if (this->x < flatform->x)
					SetState(CONCO_STATE_WALKING_RIGHT);
			}*/

		}

	}




	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void BoomerangBrother::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BROTHER_STATE_MOVE_LEFT:
		vx = -BROTHER_WALKING_SPEED;
		vy = 0;
		break;
	case BROTHER_STATE_MOVE_RIGHT:
		vx = BROTHER_WALKING_SPEED;
		break;
	case BROTHER_STATE_JUMP_SMALL:
		vy = -BROTHER_WALKING_SPEED;
		break;
	}
}

void BoomerangBrother::Render()
{
	int direction = -1;// texture nos quay ve ben trai nhung minh can quay ve ben phai
	int ny = 1;
	animation_set->at(0)->Render(x, y, 0, 255, direction, ny);

	RenderBoundingBox();
}

BoomerangBrother::BoomerangBrother(float x, CMario * player)
{
	original_x = x;
	mario = player;
}

