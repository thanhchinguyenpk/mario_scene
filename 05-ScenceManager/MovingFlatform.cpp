#include "MovingFlatform.h"
#include "Game.h"
#include "BrickBlink.h"

void MovingFlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MOVING_FLATFORM_BBOX_WIDTH / 2;
	t = y - MOVING_FLATFORM_BBOX_HEIGHT / 2;
	r = x + MOVING_FLATFORM_BBOX_WIDTH / 2;
	b = y + MOVING_FLATFORM_BBOX_HEIGHT / 2;
}

void MovingFlatform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (mario->x + mario->distance_to_set_state_enemy > this->x && this->is_cam_coming == false)
	{
		SetState(MOVING_FLATFORM_STATE_MOVE_LEFT);
		this->is_cam_coming = true;
	}

	if (is_cam_coming == true)
	{


		CGameObject::Update(dt, coObjects);

		if (state == MOVING_FLATFORM_STATE_IS_TOUCH)
			vy += MOVING_FLATFORM_GRAVITY * dt;

		x += dx;
		y += dy;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();

		//if đã nha nếu mà nấm khác với nấm biến mất thì
		CalcPotentialCollisions(coObjects, coEvents);
		//x += dx;
		if (coEvents.size() == 0)
		{

			if (state == MOVING_FLATFORM_STATE_IS_TOUCH)
				y += dy;
		}
		else
		{
			float vy_flatform = 0;
			float vx_flatform = 0;

			float y_flatform = 0;
			float x_flatform = 0;



			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			x += min_tx * dx + nx * 0.4f;
			//y += min_ty * dy + ny * 0.4f;

			x_flatform = min_tx * dx + nx * 0.4f;
			y_flatform = min_ty * dy + ny * 0.4f;

			vy_flatform = vy;
			vx_flatform = vx;

			if (nx != 0)
				//vx = 0;

			if (ny != 0)
				//vy = 0;






				for (UINT i = 0; i < coEventsResult.size(); i++)
				{

					LPCOLLISIONEVENT e = coEventsResult[i];

					if (dynamic_cast<BrickBlink*>(e->obj))
					{

						//y += (y_flatform + y_flatform);// double for safe
						//x += (x_flatform + x_flatform);
						//x += dx;
						//y += dy;
					}

				}

		}




		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];




		/*this->SetPosition(CGame::GetInstance()->GetCamX(), y);


		float ml, mt, mr, mb;
		float il, it, ir, ib;

		this->GetBoundingBox(il, it, ir, ib);
		mario->GetBoundingBox(ml, mt, mr, mb);

		if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
		{
			//SetState(CONCO_STATE_WAS_SHOOTED);
			float x, y;
			mario->GetPosition(x, y);
			mario->SetPosition(x + 0.1, y);
		}
			*/
	}

	if (y > 470 * 3)
		used = true;
}

void MovingFlatform::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MOVING_FLATFORM_STATE_MOVE_LEFT:
		vx = -MOVING_FLATFORM_WALKING_SPEED;// -0.1;//-0.04f;
		vy = 0;
		break;
	case MOVING_FLATFORM_STATE_MOVE_RIGHT:
		vx = MOVING_FLATFORM_WALKING_SPEED;
		break;
	case MOVING_FLATFORM_STATE_JUMP_SMALL:
		vy = -MOVING_FLATFORM_WALKING_SPEED;
		break;
	case MOVING_FLATFORM_STATE_IS_TOUCH:
		vx = 0;
		vy = 0;
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

