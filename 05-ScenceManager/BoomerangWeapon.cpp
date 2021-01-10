#include "BoomerangWeapon.h"
#include "debug.h"
#include "debug.h"

void BoomerangWeapon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BROTHER_WEAPON_BBOX_WIDTH / 2;
	t = y - BROTHER_WEAPON_BBOX_HEIGHT / 2;
	r = x + BROTHER_WEAPON_BBOX_WIDTH / 2;
	b = y + BROTHER_WEAPON_BBOX_HEIGHT / 2;
}

void BoomerangWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, coObjects);

	//vy += BROTHER_WEAPON_GRAVITY * dt;

	x += dx;
	y += dy;

	if (GetTickCount64() - time_move_down>200 && time_move_down)
	{
		SetState(BROTHER_WEAPON_STATE_MOVE_LEFT);
		time_move_down = 0;
		
	}
	else if (GetTickCount64() - time_move_left > 700 && time_move_left)
	{
		SetPosition(original_x, original_y);
		SetState(BROTHER_WEAPON_STATE_MOVE_RIGHT);
		time_move_left = 0;
	}
	else if (GetTickCount64() - time_move_right > 1000 && time_move_right)
	{
		SetState(BROTHER_WEAPON_STATE_MOVE_DOWN);
		time_move_right = 0;
	}


	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);



	mario->GetBoundingBox(ml, mt, mr, mb);

	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb) && was_hit_mario == false)
	{
		mario->CollideWithEnemy();
		was_hit_mario = true;
	}
	
}

void BoomerangWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BROTHER_WEAPON_STATE_MOVE_LEFT:
		time_move_left = GetTickCount64();
		vx = -0.5;
		vy =0.05;
		break;
	case BROTHER_WEAPON_STATE_MOVE_RIGHT:
		time_move_right = GetTickCount64();
		vx = BROTHER_WEAPON_WALKING_SPEED;
		vy = -0.08;
		break;
	case BROTHER_WEAPON_STATE_MOVE_DOWN:
		time_move_down = GetTickCount64();
		vy = 0.5;
		vx = 0.3;
		break;
	}
}

void BoomerangWeapon::Render()
{
	int ani = 0;
	int direction = -1;// texture nos quay ve ben trai nhung minh can quay ve ben phai
	int ny = 1;
	if (state == BROTHER_WEAPON_STATE_MOVE_DOWN)
		ani = 1;
	animation_set->at(ani)->Render(x, y, 0, 255, direction, ny);

	//RenderBoundingBox();
}

BoomerangWeapon::BoomerangWeapon(float x, float y, CMario * player)
{
	original_x = x;
	original_y = y;
	mario = player;
}

