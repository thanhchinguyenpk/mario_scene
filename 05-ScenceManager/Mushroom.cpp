#include "Mushroom.h"
#include "Brick_Coin.h"
#include "debug.h"
#include "Brick.h"
#include "Flatform.h"
#include "Mario.h"

//extern vector<LPGAMEOBJECT> objects;
//extern CMario* mario;

//int boQuaVienDaDongTienDauTienAnNap = 0;



void Mushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left	 =	 x - MUSHROOM_BBOX_WIDTH/2;
	top		 =	 y - MUSHROOM_BBOX_HEIGHT/2;
	right	 =	 x + MUSHROOM_BBOX_WIDTH/2;
	bottom	 =	 y + MUSHROOM_BBOX_HEIGHT/2;

}

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//y += dy;

	if(enable_gravity==true)
		vy += 0.003 * dt;

		
	if (y <= pos_y_brick - MUSHROOM_BBOX_HEIGHT-5)
	{
		enable_gravity = true;
		SetState(MUSHROOM_STATE_MOVING_RIGHT);
	}
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();


	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		

		//if (nx != 0)
		//	vx = -vx;
		if (ny != 0)
			vy = 0;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Flatform*>(e->obj)|| dynamic_cast<Pine*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				Flatform* flatform = dynamic_cast<Flatform*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->nx != 0) //nêu như phương va chạm hướng lên ( lưu ý trục y hướng xuống)
					vx = -vx;
			}

		/*	if (dynamic_cast<CMario*>(e->obj)) // if e->obj is Goomba // nếu như là goomba
			{
				x += dx;
				y += dy;


			}*/



		}






	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		


	/*float l, t, r, b;
	float ml, mt, mr, mb;

	mario->GetBoundingBox(l, t, r, b);


	this->GetBoundingBox(ml, mt, mr, mb);

	if (CheckOverLap(ml, mt, mr, mb, l, t, r, b))

	{
		used = true;	
	}*/
	
	
}

void Mushroom::Render()
{
	int ani = MUSHROOM_ANI_WALKING;

	if (is_read_mushroom == false)
		ani = 1;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void Mushroom::SetState(int state)
{

	CGameObject::SetState(state);

	switch (state)
	{
	case MUSHROOM_STATE_GOING_UP:
		vx = 0;
		vy = -0.1;
		break;
	case MUSHROOM_STATE_MOVING_LEFT:
		vx = -MUSHROOM_MOVING_SPEED;
		
		break;
	case MUSHROOM_STATE_MOVING_RIGHT:
		vx = MUSHROOM_MOVING_SPEED;
		break;
	}
}

Mushroom::Mushroom(float pos_x_brick, float pos_y_brick)
{
		this->pos_y_brick = pos_y_brick;

		CAnimationSets * animation_sets_temp = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets_temp->Get(12);
		this->SetAnimationSet(ani_set);

		SetPosition(pos_x_brick, pos_y_brick);
		SetState(MUSHROOM_STATE_GOING_UP);

}

