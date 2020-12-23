#include "InvisibleObject.h"

InvisibleObject::InvisibleObject(float x, float y, float width, float height, int state)
{
	this->x = x;
	this->y = y;

	this->w = width;
	this->h = height;

	this->state = state;

	if (state == STATE_GUARD)
		vx = 0.05f;
}

void InvisibleObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + w;
	bottom = top + h;
}

void InvisibleObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_GUARD) {
		if (vx < 0 && x < 250) {
			x = 250;
			vx = -vx;
			nx *= -1;

		}

		if (vx > 0 && x > 336) {
			x = 336;
			vx = -vx;
			nx *= -1;

		}
		CGameObject::Update(dt);
		x += dx;

	}
}

void InvisibleObject::Render()
{
	int ani = 0;
	if (state == STATE_GHOST_PLATFORM)
		ani = ANI_GHOST_PLATFORM;
	else if (state == STATE_CACTUS)
		ani = ANI_CACTUS;
	else if (state == STATE_HELP_TAG)
		ani = ANI_HELP_TAG;
	else if (state == STATE_GUARD)
		ani = ANI_GUARD;
	else if (state == STATE_3_INTRO)
		ani = ANI_3_INTRO;
	else if (state == STATE_ARROW)
		ani = ANI_ARROW;
	animation_set->at(ani)->Render(x+24, y+24, 0, 255, nx, ny);
	//RenderBoundingBox();
}
