#include "PiranhaPlant.h"
#include "GameObject.h"
#include "debug.h"


PiranhaPlant::PiranhaPlant(CMario * player)
{
	mario = player;
}

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	y += dy;
	if (y <= GREEN_PIRANHA_MIN_HEIGHT && !cap_cap_time)
	{
		vy = 0;
		cap_cap_time = GetTickCount64();

	}else if (y >= GREEN_PIRANHA_MAX_HEIGHT && !couch_time)
	{
		vy = 0;
		couch_time= GetTickCount64();
	}


	if (cap_cap_time && GetTickCount64() - cap_cap_time > 820)
	{
		SetState(PIRANHA_PLANT_STATE_GOING_DOWN);
		cap_cap_time = 0;

	}else if (couch_time && GetTickCount64() - couch_time > 820)
	{
		float l, t, r, b;
		mario->GetBoundingBox(l, t, r, b);
		if (!CheckMarioNear(l, t, r, b))
		{
			SetState(PIRANHA_PLANT_STATE_GOING_UP);
			couch_time = 0;
		}
	
	}

	//DebugOut(L"[ERROR---------pira-----------------] DINPUT::GetDeviceData failed. Error: %d\n", state);
}

void PiranhaPlant::Render()
{
	int ani = 0;
	int direction = 1;
	int ny = 1;

	animation_set->at(ani)->Render(x, y, 0, 255, direction, ny);
}

void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	right = x + PIRANHA_PLANT_BBOX_WIDTH / 2;
	bottom = y + PIRANHA_PLANT_BBOX_HEIGHT / 2;
}

void PiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHA_PLANT_STATE_GOING_UP:
		vy = -GREEN_PIRANHA_SPEED_Y;
		vx = 0;
		break;
	case PIRANHA_PLANT_STATE_GOING_DOWN:
		vy = GREEN_PIRANHA_SPEED_Y;
		vx = 0;
		break;

	}
}

bool PiranhaPlant::CheckMarioNear(float l, float t, float r, float b)
{
	return
		(l <= GREEN_PIRANHA_RIGHT_ZONE &&
		r >= GREEN_PIRANHA_LEFT_ZONE &&
		t <= GREEN_PIRANHA_BOTTOM_ZONE&&
		b >= GREEN_PIRANHA_TOP_ZONE) ;
		
}

